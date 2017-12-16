#include <Servo.h>  //Incorporate servo library

Servo leftWheel;    //Create servo object for the left wheel.
Servo rightWheel;    //Create servo object for the right wheel.
 

void setup() {
  leftWheel.attach(9);  // attaches left wheel servo to pin 9 
  rightWheel.attach(10);  // attaches right wheel servo to pin 10 
  pinMode(4,OUTPUT);
}



void loop() {
 
    digitalWrite(4,HIGH);
    leftWheel.attach(9);  // attaches left wheel servo to pin 9 
    rightWheel.attach(10);  // attaches right wheel servo to pin 10
    
    delay(1000);
    leftWheel.write(151);
    rightWheel.write(33.5);
    delay(2000);
    leftWheel.write(91);
    rightWheel.write(93.5);
    delay(2000);
    leftWheel.write(31);
    rightWheel.write(153.5);
    delay(2000);
    leftWheel.write(33);
    rightWheel.write(33);
    delay(2000);
    leftWheel.write(91);
    rightWheel.write(93.5);
    delay(2000);
    
    digitalWrite(4,LOW);

}
