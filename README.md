# App-Controlled-Mood-Lamp

# App-Controlled Mood Lamp with ESP32

This project controls an RGB LED strip (WS2812 or similar) using the **ESP32** and a custom **Blynk** app for an app-controlled mood lamp. You can change the color and brightness of the LED strip directly from your smartphone.

## Features
- Control color using buttons in the app (Red, Green, Blue, Yellow, Purple, Cyan).
- Adjust brightness using a slider in the app.
- Bluetooth connectivity using **ESP32**.

## Components Used
- **ESP32 Development Board**
- **WS2812 RGB LED Strip** (or similar)
- **Blynk App** on smartphone
- **Power Supply** for the ESP32 and LED strip

## Getting Started

### 1. Install Libraries:
- **Adafruit NeoPixel** (for controlling WS2812 RGB LED Strip)
- **ESP32 BLE Libraries** (for Bluetooth Low Energy communication)

You can install these libraries via the Arduino IDE Library Manager.

### 2. Upload Code to ESP32:
- Open the provided Arduino code in the Arduino IDE.
- Select the correct **ESP32 board** from the Tools menu.
- Connect your ESP32 to your computer and upload the code.

### 3. Blynk App Setup:
- Create a new project in the **Blynk App**.
- Choose **ESP32** as the board and **Bluetooth** as the connection type.
- Add buttons for controlling colors and a slider for brightness.

### 4. Run the Project:
- Pair your ESP32 with the Blynk app via Bluetooth.
- Control the color and brightness of the LED strip.


