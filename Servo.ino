
#include <Servo.h>

Servo myServo;  

void setup() {
 
  Serial.begin(9600);
  
  myServo.attach(9);  
}

void loop() {
  
  int analogValue = analogRead(A0);

  // scales it to use it with the servo (value between 0 and 180)
  int angle = map(analogValue, 0, 1023, 0, 180);

 
  myServo.write(angle); 

  // print out the value
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Angle: ");
  Serial.println(angle);
  delay(1000);
}
