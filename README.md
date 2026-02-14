# Project Title

## Overview
This repository contains the hardware and software components for the Digi Home project. It includes detailed instructions for setup, usage, and contribution.

## Bill of Materials
- Arduino Uno
- Arduino Mega
- ESP32 Module
- Relay Module
- LED Matrix
- Servo Motors
- Jumper Wires
- Breadboards

## Hardware Architecture
The hardware architecture consists of multiple Arduino slave boards communicating with a master board. 

### Components:
- **Base_trigger.ino**: Responsible for body and servo control.
- **head_arduino_0x09.ino**: Manages facial expressions using LED matrix and eye patterns.
- **esp32_relay_module.ino**: Controls appliances via relay module.

## Software Components
- Arduino IDE for programming Arduino boards.
- Libraries for various sensors and actuators.

## Setup Instructions
1. Clone the repository using `git clone https://github.com/vikas-meu/digi-home-hw.git`
2. Open the Arduino IDE and upload the corresponding `.ino` files to the respective boards.
3. Connect the components as per the hardware architecture diagram provided.
4. Ensure your ESP32 is connected to the internet for Telegram integrations.

## Repository Structure
- `Base_trigger.ino`: Body/Servo control code.
- `head_arduino_0x09.ino`: Facial expression control code.
- `esp32_relay_module.ino`: Appliance control code.
- `README.md`: Documentation for the project.

## Telegram Commands Documentation
- `/start`: Initializes the bot.
- `/control`: Control appliances connected to the ESP32.
- `/status`: Get the status of connected devices.

## Troubleshooting
- If the servo is not responding, check power connections.
- Ensure the Arduino is correctly uploaded with the script.
- If the Telegram bot is not responding, check the network connection of ESP32.

## Contribution Guidelines
1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/YourFeature`
3. Commit your changes: `git commit -m 'Add some feature'`
4. Push to the branch: `git push origin feature/YourFeature`
5. Create a pull request.  

Feel free to reach out for any questions or clarifications.