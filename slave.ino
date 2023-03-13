#include <SoftwareSerial.h>

#define rxPinFrom 5
#define txPinFrom 4
#define rxPinTo 2
#define txPinTo 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerialTo =  SoftwareSerial(rxPinTo, txPinTo);
SoftwareSerial mySerialFrom = SoftwareSerial(rxPinFrom, txPinFrom);

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
// == System flags and variables
char DeviceId = 0;
// ================================================
void generateCountPacket() {
  generatePacket(CMD_COUNT, '1', &DeviceId);

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

int receivePacket(){
  int pos = 0; // possition to start reading

  // regenerate packet
  char packet_header_ = bufferRx[pos++];
  char cmd_ = bufferRx[pos++];
  char len_ = bufferRx[pos++];
  char data_[len_];

  for(int i=0;i<len_ - '0';i++){
    data_[i] = bufferRx[pos++];
  }

  // testing
  Serial.println("Start testing: ");
  Serial.println(packet_header_, HEX);
  Serial.println(cmd_, HEX);
  Serial.println(len_, HEX);

  for(int i=0;i<len_ - '0';i++){
    Serial.println(data_[i], HEX);
  }

  Serial.println(bufferTx[pos++], HEX);

  //Packet analysis

  if(packet_header_ != PACKET_HEADER){
    Serial.println("Bad header");
    return -1;
  }

  switch(cmd_){
    case CMD_COUNT:
      DeviceId = data_[0] + 1;
      Serial.println("New device Id is: ");
      Serial.println(DeviceId); 
      generateCountPacket();          
      break;    
    
  }  
  
  clearRxBuffer();
}

void setup(){ 
  clearTxBuffer();
  mySerialTo.begin(9600);
  mySerialFrom.begin(9600);
  Serial.begin(9600);

  //generateCountPacket();
  

  Serial.println("End init");
}

void loop() {
  if(mySerialFrom.available()){
    tmpRx = mySerialFrom.read();

    if(nextFree == 0 && tmpRx == PACKET_HEADER) {
      clearRxBuffer();
    }

    if(nextFree == 2) {
      dataToReceive = tmpRx-'0';  // store how many bytes we have to receive - data len   
    }

    bufferRx[nextFree++] = tmpRx;  

    if(dataToReceive == (nextFree - 3)){
       receivePacket();
    }    

    Serial.write(bufferRx[nextFree-1]);
  }

  if(Serial.available()){
    mySerialTo.write(Serial.read());
  }
}

/*void setup(){ 
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

 
}*/