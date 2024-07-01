#define CANDLELED 11
#define REDLED 7
#define TRIG_PIN 9
#define ECHO_PIN 10
#define PROXIMITY_THRESHOLD 10 // (centimeters)
#define PROXIMITY_CONSECUTIVE_READINGS 3
#define FLICKER_INTERVAL 25

long previousMillis = 0;
long closeReadings = 0;

void setup() {
  pinMode(CANDLELED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // Trigger the ultrasonic
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure the distance
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 58; // Calculate distance in centimeters

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= PROXIMITY_THRESHOLD) {
    closeReadings++;
    if (closeReadings >= PROXIMITY_CONSECUTIVE_READINGS) {
      digitalWrite(CANDLELED, LOW);
      digitalWrite(REDLED, HIGH);
    }
  } else {
    digitalWrite(REDLED, LOW);
    closeReadings = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > FLICKER_INTERVAL) {
      previousMillis = currentMillis;
      analogWrite(CANDLELED, random(0, 256));
    }
  }
}
