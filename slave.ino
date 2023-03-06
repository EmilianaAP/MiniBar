#include <SoftwareSerial.h>

char bufferRx[100];
char bufferTx[100];
int nextfree=0;
int id = 0;

#define rxPinFrom 5
#define txPinFrom 4
#define rxPinTo 2
#define txPinTo 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerialTo =  SoftwareSerial(rxPinTo, txPinTo);
SoftwareSerial mySerialFrom = SoftwareSerial(rxPinFrom, txPinFrom);

void setup(){ 
  mySerialTo.begin(9600);
  mySerialFrom.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(mySerialTo.available()){
    bufferRx[nextfree++] = mySerialTo.read();
    if(bufferRx[nextfree-1] == '\n') {
      mySerialFrom.write(bufferRx,nextfree-1);
      Serial.write(bufferRx,nextfree-1); //Debug usb interface
      nextfree=0;
    }

    
    
  }

  if(mySerialFrom.available()){
    bufferTx[nextfree++] = mySerialFrom.read();
    if(bufferTx[nextfree-1] == '\n') {
      mySerialTo.write(bufferTx,nextfree-1);
      Serial.write(bufferTx,nextfree-1); //Debug usb interface
      mySerialTo.write('\n');
      nextfree=0;
    }
  }

 
}