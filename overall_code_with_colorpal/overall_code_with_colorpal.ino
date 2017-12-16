//Initialize Variables

//QTR Variables
int QTR=A1;
int darkness;
int QTRLimit = 750;


//IR Variables
float defaultIrMin = 17;
float defaultIrMax = 24;
int dis;
boolean present;

//QTI Variables
int qtiLimit = 100;
int qti = 6;
int qtiReading;

//Wheel Servo Variables
int leftWheelZero = 90;
int rightWheelZero = 93.5;
int wheelSpeed = 5;
int turnTime = 2000;
//int wheelPower=4;

//Trigger Servo Variables
int pulled = 65;
int notPulled = 145;
int numDarts = 6;

boolean intruder;
boolean inField;

//ColorPal Variables
float colorSensorRangeInCM = 8;
//boolean intruderInArea;
//const int colorPal = 2;      // ColorPAL connected to pin 2
//const int colorPalPower = 3;  //ColorPAL power hooked up to pin 2.
//const int unused = 255;     // Non-existant pin # for SoftwareSerial
//const int sioBaud = 4800;
//const int waitDelay = 1000;
//int red;
//int grn;
//int blu;
//const int numSamples = 10;
//int redArray[numSamples];
//int grnArray[numSamples];
//int bluArray[numSamples];
//float redMedian;
//float bluMedian;
//float grnMedian;
//int i = 0;


//Initialize IR sensor
#include <SharpIR.h>
#define ir A0
#define model 1080
SharpIR sharp(ir, 25, 93, model);

//Initialize servos
#include <Servo.h>
Servo leftWheel;
Servo rightWheel;
Servo trigger;

//Initialize color pal
//#include <SoftwareSerial.h>
//SoftwareSerial serin(colorPal, unused);
//SoftwareSerial serout(unused, colorPal);


void setup() {
  //Serial
  Serial.begin(9600);

  //Servos
  leftWheel.attach(9);
  rightWheel.attach(10);
  trigger.attach(11);
  //  pinmode(wheelPower,OUTPUT);

  //IR
  pinMode (ir, INPUT);

  //ColorPal
//  pinMode (colorPalPower, OUTPUT);

}

void loop() {
//  digitalWrite(colorPalPower, LOW);
  //  digitalWrite(wheelPower,HIGH);
  //  leftWheel.attach(9);
  //  rightWheel.attach(10);

  intruder = thereIsAnIntruder();

  while (intruder == false) {
    dis = sharp.distance();
    leftWheel.write(leftWheelZero - wheelSpeed);
    rightWheel.write(rightWheelZero + wheelSpeed);
    inField = notOnBoundary();
    intruder = thereIsAnIntruder();
    if (inField == false) {
      turnAround();
    }
  }

  driveToIntruder();
//  if (true) {
  delay(1000);
if (intruderIsEnemy()) {
    fireProjectile();
    delay(1000);
  }
  else {
    leftWheel.write(leftWheelZero - wheelSpeed);
    rightWheel.write(rightWheelZero + wheelSpeed);
    delay(3000);
    leftWheel.write(leftWheelZero);
    rightWheel.write(rightWheelZero); 
    delay(1000);
  }

}


boolean thereIsAnIntruder() {
  dis = distanceToIntruder();
  present = dis < defaultIrMin;
  return (present);
}

void driveToIntruder() {
  do  {
    leftWheel.write(leftWheelZero + wheelSpeed * 3);
    rightWheel.write(rightWheelZero - wheelSpeed * 3);  
    delay(100);
  } while (distanceToIntruder() > colorSensorRangeInCM);
  
  delay(400);
  leftWheel.write(leftWheelZero);
  rightWheel.write(rightWheelZero);
}

//void colorPalSetup() {
//  resetColorPal();          // Send reset to ColorPal
//  serout.begin(sioBaud);
//  pinMode(colorPal, OUTPUT);
//  serout.print("= (00 $ m) !"); // Loop print values, see ColorPAL documentation
//  serout.end();       // Discontinue serial port for transmitting
//  serin.begin(sioBaud);         // Set up serial port for receiving
//  pinMode(colorPal, INPUT);
//}

//Emergency QTR use
boolean intruderIsEnemy() {
  darkness=analogRead(QTR);
  return(darkness<QTRLimit);
}

//boolean intruderIsEnemy() {
//
//  //digitalWrite(wheelPower, LOW);
//  digitalWrite(colorPalPower, HIGH);
//  colorPalSetup();
//
//  int count = 0;
//
//  while (count < 20) {
//    char buffer[32];
//
//    if (serin.available() > 0) {
//      // Wait for a $ character, then read three 3 digit hex numbers
//      buffer[0] = serin.read();
//      if (buffer[0] == '$') {
//        for (int k = 0; k < 9; k++) {
//          while (serin.available() == 0);     // Wait for next input character
//          buffer[k] = serin.read();
//        }
//
//        sscanf (buffer, "%3x%3x%3x", &red, &grn, &blu);
//
//        redArray[i] = red;
//        grnArray[i] = grn;
//        bluArray[i] = blu;
//        redMedian = median (redArray);
//        grnMedian = median (grnArray);
//        bluMedian = median (bluArray);
//
//        if (i < 9) i++;
//        else i = 0;
//        delay(500);
//        count++;
//      }
//    }
//  }
//  delay(10000);
//  boolean enemy = red > (grn + blu);
//  digitalWrite(colorPalPower, LOW);
//  //  digitalWrite(wheelPower,HIGH);
//  //  leftWheel.attach(9);
//  //  rightWheel.attach(10);
//  return (enemy);
//}


//float median(int x[]) {
//  float temp;
//  int i, j;
//  for (i = 0; i < numSamples - 1; i++) {
//    for (j = i + 1; j < numSamples; j++) {
//      if (x[j] < x[i]) {
//        temp = x[i];
//        x[i] = x[j];
//        x[j] = temp;
//      }
//    }
//  }
//
//  if (numSamples % 2 == 0) {
//    return ((x[numSamples / 2] + x[numSamples / 2 - 1]) / 2.0);
//  } else {
//    return x[numSamples / 2];
//  }
//}

void fireProjectile() {
  leftWheel.write(leftWheelZero - wheelSpeed);
  rightWheel.write(rightWheelZero + wheelSpeed);
  delay(2000);
  turnAround();

  for (int shots = 0; shots <= numDarts; shots++) {
    trigger.write(pulled);
    delay(2000);
    trigger.write(notPulled);
    delay(2000);
  }
}

float distanceToIntruder() {

  dis = sharp.distance();
  //  Serial.println(dis);
  return (dis);
}

boolean notOnBoundary() {
  qtiReading = RCTime(qti);
  //  Serial.println(qtiReading);
  return (qtiReading < qtiLimit);
}

void turnAround() {
  leftWheel.write(33);
  rightWheel.write(33);
  delay(2800);
  leftWheel.write(leftWheelZero);
  rightWheel.write(rightWheelZero);
}

//void resetColorPal() {
//  delay(200);
//  pinMode(colorPal, OUTPUT);
//  digitalWrite(colorPal, LOW);
//  pinMode(colorPal, INPUT);
//  while (digitalRead(colorPal) != HIGH);
//  pinMode(colorPal, OUTPUT);
//  digitalWrite(colorPal, LOW);
//  delay(80);
//  pinMode(colorPal, INPUT);
//  delay(waitDelay);
//}

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


