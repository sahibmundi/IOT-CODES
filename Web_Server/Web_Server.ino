#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"

// WiFi credentials
const char* ssid = "SSID";
const char* password = "Password";

WebServer server(80);

// Pin definitions
#define RELAY_PIN 25
#define LED_PIN 18
#define BUZZER_PIN 27
#define SERVO_PIN 32
#define LED_STRIP_PIN 33

// LED Strip settings
#define LEDS_COUNT 6
#define LED_CHANNEL 0
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LED_STRIP_PIN, LED_CHANNEL);

bool relayStatus = LOW;
bool ledStatus = LOW;
bool buzzerStatus = LOW;
int servoPosition = 0;
int redColor = 0, greenColor = 0, blueColor = 0;

Servo myServo;

void clearLEDs() {
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, 0, 0, 0);
  }
  strip.show();
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  strip.begin();
  strip.setBrightness(50);
  clearLEDs();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/RELAYon", handle_RELAYon);
  server.on("/RELAYoff", handle_RELAYoff);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/buzzeron", handle_buzzeron);
  server.on("/buzzeroff", handle_buzzeroff);
  server.on("/servo", handle_servo);
  server.on("/setLEDColor", handle_setLEDColor);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  digitalWrite(RELAY_PIN, relayStatus ? HIGH : LOW);
  digitalWrite(LED_PIN, ledStatus ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, buzzerStatus ? HIGH : LOW);
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}

void handle_RELAYon() {
  relayStatus = HIGH;
  server.send(200, "text/html", SendHTML());
}

void handle_RELAYoff() {
  relayStatus = LOW;
  server.send(200, "text/html", SendHTML());
}

void handle_ledon() {
  ledStatus = HIGH;
  server.send(200, "text/html", SendHTML());
}

void handle_ledoff() {
  ledStatus = LOW;
  server.send(200, "text/html", SendHTML());
}

void handle_buzzeron() {
  buzzerStatus = HIGH;
  server.send(200, "text/html", SendHTML());
}

void handle_buzzeroff() {
  buzzerStatus = LOW;
  server.send(200, "text/html", SendHTML());
}

void handle_servo() {
  if (server.hasArg("pos")) {
    servoPosition = server.arg("pos").toInt();
    servoPosition = constrain(servoPosition, 0, 180);
    myServo.write(servoPosition);
  }
  server.send(200, "text/html", SendHTML());
}

void handle_setLEDColor() {
  if (server.hasArg("r")) redColor = server.arg("r").toInt();
  if (server.hasArg("g")) greenColor = server.arg("g").toInt();
  if (server.hasArg("b")) blueColor = server.arg("b").toInt();

  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, redColor, greenColor, blueColor);
  }
  strip.show();
  server.send(200, "text/html", SendHTML());
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML() {
  String ptr = "<!DOCTYPE html><html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP32 Device Control</title>\n";
  ptr += "<style>";
  ptr += "body { font-family: Arial, sans-serif; background-color: #121212; color: #e0e0e0; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }";
  ptr += ".container { max-width: 400px; padding: 20px; background: #1e1e1e; border-radius: 10px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.3); }";
  ptr += "h1 { text-align: center; color: #bb86fc; margin-bottom: 20px; }";
  ptr += ".section { margin-bottom: 20px; padding: 15px; border-radius: 10px; background-color: #333; display: flex; align-items: center; justify-content: space-between; }";
  ptr += "button, input[type='submit'] { background-color: #bb86fc; color: #121212; padding: 10px 15px; border: none; border-radius: 5px; cursor: pointer; }";
  ptr += "button:hover, input[type='submit']:hover { background-color: #3700b3; }";
  ptr += "input[type='number'] { width: 100%; padding: 10px; margin: 5px 0 10px; border: 1px solid #555; border-radius: 5px; background-color: #2a2a2a; color: #e0e0e0; }";
  ptr += "</style></head>\n";
  
  ptr += "<body><div class='container'>\n";
  ptr += "<h1>ESP32 Control</h1>\n";
  
  ptr += "<div class='section'><h3>RELAY</h3>\n";
  ptr += "<button onclick=\"location.href='/RELAY" + String(relayStatus ? "off" : "on") + "'\">Toggle</button></div>\n";
  
  ptr += "<div class='section'><h3>LED</h3>\n";
  ptr += "<button onclick=\"location.href='/led" + String(ledStatus ? "off" : "on") + "'\">Toggle</button></div>\n";
  
  ptr += "<div class='section'><h3>Buzzer</h3>\n";
  ptr += "<button onclick=\"location.href='/buzzer" + String(buzzerStatus ? "off" : "on") + "'\">Toggle</button></div>\n";
  
  ptr += "<div class='section'><h3>Servo</h3>\n";
  ptr += "<form action='/servo' method='get'><input type='number' name='pos' min='0' max='180' value='" + String(servoPosition) + "'>\n";
  ptr += "<input type='submit' value='Set Position'></form></div>\n";
  
  ptr += "<div class='section'><h3>LED Strip Color</h3>\n";
  ptr += "<form action='/setLEDColor' method='get'>\n";
  ptr += "R: <input type='number' name='r' min='0' max='255' value='" + String(redColor) + "'><br>\n";
  ptr += "G: <input type='number' name='g' min='0' max='255' value='" + String(greenColor) + "'><br>\n";
  ptr += "B: <input type='number' name='b' min='0' max='255' value='" + String(blueColor) + "'><br>\n";
  ptr += "<input type='submit' value='Set Color'></form></div>\n";
  
  ptr += "</div></body></html>";
  return ptr;
}
