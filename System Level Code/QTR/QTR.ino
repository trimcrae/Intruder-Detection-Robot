#include <SoftwareSerial.h>

//QTR Variables
int QTR=A1;
int darkness;
int QTRLimit = 200;

void setup() {
  Serial.begin (9600);
}

void loop() {
  darkness=analogRead(QTR);
  Serial.println(darkness);
  delay(500);

}
