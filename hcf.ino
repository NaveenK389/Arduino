#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "YOUR SSID";
const char* password = "******";
const char* server = "api.thingspeak.com";
const char* apiKey = "YOUR API KEY";
const int buttonPin1 = D1;  // Pin connected to the first push-button
const int buttonPin2 = D5;  // Pin connected to the second push-button
int buttonState1 = 0;       // Current state of the first button
int buttonState2 = 0;       // Current state of the second button
int lastButtonState1 = 0;   // Previous state of the first button
int lastButtonState2 = 0;   // Previous state of the second button
int pressCount1 = 0;        // Counter for presses on the first button
int pressCount2 = 0;        // Counter for presses on the second button
unsigned long lastDebounceTime1 = 0;  // Last time the button 1 state was toggled
unsigned long lastDebounceTime2 = 0;  // Last time the button 2 state was toggled
unsigned long debounceDelay = 50;     // Debounce delay time in milliseconds
WiFiClient client;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);  // Set the first button pin as input with internal pull-up resistor
  pinMode(buttonPin2, INPUT_PULLUP);  // Set the second button pin as input with internal pull-up resistor
  Serial.begin(9600);

  // Connect to Wi-Fi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Read the state of the first button
  int reading1 = digitalRead(buttonPin1);
  // Check for a change in the state of the first button
  if (reading1 != lastButtonState1) {
    // Reset the debounce timer
    lastDebounceTime1 = currentMillis;
  }
  if ((currentMillis - lastDebounceTime1) > debounceDelay) {
    // Button state has stabilized
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      // Check if the button 1 state has changed
      if (buttonState1 == LOW) {
        // Button 1 is pressed
        pressCount1++;
        Serial.print("Left button pressed! Press count: ");
        Serial.println(pressCount1);
        updateThingSpeak(pressCount1, 1); // Update ThingSpeak with press count for button 1
      }
    }
  }
  // Update lastButtonState1
  lastButtonState1 = reading1;

  // Read the state of the second button
  int reading2 = digitalRead(buttonPin2);
  // Check for a change in the state of the second button
  if (reading2 != lastButtonState2) {
    // Reset the debounce timer
    lastDebounceTime2 = currentMillis;
  }
  if ((currentMillis - lastDebounceTime2) > debounceDelay) {
    // Button state has stabilized
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      // Check if the button 2 state has changed
      if (buttonState2 == LOW) {
        // Button 2 is pressed
        pressCount2++;
        Serial.print("Right button pressed! Press count: ");
        Serial.println(pressCount2);
        updateThingSpeak(pressCount2, 2); // Update ThingSpeak with press count for button 2
      }
    }
  }
  // Update lastButtonState2
  lastButtonState2 = reading2;
}

void updateThingSpeak(int count, int button) {
  if (client.connect(server, 80)) {
    String url = "/update?api_key=";
    url += apiKey;
    url += "&field";
    url += button;
    url += "=";
    url += count;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" + 
                 "Connection: close\r\n\r\n");
    Serial.println("Updated ThingSpeak with count for button " + String(button) + ": " + String(count));
    client.stop();
  } else {
    Serial.println("Failed to connect to ThingSpeak server");
  }
}
