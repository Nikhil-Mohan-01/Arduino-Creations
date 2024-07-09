#include <Servo.h>

#define trigPin 8
#define echoPin 9

long duration;
int distance;

Servo servo;

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(11);
  Serial.begin(9600);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    servo.write(i);
    delay(15);
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
  for(int i = 165; i >= 15; i--){
    servo.write(i);
    delay(15);
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}
