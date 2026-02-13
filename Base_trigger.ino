#include <Servo.h>
#include <Wire.h>

#define ARDUINO_ADDR 0x08   // I2C slave address

Servo neckRoll;   // D3
Servo neckYaw;    // D5
Servo dispenser1; // D6
Servo dispenser2; // D9

const int NECK_MIN = 80;
const int NECK_MAX = 100;
const int NECK_MID = 90;
const int DISP_MIN = 0;
const int DISP_MAX = 90;

enum Mode { NORMAL, DANCE, SECURITY };
Mode currentMode = NORMAL;

unsigned long lastMotionTime = 0;
bool paused = false;

unsigned long lastRandomChange = 0;
unsigned long randomInterval = 5000;

int targetRoll = NECK_MID;
int targetYaw  = NECK_MID;

// Real position tracking
float currentRollPos = NECK_MID;
float currentYawPos  = NECK_MID;

// 🔑 I2C command handling (SAFE)
volatile bool newCommand = false;
String pendingCommand = "";

bool sleepMode = false;

/* ================= SETUP ================= */

void setup() {
  Serial.begin(115200);

  Wire.begin(ARDUINO_ADDR);
  Wire.onReceive(receiveEvent);

  neckRoll.attach(3);
  neckYaw.attach(5);
  dispenser1.attach(6);
  dispenser2.attach(9);

  neckRoll.write(NECK_MID);
  neckYaw.write(NECK_MID);
  dispenser1.write(DISP_MIN);
  dispenser2.write(DISP_MIN);

  randomSeed(analogRead(A0));
}

/* ================= LOOP ================= */

void loop() {

  // 🔹 Handle I2C command safely
  if (newCommand) {
    noInterrupts();
    String cmd = pendingCommand;
    newCommand = false;
    interrupts();

    handleCommand(cmd);
  }

  // Optional Serial control (for testing)
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    handleCommand(cmd);
  }

  if (paused) {
    if (millis() - lastMotionTime >= 2000) {
      paused = false;
    } else {
      return;
    }
  }

  if (sleepMode) {
    return;
  }

  switch (currentMode) {
    case NORMAL:
      aliveIdleMotion();
      break;
    case DANCE:
      dancePattern();
      break;
    case SECURITY:
      securitySweep();
      break;
  }
}

/* ================= I2C RECEIVE ================= */

void receiveEvent(int howMany) {
  pendingCommand = "";
  while (Wire.available()) {
    pendingCommand += (char)Wire.read();
  }
  pendingCommand.trim();
  newCommand = true;   // just signal loop()
}

/* ================= COMMAND HANDLER ================= */

void handleCommand(String cmd) {
  Serial.print("CMD: ");
  Serial.println(cmd);

  if (cmd == "dance" || cmd == "Dance" || cmd == "123") {
    currentMode = DANCE;
    paused = false;
  } 
  else if (cmd == "stopdance" || cmd == "000" || cmd == "stop") {
    currentMode = NORMAL;
    paused = false;
    sleepMode = false;
  } 
  else if (cmd == "Secure" || cmd == "secure") {
    currentMode = SECURITY;
    paused = false;
    neckYaw.write(NECK_MID);
  } 
  else if (cmd == "motion" || cmd == "move") {
    paused = true;
    lastMotionTime = millis();
  } 
  else if (cmd == "wakeup" || cmd == "stop") {
    currentMode = NORMAL;
    paused = false;
  } 
  else if (cmd == "slot_08" || cmd == "low") {
    dispense(dispenser2);   // D9
  } 
  else if (cmd == "medicine_slot_09" || cmd == "up") {
    dispense(dispenser1);   // D6
  }
  else if (cmd == "sleep") {
    sleepMode = true;
  }
  else if (cmd == "wakeup") {
    sleepMode = false;
  }
}

/* ================= DISPENSER ================= */

void dispense(Servo &servo) {
  for (int pos = DISP_MIN; pos <= DISP_MAX; pos++) {
    servo.write(pos);
    delay(10);
  }
  delay(10000);
  for (int pos = DISP_MAX; pos >= DISP_MIN; pos--) {
    servo.write(pos);
    delay(10);
  }
}

/* ================= ALIVE IDLE MOTION ================= */

void aliveIdleMotion() {
  if (millis() - lastRandomChange >= randomInterval) {
    targetRoll = random(NECK_MIN, NECK_MAX + 1);
    targetYaw  = random(NECK_MIN, NECK_MAX + 1);

    randomInterval = random(2000, 5000);
    lastRandomChange = millis();
  }

  currentRollPos += (targetRoll - currentRollPos) * 0.10;
  currentYawPos  += (targetYaw  - currentYawPos)  * 0.10;

  currentRollPos += random(-1, 2) * 0.03;
  currentYawPos  += random(-1, 2) * 0.03;

  neckRoll.write(constrain((int)currentRollPos, NECK_MIN, NECK_MAX));
  neckYaw.write(constrain((int)currentYawPos,  NECK_MIN, NECK_MAX));

  delay(15);
}

/* ================= DANCE ================= */

void dancePattern() {
  static int phase = 0;

  int bounceRoll = NECK_MID + 25 * sin(phase * PI / 180);
  int bounceYaw  = NECK_MID + 25 * cos(phase * PI / 180);

  neckRoll.write(constrain(bounceRoll, NECK_MIN, NECK_MAX));
  neckYaw.write(constrain(bounceYaw,  NECK_MIN, NECK_MAX));

  phase = (phase + 4) % 360;
  delay(25);
}

/* ================= SECURITY ================= */

void securitySweep() {
  static int angle = NECK_MIN;
  static int dir = 1;

  angle += dir;
  if (angle >= NECK_MAX || angle <= NECK_MIN) {
    dir = -dir;
  }

  neckRoll.write(angle);
  delay(200);
}
