#include <SoftwareSerial.h>

//================================================
#define MAX_PACKET_SIZE 100
#define PACKET_HEADER   0x23

#define CMD_COUNT       0x43   // C

// == All variables related to communication
char bufferTx[MAX_PACKET_SIZE];
char bufferRx[MAX_PACKET_SIZE];
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
  generatePacket(CMD_COUNT, '1', &id);
}

void generatePacket(char cmd, char len, char *data) {
  clearTxBuffer();

  // Here we build our packet
  bufferTx[nextFree++] = PACKET_HEADER;
  bufferTx[nextFree++] = cmd;
  bufferTx[nextFree++] = len;
  
  for(int i = 0; i < len - '0'; i++) {
    bufferTx[nextFree++] = data[i];
  }

  bufferTx[nextFree++] = '\n';

  for(int i = 0; i < nextFree; i++){
    Serial.print(i);
     Serial.print(" : ");
    Serial.print(bufferTx[i],HEX);
     Serial.println("");
    mySerialTo.write(bufferTx[i]);
  }
  Serial.println("");
}

void receivePacket(){
  int pos = 0; // possition to start reading

  // regenerate packet
  char PACKET_HEADER_ = bufferRx[pos++];
  char cmd_ = bufferRx[pos++];
  char len_ = bufferRx[pos++];
  char data_[len_];

  for(int i=0;i<len_ - '0';i++){
    data_[i] = bufferRx[pos++];
  }

  // testing
  Serial.println("Start testing: ");
  Serial.println(PACKET_HEADER_, HEX);
  Serial.println(cmd_, HEX);
  Serial.println(len_, HEX);

  for(int i=0;i<len_ - '0';i++){
    Serial.println(data_[i], HEX);
  }

  Serial.println(bufferTx[pos++], HEX);

  //Packet analysis
  clearRxBuffer();
}

void setup(){ 
  clearTxBuffer();
  mySerialTo.begin(9600);
  Serial.begin(9600);

  generateCountPacket();
  //receivePacket();

  Serial.println("End init");
}

void loop() {
  if(mySerialTo.available()){
    tmpRx = mySerialTo.read();

    if(nextFree == 0 && tmpRx == PACKET_HEADER) {
      clearRxBuffer();
    }

    if(nextFree == 2) {
      dataToReceive = tmpRx-'0';  // store how many bytes we have to receive - data len   
    }

    bufferRx[nextFree++] = tmpRx;  

    if(dataToReceive == (nextFree - 3)){
      // trqbva da go obrabotim i izpratim na sledvashtiq paketa 
    }    

    Serial.write(bufferRx[nextFree-1]);
  }

  if(Serial.available()){
    mySerialTo.write(Serial.read());
  }
}