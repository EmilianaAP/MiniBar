#include <SoftwareSerial.h>

//================================================
#define MAX_PACKET_SIZE 100
#define PACKET_HEADER   0xA5

#define CMD_COUNT       0x43   // C
// == All variables related to communication
int bufferTx[MAX_PACKET_SIZE];
int bufferRx[MAX_PACKET_SIZE];
int nextFree;
char dataToReceive;

char tmpRx;

//=================================================
void clearTxBuffer() {
  for(int i = 0 ; i < MAX_PACKET_SIZE; i ++) {
    bufferTx[i] = 0;
  }
  nextFree=0;
  Serial.println("Tx buffer cleared");
}

void clearRxBuffer() {
  for(int i = 0 ; i < MAX_PACKET_SIZE; i ++) {
    bufferRx[i] = 0;
  }
  nextFree=0;
  Serial.println("Rx buffer cleared");
}
// ================================================
char id = 0;

#define rxPinTo 2
#define txPinTo 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerialTo =  SoftwareSerial(rxPinTo, txPinTo);

void generateCountPacket() {
  generatePacket(CMD_COUNT, 1, &id);

}


void generatePacket(char cmd, char len, char *data) {
  clearTxBuffer();

  // Here we build our packet
  bufferTx[nextFree++] = PACKET_HEADER;
  bufferTx[nextFree++] = cmd;
  bufferTx[nextFree++] = len;
  for(int i = 0; i < len; i++) {
    bufferTx[nextFree++] = data[i];
  }
  bufferTx[nextFree++] = '\n';

  for(int i = 0; i < nextFree; i++){
    Serial.print(bufferTx[i],HEX);
    mySerialTo.write(bufferTx[i]);
  }
  Serial.println("");
}

void setup(){ 
  clearTxBuffer();
  mySerialTo.begin(9600);
  Serial.begin(9600);

  generateCountPacket();
  Serial.println("End init");
}

void loop() {
  if(mySerialTo.available()){
    tmpRx = mySerialTo.read();

    if(nextFree == 0 && tmpRx == PACKET_HEADER) {
      clearRxBuffer();
          
    }
    if(nextFree == 2) {
      dataToReceive = tmpRx;  // store how many bytes we have to receive - data len   
    }
    bufferRx[nextFree++] = tmpRx;  







    
    Serial.write(bufferRx[nextFree-1]);
  }

  if(Serial.available()){
    mySerialTo.write(Serial.read());
  }
}