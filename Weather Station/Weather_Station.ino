#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>  // Commented out
#include <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

bool statusBMP = false; 
//bool statusBME = false;  // Commented out

//Adafruit_BME280 bme;  // Commented out

Adafruit_BMP280 bmp; 


void setup() {
    Serial.begin(250000);

    //statusBME = bme.begin(0x76);  // Commented out
    statusBMP = bmp.begin(0x76);

    if (statusBMP) {
        Serial.println("BMP280 sensor found");
    } else {
        Serial.println("Could not find BMP280 sensor, check wiring!");
        while (true);  // Halt if sensor not found
    }

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);  // Halt if display not found
    }
    display.clearDisplay();
    display.setTextColor(WHITE);
}


// printValues() is removed as it's only for the BME280 sensor.


void printValuesbmp() {
    float t = bmp.readTemperature();
    float p = bmp.readPressure() / 100;  // Convert to hPa

    if (isnan(p) || isnan(t)) {
        Serial.println("Failed to read from BMP280 sensor!");
        return;  // Don't update display if reading failed
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.print(t, 1);  // Show temperature with 1 decimal place
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true);
    display.write(167); // º symbol
    display.setTextSize(2);
    display.print("C");

    display.setTextSize(1);
    display.setCursor(0, 35);
    display.print("Pressure: ");
    display.setTextSize(1);
    display.setCursor(0, 45);
    display.print(p, 1);  // Show pressure with 1 decimal place
    display.print(" hPa");  

    display.display(); 
}


void loop() {
    if (statusBMP) { 
        printValuesbmp();
    } 
    delay(1000); 
}
