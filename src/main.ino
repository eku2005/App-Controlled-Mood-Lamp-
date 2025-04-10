#include <BlynkSimpleEsp32BLE.h>  // Include Blynk library for BLE
#include <Adafruit_NeoPixel.h>

#define PIN 6  // Pin for the LED strip
#define NUMPIXELS 30  // Number of LEDs (adjust according to your strip)

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Blynk authentication token
char auth[] = "YourAuthToken";  // Replace with your Blynk auth token

// Blynk virtual pins for controlling the LEDs
#define VIRTUAL_COLOR_PIN V0  // Virtual pin to set color (R, G, B, etc.)
#define VIRTUAL_BRIGHTNESS_PIN V1  // Virtual pin to set brightness

int red = 0, green = 0, blue = 0, brightness = 255;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();  // Initialize the LED strip

  // Initialize Blynk BLE
  Blynk.begin(auth);  // Connect to Blynk using BLE
}

void loop() {
  Blynk.run();  // Keep Blynk running

  // Check for color changes via virtual pin V0
  if (Blynk.virtualRead(VIRTUAL_COLOR_PIN)) {
    char color = Blynk.virtualRead(VIRTUAL_COLOR_PIN);
    updateColor(color);
  }

  // Check for brightness changes via virtual pin V1
  if (Blynk.virtualRead(VIRTUAL_BRIGHTNESS_PIN)) {
    int brightnessLevel = Blynk.virtualRead(VIRTUAL_BRIGHTNESS_PIN);
    brightness = brightnessLevel;
    applyBrightness();
  }
}

// Function to set color based on received data
void updateColor(char color) {
  if (color == 'R') {
    setColor(255, 0, 0);
  } else if (color == 'G') {
    setColor(0, 255, 0);
  } else if (color == 'B') {
    setColor(0, 0, 255);
  } else if (color == 'Y') {
    setColor(255, 255, 0);
  } else if (color == 'P') {
    setColor(255, 0, 255);
  } else if (color == 'C') {
    setColor(0, 255, 255);
  }
}

// Set the LED color
void setColor(int r, int g, int b) {
  red = r;
  green = g;
  blue = b;
  applyBrightness();  // Adjust brightness immediately
}

// Apply brightness to the LEDs
void applyBrightness() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int r = (red * brightness) / 255;
    int g = (green * brightness) / 255;
    int b = (blue * brightness) / 255;

    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
