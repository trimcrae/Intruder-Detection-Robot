#include <Servo.h>  //Incorporate servo library

Servo trigger;
int pulled = 65;
int notPulled = 145;
int numDarts = 6;


void setup() {
  trigger.attach(11);

}

void loop() {
  trigger.write(notPulled);
  delay(5000);
  for (int i = 1; i <= numDarts; i++) {
    trigger.write(notPulled);
    delay(2000);
    trigger.write(pulled);
    delay(2000);
  }
  delay(100000000000);

}
