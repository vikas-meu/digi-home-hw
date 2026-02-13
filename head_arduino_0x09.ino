#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Servo.h>
#include <Wire.h>

// ================= I2C ADDRESS =================
#define I2C_ADDR 0x09

// ================= LED MATRIX =================
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// ================= SERVOS =================
#define LEFT_SERVO_PIN 6
#define RIGHT_SERVO_PIN 3
Servo leftServo;
Servo rightServo;
int currentPos = 45;

// ================= MODES =================
enum Mode {
  MODE_DEFAULT,
  MODE_SAD,
  MODE_HAPPY,
  MODE_SLEEP,
  MODE_SECURE
};

Mode currentMode = MODE_DEFAULT;
bool servoEnabled = true;
unsigned long sleepStartTime = 0;
bool sleepMessageShown = false;

// ================= EYE PATTERNS =================

// OPEN
const uint8_t eye_open[8] = {
  0b00000000,
  0b00111100,
  0b01111110,
  0b11100111,
  0b11100111,
  0b01111110,
  0b00111100,
  0b00000000
};

// SAD (drooping bottom)
const uint8_t eye_sad[8] = {
  0b00000111,
  0b00001110,
  0b00111000,
  0b00011100,
  0b00001110,
  0b00011100,
  0b00111000,
  0b01100000
};

// HAPPY (bigger arc)
const uint8_t eye_happy[8] = {
  0b00000000,
  0b00000000,
  0b01111110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00000000,
  0b00000000
};

// CLOSED
const uint8_t eye_closed[8] = {
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000
};

// SECURE (circle + center dot)
const uint8_t eye_secure[8] = {
  0b00000000,
  0b00111100,
  0b01100110,
  0b10011001,
  0b10011001,
  0b01100110,
  0b00111100,
  0b00000000
};

// ================= SETUP =================
void setup() {
  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 4);

  randomSeed(analogRead(0));
  Serial.begin(115200);

  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  leftServo.write(currentPos);
  rightServo.write(90 - currentPos);

  // I2C SLAVE START
  Wire.begin(I2C_ADDR);
  Wire.onReceive(receiveEvent);

  Serial.println("Robot Eyes Ready (I2C 0x09)");
}

// ================= DISPLAY =================
void displayEyes(const uint8_t *pattern) {
  mx.clear();
  for (uint8_t col = 0; col < 8; col++) {
    mx.setColumn(col, pattern[col]);
    mx.setColumn(col + 24, pattern[col]);
  }
  mx.update();
}

// ================= SERVO =================
void smoothMove(int targetPos) {
  if (!servoEnabled) return;

  int step = (targetPos > currentPos) ? 1 : -1;
  while (currentPos != targetPos) {
    currentPos += step;
    leftServo.write(currentPos);
    rightServo.write(90 - currentPos);
    delay(15);
  }
}

// ================= COMMAND HANDLER =================
void handleCommand(String cmd) {
  cmd.trim();

  if (cmd == "exp1") {
    currentMode = MODE_SAD;
  }
  else if (cmd == "exp2") {
    currentMode = MODE_HAPPY;
  }
  else if (cmd == "sleep") {
    currentMode = MODE_SLEEP;
    servoEnabled = false;
    sleepStartTime = millis();
    sleepMessageShown = false;
  }
  else if (cmd == "secure") {
    currentMode = MODE_SECURE;
    servoEnabled = false;
  }
  else if (cmd == "wake") {
    currentMode = MODE_DEFAULT;
    servoEnabled = true;
    mx.control(MD_MAX72XX::SHUTDOWN, false);
  }
}

// ================= I2C RECEIVE =================
void receiveEvent(int howMany) {
  String received = "";
  while (Wire.available()) {
    char c = Wire.read();
    received += c;
  }
  handleCommand(received);
}

// ================= LOOP =================
unsigned long lastBlinkTime = 0;
unsigned long lastServoTime = 0;

void loop() {

  // SERIAL COMMAND SUPPORT
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    handleCommand(cmd);
  }

  switch (currentMode) {

    case MODE_DEFAULT:
      displayEyes(eye_open);

      if (millis() - lastBlinkTime > random(2000, 5000)) {
        displayEyes(eye_closed);
        delay(150);
        displayEyes(eye_open);
        lastBlinkTime = millis();
      }

      if (millis() - lastServoTime > random(1000, 5000)) {
        smoothMove(random(0, 91));
        lastServoTime = millis();
      }
      break;

    case MODE_SAD:
      displayEyes(eye_sad);
      break;

    case MODE_HAPPY:
      displayEyes(eye_happy);
      break;

    case MODE_SLEEP:
      displayEyes(eye_closed);

      if (!sleepMessageShown && millis() - sleepStartTime > 10000) {
        Serial.println("Going to sleep...");
        mx.control(MD_MAX72XX::SHUTDOWN, true);  // turn off LEDs
        sleepMessageShown = true;
      }
      break;

    case MODE_SECURE:
      displayEyes(eye_secure);
      break;
  }
}
