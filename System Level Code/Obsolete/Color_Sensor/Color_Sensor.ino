

#include <SoftwareSerial.h>

const int colorPal = 2;      // ColorPAL connected to pin 2
const int unused = 255;     // Non-existant pin # for SoftwareSerial
const int sioBaud = 4800;
const int waitDelay = 200;

// Received RGB values from ColorPAL
int red;
int grn;
int blu;

// Set up two software serials on the same pin.
SoftwareSerial serin(colorPal, unused);
SoftwareSerial serout(unused, colorPal);

void setup() {
  Serial.begin(9600);
  reset();          // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(colorPal, OUTPUT);
  serout.print("= (00 $ m) !"); // Loop print values, see ColorPAL documentation
  serout.end();       // Discontinue serial port for transmitting

  serin.begin(sioBaud);         // Set up serial port for receiving
  pinMode(colorPal, INPUT);
}

void loop() {
  isEnemy();
}  

// Reset ColorPAL; see ColorPAL documentation for sequence
void reset() {
  delay(200);
  pinMode(colorPal, OUTPUT);
  digitalWrite(colorPal, LOW);
  pinMode(colorPal, INPUT);
  while (digitalRead(colorPal) != HIGH);
  pinMode(colorPal, OUTPUT);
  digitalWrite(colorPal, LOW);
  delay(80);
  pinMode(colorPal, INPUT);
  delay(waitDelay);
}

boolean isEnemy() {
  char buffer[32];
  
  if (serin.available() > 0) {
    // Wait for a $ character, then read three 3 digit hex numbers
    buffer[0] = serin.read();
    if (buffer[0] == '$') {
      for(int i = 0; i < 9; i++) {
        while (serin.available() == 0);     // Wait for next input character
        buffer[i] = serin.read();
        if (buffer[i] == '$')               // Return early if $ character encountered
          break;
      }
      // Parse the hex data into integers
      sscanf (buffer, "%3x%3x%3x", &red, &grn, &blu); //This line may have an issue with buffer but I think it should be good.
      delay(10);
      Serial.print(red);
      Serial.print(", ");
      Serial.print(grn);
      Serial.print(", ");
      Serial.println(blu);
      delay(500);
      if (red>200&&grn<100&&blu<100) return true;
      else return false;
    }
  }
}




