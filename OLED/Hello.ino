#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LEDS_COUNT  6
#define LEDS_PIN    33
#define TOUCHPAD    14
#define BMP280_PIN  12
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_COUNT, LEDS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_BMP280 bmp; // I2C

bool touchState = false;
uint8_t currentColor = 0;

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(115200);

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); // Clear the buffer
  display.setTextColor(WHITE); // Set text color
}

void loop() {
  // Check touch sensor
  if (TouchSens() < 60) {
    touchState = !touchState;
    delay(350);
  }
  
  // Get temperature from BMP280 sensor
  float temperature = bmp.readTemperature();
  
  // Display touch state and temperature on Serial Monitor
  Serial.print("Touch State: ");
  Serial.println(touchState);
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Update LEDs based on touch state and temperature
  if (touchState) {
    if (temperature < 30) {
      for (int i = 0; i < LEDS_COUNT; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green color
      }
    } else {
      for (int i = 0; i < LEDS_COUNT; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red color
      }
    }
  } else {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));  // Turn off LEDs
    }
  }

  strip.show();

  // Display temperature on OLED
  display.clearDisplay();
  display.setTextSize(2);   // Set text size (larger for better visibility)
  display.setCursor(0, 0);  // Position the text at the top-left
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.display();       // Refresh the display to show the text

  delay(500); // Adjust delay for sensor reading frequency
}

int TouchSens() {
  int sample = 0;
  for (int i = 0; i < 32; i++) {
    sample += touchRead(TOUCHPAD);
  }
  sample = sample / 32;
  return sample;
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
