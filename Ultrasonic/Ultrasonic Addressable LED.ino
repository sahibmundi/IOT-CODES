#include "Adafruit_NeoPixel.h"
#define LEDS_COUNT  6
#define LEDS_PIN  33
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_COUNT, LEDS_PIN, NEO_RGB + NEO_KHZ800);

const int echoPin = 12;
const int trigPin = 13;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  strip.begin();
  Serial.begin(250000);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.0343 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Turn off all LEDs initially
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setPixelColor(i, 0, 0, 0); // Set color to black (off)
  }

  if (distance <= 10) {
    strip.setPixelColor(0, 255, 0, 0); // Red
    strip.setPixelColor(1, 0, 0, 0); // Red
    strip.setPixelColor(2, 0, 0, 0); // Red
    strip.setPixelColor(3, 0, 0, 0); // Red
    strip.setPixelColor(4, 0, 0, 0); // Red
    strip.setPixelColor(5, 0, 0, 0); // Red
  } else if (distance <= 20) {
    strip.setPixelColor(0, 255, 0, 0); // Red
    strip.setPixelColor(1, 255, 0, 0); // Red
    strip.setPixelColor(2, 0, 0, 0); // Red
    strip.setPixelColor(3, 0, 0, 0); // Red
    strip.setPixelColor(4, 0, 0, 0); // Red
    strip.setPixelColor(5, 0, 0, 0); // Red
  } else if (distance <= 30) {
    strip.setPixelColor(0, 255, 0, 0); // Red
    strip.setPixelColor(1, 255, 0, 0); // Red
    strip.setPixelColor(2, 255, 0, 0); // Red
    strip.setPixelColor(3, 0, 0, 0); // Red
    strip.setPixelColor(4, 0, 0, 0); // Red
    strip.setPixelColor(5, 0, 0, 0); // Red
  } else if (distance <= 40) {
    strip.setPixelColor(0, 255, 0, 0); // Red
    strip.setPixelColor(1, 255, 0, 0); // Red
    strip.setPixelColor(2, 255, 0, 0); // Red
    strip.setPixelColor(3, 255, 0, 0); // Red
    strip.setPixelColor(4, 0, 0, 0); // Red
    strip.setPixelColor(5, 0, 0, 0); // Red
  } else if (distance <= 50) {
    strip.setPixelColor(0, 255, 0, 0); // Red
    strip.setPixelColor(1, 255, 0, 0); // Red
    strip.setPixelColor(2, 255, 0, 0); // Red
    strip.setPixelColor(3, 255, 0, 0); // Red
    strip.setPixelColor(4, 255, 0, 0); // Red
    strip.setPixelColor(5, 0, 0, 0); // Red
  } else if (distance <= 60) {
    strip.setPixelColor(0, 255, 0, 0); // Red
    strip.setPixelColor(1, 255, 0, 0); // Red
    strip.setPixelColor(2, 255, 0, 0); // Red
    strip.setPixelColor(3, 255, 0, 0); // Red
    strip.setPixelColor(4, 255, 0, 0); // Red
    strip.setPixelColor(5, 255, 0, 0); // Red
  } else{
    strip.setPixelColor(0, 0, 0, 0); // Red
    strip.setPixelColor(1, 0, 0, 0); // Red
    strip.setPixelColor(2, 0, 0, 0); // Red
    strip.setPixelColor(3, 0, 0, 0); // Red
    strip.setPixelColor(4, 0, 0, 0); // Red
    strip.setPixelColor(5, 0, 0, 0); // Red
  }

  strip.show();
}
