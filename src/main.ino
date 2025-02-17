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

int red = 0, green = 0, blue = 0, brightness = 255;

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
  if (pCharacteristic->getValue().length() > 0) {
    char color = pCharacteristic->getValue()[0];  // Read first byte for color
    int brightnessLevel = pCharacteristic->getValue()[1];  // Read second byte for brightness
    
    // Update color and brightness based on received data
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
    
    adjustBrightness(brightnessLevel);
  }
}

void setColor(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void adjustBrightness(int brightnessLevel) {
  for (int i = 0; i < NUMPIXELS; i++) {
    int r = (strip.getPixelColor(i) >> 16) & 0xFF;
    int g = (strip.getPixelColor(i) >> 8) & 0xFF;
    int b = strip.getPixelColor(i) & 0xFF;

    r = map(brightnessLevel, 0, 255, 0, r);
    g = map(brightnessLevel, 0, 255, 0, g);
    b = map(brightnessLevel, 0, 255, 0, b);

    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
