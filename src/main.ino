#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define PIN 6  // Pin for the LED strip
#define NUMPIXELS 30  // Number of LEDs (adjust according to your strip)

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// BLE server setup
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

int red = 0, green = 0, blue = 0, brightness = 255; // Default to full brightness

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();  // Initialize the LED strip

  // Initialize BLE
  BLEDevice::init("MoodLamp");
  pServer = BLEDevice::createServer();

  pCharacteristic = pServer->createCharacteristic(
                      BLEUUID((uint16_t)0xFFE1),
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pServer->getAdvertising()->start();
  Serial.println("Waiting for client to connect...");
}

void loop() {
  std::string value = pCharacteristic->getValue();

  if (value.length() >= 2) {  // Ensure at least 2 bytes (color + brightness)
    char color = value[0];  
    int brightnessLevel = value[1];  
    
    // Update global brightness variable
    brightness = brightnessLevel;

    // Set color based on received value
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
}

void setColor(int r, int g, int b) {
  red = r;
  green = g;
  blue = b;
  applyBrightness();  // Adjust brightness immediately
}

void applyBrightness() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int r = (red * brightness) / 255;
    int g = (green * brightness) / 255;
    int b = (blue * brightness) / 255;

    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
