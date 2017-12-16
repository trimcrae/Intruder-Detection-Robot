//Initialize IR sensor
#include <SharpIR.h>
#define ir A0
#define model 1080
SharpIR sharp(ir, 25, 93, model);
int dis;
boolean present;
float defaultIrMin = 14;

//Setup Pins
void setup() {
  Serial.begin(9600);
  pinMode (ir, INPUT);
}

void loop(){
  dis = sharp.distance();
  present = (dis<defaultIrMin);
  Serial.println(dis);
  if(present) Serial.println("Object Detected");
  else Serial.println("No Object Detected");
  delay(1000);
}




