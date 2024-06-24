#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define ENA 9
#define ENB 10

int ir_back = 6;
int ir_left = 7;
int ir_right = 8;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(ir_back, INPUT);
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);
}

void loop() {

  int obj1 = digitalRead(ir_back);
  int obj2 = digitalRead(ir_left);
  int obj3 = digitalRead(ir_right);


  analogWrite(ENA, 255);
  analogWrite(ENB, 255);


  if (Serial.available() > 0) {
    char value = Serial.read();
    Serial.print(value);

    if (value == 'F') {
      forward();
    } else if (value == 'B') {
      backward();
    } else if (value == 'L') {
      left();
    } else if (value == 'R') {
      right();
    } 
     else if (value == 'I') {
      obstacleDetection(obj1, obj2, obj3);
     }
      else {
      Stop();
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}



void obstacleDetection(int obj1, int obj2, int obj3) {


  analogWrite(ENA, 100);
  analogWrite(ENB, 100);

  if (obj1 == 0 || obj2 == 0 || obj3 == 0) {
 for (int i = 0; i <= 5; i++) {

  forward();
  delay(100);

 }

  }
   else if (obj1 == 0 || obj2 == 0 || obj3 == 1) {
    for (int i = 0; i <= 5; i++) {
  left();
  delay(100);
    }
  } else if (obj1 == 0 || obj2 == 1 || obj3 == 0) {
    for (int i = 0; i <= 5; i++) {
  right();
   delay(100);
    }
  } else if (obj1 == 1 || obj2 == 0 || obj3 == 0) {
    for (int i = 0; i <= 5; i++) {
    Stop();
       delay(100);
    }
  }
}
