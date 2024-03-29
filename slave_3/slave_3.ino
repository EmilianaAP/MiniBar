#include <SoftwareSerial.h>
#include <avr/wdt.h>

// #define DEBUG 1

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
#define CMD_EBP         0x41   // A
#define CMD_PFB         0x42   // B

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
  //Serial.println("Tx buffer cleared");
}

void clearRxBuffer() {
  for(int i = 0 ; i < MAX_PACKET_SIZE; i ++) {
    bufferRx[i] = 0;
  }
  nextFree=0;
  //Serial.println("Rx buffer cleared");
}
// ================================================
// == System flags and variables
char id = '3';
// ================================================

void generateEmptyBottlePacket() {
  generatePacket(CMD_EBP, '1', &id);
}

void TransmitEmptyBottlePacket(char* id_data) {
  generatePacket(CMD_EBP, '1', id_data);
}

void TransmitPouringFromBottlePacket(char bottleId, char quantity) {
  char data[2];
  data[0] = bottleId;
  data[1] = quantity;
  
  generatePacket(CMD_PFB, '2', data);
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

  //bufferTx[nextFree++] = '\n';

  for(int i = 0; i < nextFree; i++){
      mySerialTo.write(bufferTx[i]);
  }
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

  //Packet analysis

  if(packet_header_ != PACKET_HEADER){
    Serial.println("Bad header");
    return -1;
  }

  switch(cmd_){
    wdt_disable();
    case CMD_EBP:
      TransmitEmptyBottlePacket(&data_[0]);
      clearTxBuffer();        
      break;
    case CMD_PFB:
      if(data_[0] == id){
        Serial.print("Pouring ");
        Serial.print(data_[1]);
        Serial.println("ml");
        delay(2000);
        Serial.println("Pump on");
        digitalWrite(8,LOW);  
        delay(3000);
        Serial.println("Pump off");
        digitalWrite(8,HIGH);
        clearTxBuffer();         
        break;       
      }else{        
        Serial.print("Transmit ");
        Serial.print(data_[1]);
        Serial.print("ml to slave ");
        Serial.println(data_[0]);
        TransmitPouringFromBottlePacket(data_[0], data_[1]);   
        clearTxBuffer();         
        break;
      } 
  }  
  
  clearRxBuffer();
}

void setup(){ 
  clearTxBuffer();
  mySerialTo.begin(9600);
  mySerialFrom.begin(9600);
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  Serial.println("Pump off");
  digitalWrite(8,HIGH);

  Serial.println("This arduino id: ");
  Serial.println(id);

  wdt_disable();
  delay(8000);
  wdt_enable(WDTO_8S);
  
#ifdef DEBUG  
  Serial.println("End init");
#endif
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

    //Serial.write(bufferRx[nextFree-1]);
  }

  if(Serial.available()){
    mySerialTo.write(Serial.read());
  }
}
