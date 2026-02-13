# ESP32 PyCamera Home Assistant Project

![Robot Image](Digi_home.jpg)

## Overview

This project transforms an Adafruit PyCamera (ESP32-S3) into a powerful smart home assistant, security camera, gaming console, and Telegram-controlled robot brain. It features live camera preview, motion-triggered security snapshots, photo capture, audio recording/playback, simple games, and full Telegram remote control. The device communicates with external Arduinos via I2C to control lights, fans, motors (dance/sleep/expressions), and other appliances.

**Key Technologies:**
- ESP32-S3 with OV5640 camera
- Adafruit PyCamera library
- Telegram Bot API
- I2C master for controlling one or two slave Arduinos
- NTP time sync (IST timezone supported)

Licensed under GNU GPL v3.

## Features

### 1. **Modes & Navigation**
- Clean menu system using UP/DOWN/OK/SEL buttons
- Modes: Camera | Games | Home Assistant
- Idle mode shows live camera preview

### 2. **Camera Mode**
- Live preview on display
- Adjustable resolution (UP/DOWN)
- Special effects (LEFT/RIGHT)
- Shutter button takes and saves photos to SD card

### 3. **Games**
- **Snake** – Classic game with wrap-around, score display
- **Ping Pong** – Player vs simple AI, score tracking

### 4. **Home Assistant Mode** (Main operating mode)
- **Security Mode** (`/securitymode`): Motion detection with automatic photo capture and Telegram alert (5-second cooldown)
- **Live Accelerometer Display** on screen (X/Y/Z values)
- **Audio Record & Play** (5-second clips via Telegram `/record` and `play`)
- **Event Scheduling** via Telegram (date, time, Arduino command, reminder)
- **Full appliance & robot control** via Telegram:
  - `lighton` / `lightoff`
  - `fanon` / `fanoff`
  - `dance` → activates dance routine on robot
  - `sleep` / `wakeup`
  - `exp1`, `exp2` → change facial expression (second Arduino)
  - `stop` → emergency stop everything
  - `/iamhome` → disable security mode + welcome routine
- **Manual snapshot** anytime via shutter button or Telegram `/pic`

## Hardware Requirements
- Adafruit PyCamera (Qualia ESP32-S3)
- Formatted SD card
- WiFi connection
- One or two slave Arduinos (addresses 0x08 and 0x09) for controlling lights, fans, motors, etc.
- Microphone on GPIO20, speaker on GPIO18(Bt defaiult adafruit memento has this in bydefault)

## Required Libraries (Install via Arduino Library Manager)

1. **Adafruit PyCamera** → Search "Adafruit PyCamera"
2. **UniversalTelegramBot** → Brian Lough
3. **ArduinoJson** → Benoit Blanchon (v6.x)
4. **NTPClient** → Fabrice Weinberg
5. **SdFat** → (usually installed with PyCamera library)

ESP32 board package by Espressif must be installed.

## Setup Instructions

1. Fill in your credentials in the code:
   ```cpp
   const char* ssid = "YourWiFi";
   const char* password = "YourPassword";
   #define BOTtoken "YourBotToken"
   #define CHAT_ID "YourChatID"
   ```

2. Upload to PyCamera (select correct ESP32-S3 board in Arduino IDE)

3. Create Telegram bot with @BotFather → get token  
   Start chat with your bot → send any message → use @userinfobot to get your CHAT_ID

4. Insert SD card

5. Power on → device connects to WiFi and is ready

## Telegram Commands (all case-insensitive)

- `/pic` or `send me a pic` → take and send photo
- `/record` → record 5-second audio
- `play` → play last recorded audio
- `/securitymode` → enable motion detection security
- `/iamhome` → disable security + welcome routine
- `lighton` / `lightoff`
- `fanon` / `fanoff`
- `dance` → robot dance mode
- `stop` → stop all movement
- `sleep` → sleep mode
- `wakeup` → wake robot
- `exp1`, `exp2` → change expression
- `/schedule` → shows scheduling format
- `/instantschedule ...` → one-line scheduling
- `ping` or `hi` → pong response

## Scheduling Format (multi-line message after /schedule)

```
Time: 7:30 pm
Date: 15/2/2026
Details: Take medicine
Command: medicine_slot_08
Reminder: Time to take medicine!
```

or use `/instantschedule` + same text in one line.

## Notes & Tips

- Motion sensitivity is tuned for indoor use (adjust `pix_threshold` and `avg_diff > 0.05` if needed)
- Security mode only active in Home Assistant mode
- All photos saved to SD card as well as sent to Telegram
- Serial monitor (115200 baud) shows detailed debug info
- Press SEL button anytime to return to main menu

Enjoy your fully Telegram-controlled smart home robot camera! 🚀

I am Vikas 
I Love Robotics ❤️
