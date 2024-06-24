#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int dayButtonPin = 2;   // Change this to the pin connected to the day button
const int monthButtonPin = 3; // Change this to the pin connected to the month button

const int currentSensorPin = A0; // Change this to the pin connected to the current sensor
const int voltageSensorPin = A1; // Change this to the pin connected to the voltage sensor

double totalPowerDay = 0;
double  totalPowerMonth = 0;
float totalCostDay = 0;
float totalCostMonth = 0;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; 

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  Serial.begin(9600);

  pinMode(dayButtonPin, INPUT);
  pinMode(monthButtonPin, INPUT);
}

void loop() {
  display.clearDisplay();
  
  // Read sensor values
  float voltage = analogRead(voltageSensorPin) * (5.0 / 1023.0); // Convert ADC value to voltage
  float current = analogRead(currentSensorPin) * (5.0 / 1023.0); // Convert ADC value to current
float power = voltage * current;
      Serial.println(voltage);
      Serial.println(current);
      Serial.println(power);

  // Check if sensor readings are within valid ranges
  if (voltage >= 0 && voltage <= 5 && current >= 0 && current <= 5) {
    // Calculate power in watts
    float cost;

// Check if it's time to update the power values
    if (millis() - lastUpdateTime >= updateInterval) {
      Serial.println(voltage);
      Serial.println(current);
      // float power = voltage * current;
      totalPowerDay += power;
      totalPowerMonth = power*30*360000;
      totalCostDay=totalPowerDay*0.2;
      totalCostMonth=totalPowerMonth*30*360000*0.5;
      lastUpdateTime = millis();
    }

    // Check button presses
    if (digitalRead(dayButtonPin) == HIGH) {
      displayPower("Day Power", totalPowerDay,totalCostDay);
    } else if (digitalRead(monthButtonPin) == HIGH) {
      displayPower("Month Power", totalPowerMonth,totalCostMonth);
    } else {
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("IoT Energy Meter");
    }
  } else {
    // Handle invalid sensor readings
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("Invalid Sensor Readings");
  }

  display.display();
}

void displayPower(const char* label, unsigned long power,float totalCostDay) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.print(label);
  display.setCursor(0, 30);
  display.print(power);
  display.println(" Wh");
    display.setCursor(0, 40);
  display.print(totalCostDay);
  display.println(" rupee");
}
