#include "Adafruit_NeoPixel.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LEDS_COUNT  6
#define LEDS_PIN  33

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_COUNT, LEDS_PIN, NEO_RGB + NEO_KHZ800);

const int echoPin = 12;
const int trigPin = 13;
const int relay = 25;
long duration;
int distance;
int num = 0;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  strip.begin();
  Serial.begin(2000000);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Counter: "));
  display.display();
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

  if(distance >= 15 && distance <= 50){
    digitalWrite(relay, HIGH);
    num++;

    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(2);
    display.print(num);
    display.display();

    for(int i = 0; i <= num - 1; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
      strip.show();
      delay(100);
    }
  } else {
    digitalWrite(relay, LOW);
  }

  delay(1000);
}
