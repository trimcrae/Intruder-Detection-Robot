#include <SoftwareSerial.h>

long QTI;
int QTIPin=5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  QTI = RCTime(QTIPin);
  Serial.println(QTI);
  delay(500);
}

long RCTime(int sensorIn) {
  long duration = 0;
  pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
  digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
  delay(1);                      // Wait 1ms
  pinMode(sensorIn, INPUT);      // Make pin INPUT
  digitalWrite(sensorIn, LOW);   // Turn off internal pullups
  while (digitalRead(sensorIn)) { // Wait for pin to go LOW
    duration++;
  }
  return duration;
}
