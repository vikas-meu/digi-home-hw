/*
 * Copyright (C) 2026-Present Vikash Singh Thakur
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */
#include "Adafruit_PyCamera.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SdFat.h> // Already included via Adafruit_PyCamera, but ensure
#include <driver/ledc.h>
#include <driver/gpio.h>
#include <Wire.h>
#include <time.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <vector>
#include <strings.h>
#include <esp_camera.h>
// --- CREDENTIALS ---
const char* ssid = " ";
const char* password = " ";
#define BOTtoken " "
#define CHAT_ID " "
// Pin definitions
#define MIC 20
#define SPEAKER 18
#define AWEXP_SPKR_SD 0 // Speaker mute control on AW9523 pin 0
#define SDA_PIN 34
#define SCL_PIN 33
// I2C slave address for Arduino
const uint8_t ARDUINO_ADDR = 0x08;
const uint8_t ARDUINO2_ADDR = 0x09; // Second Arduino
// Timezone offset for IST (UTC+5:30)
const long timezoneOffset = 19800; // 5.5 * 3600
// Controller ESP32 IP (replace with the actual IP of the ESP32 running the web server)
const char* controllerIP = "192.168.1.100"; // TODO: Set to the IP address of the control ESP32
Adafruit_PyCamera pycamera;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
// Global variables for the "chunked" upload
int currentByte = 0;
size_t fb_length = 0;
uint8_t* fb_buffer = NULL;
// Helper functions for Telegram binary transfer
bool isMoreDataAvailable() {
  return (fb_length - currentByte);
}
uint8_t photoNextByte() {
  currentByte++;
  return fb_buffer[currentByte - 1];
}
// For Telegram polling
unsigned long bot_lasttime = 0;
const long BOT_MTBS = 2000; // Poll every 1 second
// For motion detection
uint16_t *prev_buffer = NULL;
unsigned long last_snap_time = 0;
const long SNAP_COOLDOWN = 5000; // 5 seconds cooldown to avoid spamming
bool securityMode = false;
// For green object tracking
bool tracking = false;
// For scheduling
struct Event {
  time_t eventTime;
  String details;
  String arduinoCmd;
  String reminder;
  bool triggered = false;
};
std::vector<Event> scheduledEvents;
bool awaitingSchedule = false;
// Modes
enum Mode {
  MODE_IDLE,
  MODE_MENU,
  MODE_CAMERA,
  MODE_GAME_MENU,
  MODE_PINGPONG,
  MODE_SNAKE,
  MODE_HOME_ASSISTANT
};
Mode currentMode = MODE_IDLE;
int menuSelection = 0;
const char* menuOptions[] = {"Camera Mode", "Game Mode", "Home Assistant"};
int numMenuOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
// For games
// Snake game variables
#define SNAKE_MAX_LENGTH 100
struct Point {
  int x, y;
};
Point snake[SNAKE_MAX_LENGTH];
int snakeLength = 5;
int snakeDir = 0; // 0 right, 1 down, 2 left, 3 up
Point food;
unsigned long lastSnakeMove = 0;
int snakeSpeed = 200;
// Pong game variables
int paddle1Y = 100, paddle2Y = 100;
int ballX = 120, ballY = 120;
int ballDX = 2, ballDY = 2;
int score1 = 0, score2 = 0;
unsigned long lastPongUpdate = 0;
int pongSpeed = 10;
// For game submenu
const char* gameOptions[] = {"Ping Pong", "Snake"};
int numGameOptions = 2;
int gameSelection = 0;
// Function prototypes
void drawMenu();
void handleMenuNavigation();
void cameraMode();
void pingPongMode();
void snakeMode();
void homeAssistantMode();
void handleNewMessages(int numNewMessages);
void takeAndSendPhoto(int reply_to_message_id = 0);
void recordAudio();
void playAudio();
void sendDanceCommand();
void trackGreenObject();
void checkScheduledEvents();
bool parseSchedule(String text, String chat_id);
void sendI2CCommandTo(uint8_t addr, const char* cmd);
void sendTelegramMessage(String chat_id, String message, int reply_to_message_id = 0);
void sendControlCommand(String endpoint);
void setup() {
  Serial.begin(115200);
  delay(100);
  if (!pycamera.begin()) {
    Serial.println("Failed to initialize pyCamera interface");
    while (1) yield();
  }
  Serial.println("pyCamera hardware initialized!");
  pycamera.initSD();
  // Initialize snake
  for (int i = 0; i < snakeLength; i++) {
    snake[i].x = 120 - i*10;
    snake[i].y = 120;
  }
  food.x = random(24)*10;
  food.y = random(24)*10;
  pycamera.photoSize = FRAMESIZE_QVGA;
  if (!pycamera.initSD()) {
    Serial.println("SD init failed!");
    while (1);
  }
  // Allocate previous buffer for motion detection (240x240 RGB565)
  prev_buffer = (uint16_t*)ps_malloc(240 * 240 * sizeof(uint16_t));
  if (!prev_buffer) {
    Serial.println("Failed to allocate prev_buffer!");
    while (1);
  }
  WiFi.begin(ssid, password);
  client.setInsecure();
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nReady!");
  // Set up time
  configTime(timezoneOffset, 0, "pool.ntp.org", "time.nist.gov");
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
  }
  // Initialize display settings for the Gyro text
  pycamera.fb->setTextSize(2);
  // Setup LEDC timer
  ledc_timer_config_t timer_conf = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 200000,
      .clk_cfg = LEDC_AUTO_CLK
  };
  ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));
  // Initialize I2C as master
  Wire.begin(SDA_PIN, SCL_PIN);

  // Start in Home Assistant mode by default
  currentMode = MODE_HOME_ASSISTANT;
}
void loop() {
  pycamera.readButtons();
  if (pycamera.justPressed(AWEXP_BUTTON_SEL)) {
    if (currentMode != MODE_MENU) {
      currentMode = MODE_MENU;
      menuSelection = 0;
      drawMenu();
    }
  }
  switch (currentMode) {
    case MODE_MENU:
      handleMenuNavigation();
      break;
    case MODE_CAMERA:
      cameraMode();
      break;
    case MODE_GAME_MENU:
      // Similar to menu
      if (pycamera.justPressed(AWEXP_BUTTON_UP)) gameSelection = (gameSelection - 1 + numGameOptions) % numGameOptions;
      if (pycamera.justPressed(AWEXP_BUTTON_DOWN)) gameSelection = (gameSelection + 1) % numGameOptions;
      if (pycamera.justPressed(AWEXP_BUTTON_OK)) {
        if (gameSelection == 0) currentMode = MODE_PINGPONG;
        else currentMode = MODE_SNAKE;
      }
      // Draw game menu
      pycamera.fb->fillScreen(0);
      pycamera.fb->setCursor(10, 10);
      pycamera.fb->setTextSize(2);
      pycamera.fb->print("Games:");
      for (int i = 0; i < numGameOptions; i++) {
        pycamera.fb->setCursor(10, 40 + i*20);
        if (i == gameSelection) pycamera.fb->setTextColor(0xFFFF);
        else pycamera.fb->setTextColor(0xAD55);
        pycamera.fb->print(gameOptions[i]);
      }
      pycamera.blitFrame();
      break;
    case MODE_PINGPONG:
      pingPongMode();
      break;
    case MODE_SNAKE:
      snakeMode();
      break;
    case MODE_HOME_ASSISTANT:
      homeAssistantMode();
      break;
    default:
      // Idle: perhaps live preview
      pycamera.captureFrame();
      pycamera.blitFrame();
      break;
  }
  delay(10);
}
// Draw main menu
void drawMenu() {
  pycamera.fb->fillScreen(0);
  pycamera.fb->setCursor(10, 10);
  pycamera.fb->setTextSize(2);
  pycamera.fb->setTextColor(0xFFFF);
  pycamera.fb->print("Menu:");
  for (int i = 0; i < numMenuOptions; i++) {
    pycamera.fb->setCursor(10, 40 + i*20);
    if (i == menuSelection) pycamera.fb->setTextColor(0xFFFF);
    else pycamera.fb->setTextColor(0xAD55);
    pycamera.fb->print(menuOptions[i]);
  }
  pycamera.blitFrame();
}
// Handle navigation in menu
void handleMenuNavigation() {
  if (pycamera.justPressed(AWEXP_BUTTON_UP)) {
    menuSelection = (menuSelection - 1 + numMenuOptions) % numMenuOptions;
    drawMenu();
  }
  if (pycamera.justPressed(AWEXP_BUTTON_DOWN)) {
    menuSelection = (menuSelection + 1) % numMenuOptions;
    drawMenu();
  }
  if (pycamera.justPressed(AWEXP_BUTTON_OK)) {
    switch (menuSelection) {
      case 0: currentMode = MODE_CAMERA; break;
      case 1: currentMode = MODE_GAME_MENU; gameSelection = 0; break;
      case 2: currentMode = MODE_HOME_ASSISTANT; break;
    }
  }
}
// Camera mode
void cameraMode() {
  pycamera.captureFrame();
  // Add UI if needed
  pycamera.fb->setCursor(10, 10);
  pycamera.fb->setTextSize(1);
  pycamera.fb->print("Camera Mode");
  pycamera.blitFrame();
  if (pycamera.justPressed(SHUTTER_BUTTON)) {
    pycamera.takePhoto("PHOTO", pycamera.photoSize);
    pycamera.speaker_tone(100, 50);
  }
  if (pycamera.justPressed(AWEXP_BUTTON_UP)) pycamera.photoSize = (framesize_t)((int)pycamera.photoSize + 1 % 11);
  if (pycamera.justPressed(AWEXP_BUTTON_DOWN)) pycamera.photoSize = (framesize_t)((int)pycamera.photoSize - 1 + 11 % 11);
  if (pycamera.justPressed(AWEXP_BUTTON_LEFT)) pycamera.specialEffect = (pycamera.specialEffect + 6) % 7; pycamera.setSpecialEffect(pycamera.specialEffect);
  if (pycamera.justPressed(AWEXP_BUTTON_RIGHT)) pycamera.specialEffect = (pycamera.specialEffect + 1) % 7; pycamera.setSpecialEffect(pycamera.specialEffect);
}
// Ping Pong mode (simple AI for player 2)
void pingPongMode() {
  if (millis() - lastPongUpdate > pongSpeed) {
    lastPongUpdate = millis();
    // Move paddles
    if (pycamera.justPressed(AWEXP_BUTTON_UP)) paddle1Y -= 10;
    if (pycamera.justPressed(AWEXP_BUTTON_DOWN)) paddle1Y += 10;
    paddle1Y = constrain(paddle1Y, 0, 200);
    // AI for paddle2
    if (ballY > paddle2Y + 20) paddle2Y += 4;
    if (ballY < paddle2Y) paddle2Y -= 4;
    paddle2Y = constrain(paddle2Y, 0, 200);
    // Move ball
    ballX += ballDX;
    ballY += ballDY;
    // Bounce walls
    if (ballY <= 0 || ballY >= 240) ballDY = -ballDY;
    // Bounce paddles
    if (ballX <= 10 && ballY > paddle1Y && ballY < paddle1Y + 40) ballDX = -ballDX;
    if (ballX >= 230 && ballY > paddle2Y && ballY < paddle2Y + 40) ballDX = -ballDX;
    // Score
    if (ballX < 0) { score2++; ballX = 120; ballY = 120; ballDX = 2; }
    if (ballX > 240) { score1++; ballX = 120; ballY = 120; ballDX = -2; }
  }
  // Draw
  pycamera.fb->fillScreen(0);
  // Paddles
  pycamera.fb->fillRect(5, paddle1Y, 5, 40, 0xFFFF);
  pycamera.fb->fillRect(230, paddle2Y, 5, 40, 0xFFFF);
  // Ball
  pycamera.fb->fillRect(ballX, ballY, 5, 5, 0xFFFF);
  // Scores
  pycamera.fb->setCursor(50, 10);
  pycamera.fb->print(score1);
  pycamera.fb->setCursor(180, 10);
  pycamera.fb->print(score2);
  pycamera.blitFrame();
  if (pycamera.justPressed(AWEXP_BUTTON_SEL)) currentMode = MODE_MENU; // Exit
}
// Snake mode
void snakeMode() {
  if (millis() - lastSnakeMove > snakeSpeed) {
    lastSnakeMove = millis();
    // Move snake
    for (int i = snakeLength - 1; i > 0; i--) {
      snake[i] = snake[i-1];
    }
    if (snakeDir == 0) snake[0].x += 10;
    if (snakeDir == 1) snake[0].y += 10;
    if (snakeDir == 2) snake[0].x -= 10;
    if (snakeDir == 3) snake[0].y -= 10;
    // Wrap around
    if (snake[0].x >= 240) snake[0].x = 0;
    if (snake[0].x < 0) snake[0].x = 240;
    if (snake[0].y >= 240) snake[0].y = 0;
    if (snake[0].y < 0) snake[0].y = 240;
    // Eat food
    if (snake[0].x == food.x && snake[0].y == food.y) {
      snakeLength++;
      food.x = random(24)*10;
      food.y = random(24)*10;
      pycamera.speaker_tone(440, 50);
    }
    // Collision with self
    for (int i = 1; i < snakeLength; i++) {
      if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
        snakeLength = 5; // Reset
        pycamera.speaker_tone(100, 200);
      }
    }
  }
  // Controls
  if (pycamera.justPressed(AWEXP_BUTTON_RIGHT)) snakeDir = 0;
  if (pycamera.justPressed(AWEXP_BUTTON_DOWN)) snakeDir = 1;
  if (pycamera.justPressed(AWEXP_BUTTON_LEFT)) snakeDir = 2;
  if (pycamera.justPressed(AWEXP_BUTTON_UP)) snakeDir = 3;
  // Draw
  pycamera.fb->fillScreen(0);
  for (int i = 0; i < snakeLength; i++) {
    pycamera.fb->fillRect(snake[i].x, snake[i].y, 10, 10, 0x07E0);
  }
  pycamera.fb->fillRect(food.x, food.y, 10, 10, 0xF800);
  pycamera.fb->setCursor(10, 10);
  pycamera.fb->print("Length: "); pycamera.fb->print(snakeLength);
  pycamera.blitFrame();
  if (pycamera.justPressed(AWEXP_BUTTON_SEL)) currentMode = MODE_MENU;
}
// Home Assistant placeholder
void homeAssistantMode() {
  pycamera.captureFrame();
  // Motion detection only in security mode
  if (securityMode && prev_buffer) {
    uint16_t *curr = (uint16_t *)pycamera.fb->getBuffer();
    long total_diff = 0;
    long sum_x = 0;
    long sum_y = 0;
    int step = 2; // Subsample for efficiency (balance speed and accuracy)
    int pix_threshold = 20; // Lowered from 30 for better sensitivity
    for (int y = 0; y < 240; y += step) {
      for (int x = 0; x < 240; x += step) {
        uint16_t p1 = prev_buffer[y * 240 + x];
        uint16_t p2 = curr[y * 240 + x];
        int r1 = (p1 >> 11) & 0x1F;
        int g1 = (p1 >> 5) & 0x3F;
        int b1 = p1 & 0x1F;
        int r2 = (p2 >> 11) & 0x1F;
        int g2 = (p2 >> 5) & 0x3F;
        int b2 = p2 & 0x1F;
        int pix_diff = abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2);
        if (pix_diff > pix_threshold) {
          sum_x += (long)x * pix_diff;
          sum_y += (long)y * pix_diff;
          total_diff += pix_diff;
        }
      }
    }
    int num_pixels = (240 / step) * (240 / step);
    float avg_diff = (float)total_diff / (num_pixels * 3.0 * 31.0); // Normalized (adjust threshold as needed)
    Serial.printf("Average diff: %.2f\n", avg_diff); // Added for debugging
    if (total_diff > 0) {
      int cx = sum_x / total_diff;
      int cy = sum_y / total_diff;
      Serial.printf("Motion blob center at (%d, %d)\n", cx, cy);
    }
    if (avg_diff > 0.05 && (millis() - last_snap_time > SNAP_COOLDOWN)) { // Lowered threshold from 0.2 for better sensitivity
      Serial.println("High motion detected! Taking snapshot...");
      sendI2CCommandTo(ARDUINO_ADDR, "High motion detected! Taking snapshot...");
      takeAndSendPhoto(0);
      last_snap_time = millis();
    }
  }
  memcpy(prev_buffer, pycamera.fb->getBuffer(), 240 * 240 * sizeof(uint16_t));
  // --- LIVE GYRO DATA DISPLAY ---
  float x, y, z;
  if (pycamera.readAccelData(&x, &y, &z)) {
    // Positioning text at the top of the frame
    Serial.printf("ACCEL: X=%0.2f, Y=%0.2f, Z=%0.2f\n", x, y, z);
    pycamera.fb->setCursor(10, 10);
    pycamera.fb->setTextColor(0x780F); // Your favorite Purple color!
    pycamera.fb->printf("X:%0.1f Y:%0.1f Z:%0.1f", x, y, z);
  }
  // Green object tracking if enabled
  if (tracking) {
    trackGreenObject();
  }
  // Check scheduled events
  checkScheduledEvents();
  // Trigger snapshot with the Shutter button
  if (pycamera.justPressed(SHUTTER_BUTTON)) {
    Serial.println("Taking Snapshot...");
    takeAndSendPhoto(0);
  }
  // Check for serial commands
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "snap") {
      Serial.println("Serial snap command received!");
      takeAndSendPhoto(0);
    }
  }
  // Poll Telegram for new messages
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    handleNewMessages(numNewMessages);
    bot_lasttime = millis();
  }
  pycamera.blitFrame();
  if (pycamera.justPressed(AWEXP_BUTTON_SEL)) currentMode = MODE_MENU;
}
void sendI2CCommandTo(uint8_t addr, const char* cmd) {
  Wire.beginTransmission(addr);
  Wire.write((const uint8_t*)cmd, strlen(cmd));
  Wire.endTransmission();
}
// Helper function to send Telegram messages
// Centralizes bot.sendMessage calls for easy parameter modification
void sendTelegramMessage(String chat_id, String message, int reply_to_message_id) {
  bot.sendMessage(chat_id, message, "", 0, reply_to_message_id);
}
void checkScheduledEvents() {
  time_t now = time(nullptr);
  for (auto it = scheduledEvents.begin(); it != scheduledEvents.end(); ) {
    if (now >= it->eventTime && !it->triggered) {
      if (it->arduinoCmd != "none") {
        sendI2CCommandTo(ARDUINO_ADDR, it->arduinoCmd.c_str());
        Serial.printf("Sent command '%s' to Arduino\n", it->arduinoCmd.c_str());
      }
      if (!it->reminder.isEmpty()) {
        sendTelegramMessage(CHAT_ID, it->reminder);
      }
      it->triggered = true;
      it = scheduledEvents.erase(it); // Remove after trigger
    } else {
      ++it;
    }
  }
}
bool parseSchedule(String text, String chat_id) {
  // Split by lines
  String lines[5];
  int idx = 0;
  int pos = 0;
  while (idx < 5) {
    int nl = text.indexOf('\n', pos);
    if (nl == -1) {
      lines[idx] = text.substring(pos);
      break;
    }
    lines[idx] = text.substring(pos, nl);
    pos = nl + 1;
    idx++;
  }
  String timeStr, dateStr, details, arduinoCmd, reminder;
  for (int i = 0; i <= idx; i++) {
    String line = lines[i];
    line.trim();
    if (line.startsWith("Time:")) {
      timeStr = line.substring(5);
      timeStr.trim();
    } else if (line.startsWith("Date:")) {
      dateStr = line.substring(5);
      dateStr.trim();
    } else if (line.startsWith("Details:")) {
      details = line.substring(8);
      details.trim();
    } else if (line.startsWith("Command:")) {
      arduinoCmd = line.substring(8);
      arduinoCmd.trim();
    } else if (line.startsWith("Reminder:")) {
      reminder = line.substring(9);
      reminder.trim();
    }
  }
  if (timeStr.isEmpty() || dateStr.isEmpty()) {
    return false;
  }
  // Parse date and time - support both MM/DD/YYYY and DD/MM/YYYY
  struct tm tm = {0};
  int day, month, year;
  if (sscanf(dateStr.c_str(), "%d/%d/%d", &month, &day, &year) != 3) {
    return false;
  }
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  int hour, min;
  char ampm[3];
  if (sscanf(timeStr.c_str(), "%d:%d %2s", &hour, &min, ampm) != 3) {
    return false;
  }
  if (strcasecmp(ampm, "pm") == 0 && hour < 12) hour += 12;
  else if (strcasecmp(ampm, "am") == 0 && hour == 12) hour = 0;
  tm.tm_hour = hour;
  tm.tm_min = min;
  tm.tm_sec = 0;
  time_t eventTime = mktime(&tm);
  Event ev;
  ev.eventTime = eventTime;
  ev.details = details;
  ev.arduinoCmd = arduinoCmd;
  ev.reminder = reminder;
  scheduledEvents.push_back(ev);
  return true;
}
void trackGreenObject() {
  uint16_t *fb = (uint16_t *)pycamera.fb->getBuffer();
  int minx = 239, maxx = 0, miny = 239, maxy = 0;
  bool found = false;
  for (int y = 0; y < 240; y++) {
    for (int x = 0; x < 240; x++) {
      uint16_t pix = fb[y * 240 + x];
      uint8_t r = ((pix >> 11) & 0x1F) << 3;
      uint8_t g = ((pix >> 5) & 0x3F) << 2;
      uint8_t b = (pix & 0x1F) << 3;
      // Green detection threshold (adjust as needed)
      if (g > 100 && g > r + 50 && g > b + 50) {
        found = true;
        if (x < minx) minx = x;
        if (x > maxx) maxx = x;
        if (y < miny) miny = y;
        if (y > maxy) maxy = y;
      }
    }
  }
  if (found && (maxx - minx > 10) && (maxy - miny > 10)) {
    int cx = (minx + maxx) / 2;
    int cy = (miny + maxy) / 2;
    // Draw bounding box (red)
    pycamera.fb->drawRect(minx, miny, maxx - minx + 1, maxy - miny + 1, 0xF800);
    // Send position to Arduino via I2C
    Wire.beginTransmission(ARDUINO_ADDR);
    Wire.write((uint8_t)cx);
    Wire.write((uint8_t)cy);
    Wire.endTransmission();
    Serial.printf("Green object at (%d, %d)\n", cx, cy);
  }
}
void sendDanceCommand() {
  sendI2CCommandTo(ARDUINO_ADDR, "dance");
  Serial.println("Sent 'dance' command to Arduino");
}
void takeAndSendPhoto(int reply_to_message_id) {
  pycamera.setNeopixel(0x800080); // Purple flash
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    if (reply_to_message_id != 0) {
      sendTelegramMessage(CHAT_ID, "❌ Camera capture failed!", reply_to_message_id);
    }
    return;
  }
  fb_length = fb->len;
  fb_buffer = fb->buf;
  currentByte = 0;
  Serial.println("Sending to Telegram...");
  // Note: UniversalTelegramBot's sendPhotoByBinary doesn't support reply_to_message_id directly
  // The photo itself won't be a reply, but we send a confirmation message as a reply
  if (bot.sendPhotoByBinary(CHAT_ID, "image/jpeg", fb->len,
                            isMoreDataAvailable, photoNextByte,
                            nullptr, nullptr)) {
    Serial.println("Photo sent successfully!");
    if (reply_to_message_id != 0) {
      sendTelegramMessage(CHAT_ID, "✅ Photo captured and sent!", reply_to_message_id);
    }
  } else {
    Serial.println("Telegram upload failed.");
    if (reply_to_message_id != 0) {
      sendTelegramMessage(CHAT_ID, "❌ Failed to send photo!", reply_to_message_id);
    }
  }
  esp_camera_fb_return(fb);
  pycamera.setNeopixel(0x000000);
}
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    int message_id = bot.messages[i].message_id; // Extract message_id for reply tracking
  
    // Process messages from authorized user OR messages starting with "app_" prefix
    if (chat_id != CHAT_ID && !text.startsWith("app_")) continue;
    // Remove "app_" prefix if present
    if (text.startsWith("app_")) {
      text = text.substring(4); // Remove "app_" (4 characters)
    }
   // text.toLowerCase(); // Make case-insensitive
    // Command handling with reply tracking
    if (text == "send me a pic" || text == "/pic" || text == "pic") {
      Serial.println("Telegram pic command received!");
      takeAndSendPhoto(message_id);
    } else if (text == "/record" || text == "record") {
      Serial.println("Telegram record command received!");
      sendTelegramMessage(chat_id, "🎤 Recording audio...", message_id);
      recordAudio();
    } else if (text == "play" || text == "letsplay" || text == "/letsplay") {
      Serial.println("Telegram play command received!");
      sendTelegramMessage(chat_id, "🔊 Playing audio...", message_id);
      playAudio();
    } else if (text == "/letsplay" || text == "letsplay") {
      tracking = true;
      sendTelegramMessage(chat_id, "🎮 Tracking started! Let's play!", message_id);
      Serial.println("Tracking enabled!");
    } else if (text == "/stopdance" || text == "stopdance") {
      tracking = false;
      sendTelegramMessage(chat_id, "🛑 Dance stopped!", message_id);
      sendI2CCommandTo(ARDUINO_ADDR, "stopdance");
      sendI2CCommandTo(ARDUINO2_ADDR, "stop");
      Serial.println("stopdance");
    } else if (text == "stop") {
      tracking = false;
      securityMode = false;
      sendTelegramMessage(chat_id, "🛑 All commands stopped!", message_id);
      sendI2CCommandTo(ARDUINO_ADDR, "stop");
      sendI2CCommandTo(ARDUINO2_ADDR, "stop");
      sendI2CCommandTo(ARDUINO2_ADDR, "wake");
      Serial.println("stop");
    } else if (text == "dance" || text == "/dance") {
      sendDanceCommand();
      sendTelegramMessage(chat_id, "💃 Dance mode activated!", message_id);
      sendI2CCommandTo(ARDUINO2_ADDR, "exp1");
      sendI2CCommandTo(ARDUINO_ADDR, "dance");
    } else if (text == "/securitymode" || text == "securitymode") {
      securityMode = true;
      sendTelegramMessage(chat_id, "🔒 Security mode enabled! Monitoring for motion...", message_id);
      sendI2CCommandTo(ARDUINO_ADDR, "Secure");
      sendI2CCommandTo(ARDUINO2_ADDR, "secure");
      Serial.println("Security mode enabled!");
    } else if (text == "/iamhome" || text == "iamhome") {
      securityMode = false;
      sendTelegramMessage(chat_id, "🏠 Welcome home! Security mode disabled.", message_id);
      sendI2CCommandTo(ARDUINO_ADDR, "Security mode disabled!");
      Serial.println("Security mode disabled!");
      sendI2CCommandTo(ARDUINO2_ADDR, "wake");
      sendI2CCommandTo(ARDUINO_ADDR, "wakeup");
      sendI2CCommandTo(ARDUINO_ADDR, "stop");
    } else if (text == "lighton") {
      sendControlCommand("light_on");
      sendTelegramMessage(chat_id, "💡 Light turned on!", message_id);
      Serial.println("Light on command sent");
    } else if (text == "lightoff") {
      sendControlCommand("light_off");
      sendTelegramMessage(chat_id, "🌙 Light turned off!", message_id);
      Serial.println("Light off command sent");
    } else if (text == "fanon") {
      sendControlCommand("fan_on");
      sendTelegramMessage(chat_id, "🪭 Fan turned on!", message_id);
      Serial.println("Fan on command sent");
    } else if (text == "fanoff") {
      sendControlCommand("fan_off");
      sendTelegramMessage(chat_id, "✋ Fan turned off!", message_id);
      Serial.println("Fan off command sent");
    } else if (text == "ping" || text == "hi") {
      sendTelegramMessage(chat_id, "pong", message_id);
    } else if (text == "schedule" || text == "/schedule") {
      sendTelegramMessage(chat_id, "📅 Please schedule an event in this format:\nTime: 12:00 pm\nDate: 2/3/2026\nDetails: \"i have a meeting to attend\"\nCommand: \"medicine_slot_08\" or \"none\"\nReminder: \"reminder text\"", message_id);
      awaitingSchedule = true;
    } else if (text.startsWith("/instantschedule ") || text.startsWith("instantschedule ")) {
      String scheduleData = text.substring(17); // Extract text after "/instantschedule "
      scheduleData.trim();
      if (scheduleData.length() > 0) {
        if (parseSchedule(scheduleData, chat_id)) {
          sendTelegramMessage(chat_id, "✅ Event scheduled successfully!", message_id);
        } else {
          sendTelegramMessage(chat_id, "❌ Failed to schedule event. Check format.", message_id);
        }
      } else {
        sendTelegramMessage(chat_id, "❌ Please provide schedule details after the command.", message_id);
      }
    } else if (text == "sleep") {
      sendI2CCommandTo(ARDUINO2_ADDR, "sleep");
      sendI2CCommandTo(ARDUINO_ADDR, "sleep");
      sendTelegramMessage(chat_id, "😴 Sleep mode enabled", message_id);
    } else if (text == "wakeup") {
      sendI2CCommandTo(ARDUINO2_ADDR, "wake");
      sendTelegramMessage(chat_id, "👋 Waking up the robot!", message_id);
      sendI2CCommandTo(ARDUINO_ADDR, "wakeup");
    } else if (text == "exp1") {
      sendI2CCommandTo(ARDUINO2_ADDR, "exp1");
      sendTelegramMessage(chat_id, " Expression changed ", message_id);
    } else if (text == "exp2") {
      sendI2CCommandTo(ARDUINO2_ADDR, "exp2");
      sendTelegramMessage(chat_id, "😊 Expression changed to normal", message_id);
    } else if (awaitingSchedule) {
      if (parseSchedule(text, chat_id)) {
        sendTelegramMessage(chat_id, "✅ Event scheduled successfully!", message_id);
        awaitingSchedule = false;
      } else {
        sendTelegramMessage(chat_id, "❌ Failed to parse schedule. Please try again.", message_id);
      }
    }
  }
}
void recordAudio() {
  const int sampleRate = 8000;
  const int duration = 5;
  int numSamples = sampleRate * duration;
  uint16_t *samples = (uint16_t*)malloc(numSamples * sizeof(uint16_t));
  if (!samples) {
    Serial.println("Failed to allocate samples!");
    return;
  }
  unsigned long last = micros();
  for (int i = 0; i < numSamples; i++) {
    while (micros() - last < (1000000UL / sampleRate));
    last += (1000000UL / sampleRate);
    samples[i] = analogRead(MIC);
  }
  File file = pycamera.sd.open("last_voice.raw", FILE_WRITE);
  if (file) {
    file.write((uint8_t*)samples, numSamples * sizeof(uint16_t));
    file.close();
    Serial.println("Audio recorded and saved!");
  } else {
    Serial.println("Failed to open file for writing!");
  }
  free(samples);
}
void playAudio() {
  const int sampleRate = 8000;
  File file = pycamera.sd.open("last_voice.raw", FILE_READ);
  if (!file) {
    Serial.println("Failed to open file for reading!");
    return;
  }
  size_t size = file.size();
  if (size == 0) {
    file.close();
    return;
  }
  uint16_t *samples = (uint16_t*)malloc(size);
  if (!samples) {
    Serial.println("Failed to allocate samples!");
    file.close();
    return;
  }
  file.read((uint8_t*)samples, size);
  file.close();
  int numSamples = size / sizeof(uint16_t);
  // Configure LEDC channel
  ledc_channel_config_t chan_conf = {
      .gpio_num = SPEAKER,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0,
      .flags = { .output_invert = 0 }
  };
  ESP_ERROR_CHECK(ledc_channel_config(&chan_conf));
  // Unmute speaker
  pycamera.aw.digitalWrite(AWEXP_SPKR_SD, HIGH);
  unsigned long last = micros();
  for (int i = 0; i < numSamples; i++) {
    while (micros() - last < (1000000UL / sampleRate));
    last += (1000000UL / sampleRate);
    uint32_t duty = samples[i] >> 4; // Scale 12-bit to 8-bit
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
  }
  // Stop and mute
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
  pycamera.aw.digitalWrite(AWEXP_SPKR_SD, LOW);
  // Reset pin
  gpio_reset_pin((gpio_num_t)SPEAKER);
  free(samples);
  Serial.println("Audio playback complete!");
}
// New function to send HTTP requests to the control ESP32
void sendControlCommand(String endpoint) {
  WiFiClient httpClient;
  if (httpClient.connect(controllerIP, 80)) {
    httpClient.print(String("GET /") + endpoint + " HTTP/1.1\r\n" +
                     "Host: " + controllerIP + "\r\n" +
                     "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (httpClient.connected() && millis() - timeout < 5000) {
      if (httpClient.available()) {
        String line = httpClient.readStringUntil('\n');
        // You can process the response if needed, but for now, we just send the request
      }
    }
    httpClient.stop();
    Serial.println("Command sent to control ESP32: " + endpoint);
  } else {
    Serial.println("Failed to connect to control ESP32");
  }
}
