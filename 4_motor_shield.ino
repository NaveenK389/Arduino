#include  <AFMotor.h>
  #include <Servo.h>
//initial motors pin
AF_DCMotor motor1(1, MOTOR12);
AF_DCMotor  motor2(2, MOTOR12);
AF_DCMotor motor3(3, MOTOR34);
AF_DCMotor motor4(4,  MOTOR34);
Servo myservo;  // create servo object to control a servo

int val;
int Speeed = 255;
float pos = 0;
  
void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
   myservo.attach(9); 
}
void loop(){
  if(Serial.available()  > 0){
    val = Serial.read();
      
    Stop(); //initialize with motors  stoped
      
          if (val == 'F'){
          forward();
          }
  
          if (val == 'B'){
          back();
          }
  
          if  (val == 'L'){
          left();
          }
  
          if (val ==  'R'){
          right();
          }
          if (val == 'I'){
          topright();
          }
  
          if (val == 'J'){
          topleft();
          }
  
          if (val == 'K'){
          bottomright();
          }
  
          if (val == 'M'){
          bottomleft();
          }
          if  (val == 'T'){
          Stop();
          }
  }
}
           
  
            
  
  
  
void forward()
{
   Serial.println("Forward");
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate  the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed);//Define  maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed);//Define  maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
  
  
}
  
void back()
{
 Serial.println("Bacward");
  motor1.setSpeed(Speeed);  //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum  velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed);  //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
void left()
{
 Serial.println("Left");
 
  motor1.setSpeed(Speeed);  //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum  velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(Speeed);  //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}
  
void right()
{
  Serial.println("Right");
 motor1.setSpeed(Speeed);  //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate  the motor clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed);  //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
void topleft(){
  Serial.println("Top Left");
 motor1.setSpeed(Speeed);  //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate  the motor clockwise
  motor3.setSpeed(Speeed/3.1);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed/3.1);//Define  maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
  
void topright()
{
  Serial.println("Top Right");
 motor1.setSpeed(Speeed/3.1);  //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed/3.1); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(Speeed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed);//Define  maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
  
void bottomleft()
{
  Serial.println("Botom Left");
 motor1.setSpeed(Speeed);  //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed/3.1); //Define maximum  velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed/3.1);  //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
void bottomright()
{
Serial.println("Bottom Right");
for (pos = 0; pos <= 180; pos += 0.6) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 0.6) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);  
  } 
  
  
void Stop()
{
 Serial.println("Stop");
 
  motor1.setSpeed(0);  //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release  the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE);  //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0);  //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release  the button
 for (pos = 0; pos <= 180; pos += 0) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);
 }
 
}