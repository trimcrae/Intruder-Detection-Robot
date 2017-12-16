

#include <SoftwareSerial.h>

const int sio = 2;			// ColorPAL connected to pin 4
const int unused = 255; 		// Non-existant pin # for SoftwareSerial
const int sioBaud = 4800;
const int waitDelay = 200;
int colorPalPower=3;
int t=0;



// Received RGB values from ColorPAL
int red;
int grn;
int blu;
const int numSamples=10;
int redArray[numSamples];
int grnArray[numSamples];
int bluArray[numSamples];
float redMedian;
float bluMedian;
float grnMedian;

int i=0;

// Set up two software serials on the same pin.
SoftwareSerial serin(sio, unused);
SoftwareSerial serout(unused, sio);

void setup() {
  Serial.begin(9600);
  pinMode (colorPalPower, OUTPUT);
}

void loop() {
  boolean enemy=intruderIsEnemy();
  Serial.println(enemy);
}  

void colorPalSetup(){
  reset();          // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(sio, OUTPUT);
  serout.print("= (00 $ m) !"); // Loop print values, see ColorPAL documentation
  serout.end();       // Discontinue serial port for transmitting
  serin.begin(sioBaud);         // Set up serial port for receiving
  pinMode(sio, INPUT);
  }

// Reset ColorPAL; see ColorPAL documentation for sequence
void reset() {
  delay(200);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  pinMode(sio, INPUT);
  while (digitalRead(sio) != HIGH);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  delay(80);
  pinMode(sio, INPUT);
  delay(waitDelay);
}

boolean intruderIsEnemy() {
  digitalWrite(colorPalPower, HIGH);
  if(t==0) colorPalSetup();
  t=1;
  
  
  int count=0;
  
  while (count < 20) {
    char buffer[32];

    if (serin.available() > 0) {
      // Wait for a $ character, then read three 3 digit hex numbers
      buffer[0] = serin.read();
      if (buffer[0] == '$') {
        for (int k = 0; k < 9; k++) {
          while (serin.available() == 0);     // Wait for next input character
          buffer[k] = serin.read();
        }

        sscanf (buffer, "%3x%3x%3x", &red, &grn, &blu);

        redArray[i] = red;
        grnArray[i] = grn;
        bluArray[i] = blu;
        redMedian = median (redArray);
        grnMedian = median (grnArray);
        bluMedian = median (bluArray);

      Serial.print(red);
      Serial.print(", ");
      Serial.print(grn);
      Serial.print(", ");
      Serial.println(blu);
        if (i < 9) i++;
        else i = 0;
        delay(500);
        count++;
      }
    }
  }
  boolean enemy = red > (grn + blu);
  digitalWrite(colorPalPower, LOW);
  return (enemy);
}

//void readData() {
//  char buffer[32];
//  
//  if (serin.available() > 0) {
//    // Wait for a $ character, then read three 3 digit hex numbers
//    buffer[0] = serin.read();
//    if (buffer[0] == '$') {
//      for(int i = 0; i < 9; i++) {
//        while (serin.available() == 0);     // Wait for next input character
//        buffer[i] = serin.read();
//        if (buffer[i] == '$')               // Return early if $ character encountered
//          return;
//      }
//      parseAndPrint(buffer);
//      delay(10);
//    }
//  }
//}
//
//// Parse the hex data into integers
//void parseAndPrint(char * data) {
//  
//  sscanf (data, "%3x%3x%3x", &red, &grn, &blu);
//  char buffer[32];
//
//      delay(500);
//      redArray[i]=red;
//      grnArray[i]=grn;
//      bluArray[i]=blu;
//
//      redMedian = median (redArray);
//      grnMedian = median (grnArray);
//      bluMedian = median (bluArray);
//      
//      if (i<9) i++;
//      else i=0;
//      Serial.print(redMedian);
//      Serial.print(", ");
//      Serial.print(grnMedian);
//      Serial.print(", ");
//      Serial.println(bluMedian);
//}

float median(int x[]) {
    float temp;
    int i, j;
    // the following two loops sort the array x in ascending order
    for(i=0; i<numSamples-1; i++) {
        for(j=i+1; j<numSamples; j++) {
            if(x[j] < x[i]) {
                // swap elements
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }

    if(numSamples%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
        return((x[numSamples/2] + x[numSamples/2 - 1]) / 2.0);
    } else {
        // else return the element in the middle
        return x[numSamples/2];
    }
}

