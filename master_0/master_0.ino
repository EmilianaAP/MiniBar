#include <SoftwareSerial.h>
#include <avr/wdt.h>

//================================================
#define MAX_PACKET_SIZE 100
#define PACKET_HEADER   0x23

#define CMD_EBP         0x41   // A
#define CMD_PFB         0x42   // B
#define CMD_COUNT       0x43   // C
#define CMD_RS          0x44   //D

// == All variables related to communication
char bufferTx[MAX_PACKET_SIZE];
char bufferRx[MAX_PACKET_SIZE];
int nextFree;
char dataToReceive;

char tmpRx;

//=================================================
void reset() {
  asm volatile ("  jmp 0");  // jump to the reset vector
}

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
// Arduino id:
int id = 0;

#define rxPinFrom 5
#define txPinFrom 4
#define rxPinTo 2
#define txPinTo 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerialTo =  SoftwareSerial(rxPinTo, txPinTo);
SoftwareSerial mySerialFrom = SoftwareSerial(rxPinFrom, txPinFrom);

// ==================================================
// BLT
SoftwareSerial BT(10,11); // TX to pin_10. RX to pin_11 of Arduino.

void generatePouringFromBottlePacket(char bottleId, char quantity) {
  char data[2];
  data[0] = bottleId;
  data[1] = quantity;

  generatePacket(CMD_PFB, '2', data);
}

void restartSlave(char *slaveId) {
  generatePacket(CMD_RS, '1', slaveId);
}

void generatePacket(char cmd, char len, char *data) {
  clearTxBuffer();

  // Here we build our packet
  bufferTx[nextFree++] = PACKET_HEADER;
  bufferTx[nextFree++] = cmd;
  bufferTx[nextFree++] = len;
  
  for(int i = 0; i < len - '0'; i++) {
    bufferTx[nextFree++] = data[i];
    //Serial.print(bufferTx[nextFree++], HEX);    
  }

 // bufferTx[nextFree++] = '\n';

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

  switch(cmd_){
    case CMD_EBP:
      //generateEmptyBottlePacket(); 
      Serial.print("Empty bottle id is : ");
      Serial.print(data_[0]);
      Serial.println(" ");            
      clearTxBuffer();         
      break;
  }  
  
  clearRxBuffer();
}

void drink1(){
  char id_ = '1';
  char quantity = '8';
  generatePouringFromBottlePacket(id_, quantity);
  delay(5500);
  reset();
}

void drink2(){
  char id_ = '2';
  char quantity = '8';
  generatePouringFromBottlePacket(id_, quantity);  
}

void drink3(){
  char id_ = '3';
  char quantity = '8';
  generatePouringFromBottlePacket(id_, quantity);    
}

void drink4(){
  char id_ = '4';
  char quantity = '8'; 
  generatePouringFromBottlePacket(id_, quantity);    
}

void setup(){ 
  clearTxBuffer();
  mySerialTo.begin(9600);
  mySerialFrom.begin(9600);
  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("\nThis arduino id: ");
  Serial.println(id);

  wdt_disable();
  delay(9000);
  wdt_enable(WDTO_8S);
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
      // trqbva da go obrabotim i izpratim na sledvashtiq paketa 
      receivePacket();
    }  
  }

  if(Serial.available()){
    mySerialTo.write(Serial.read());

    String command = Serial.readStringUntil('\n');
    Serial.println(command); 
    BT.print(command);  
  }

  if (BT.available()){
    String receive = BT.readStringUntil('\n');
    Serial.println(receive);
    
    if(receive.toInt() == 1){
      drink1();
      reset();      
    }

    if(receive.toInt() == 2){
      drink2();
      reset();      
    }

    if(receive.toInt() == 3){
      drink3();
      reset();      
    }

    if(receive.toInt() == 4){
      wdt_disable();
      drink4();
      reset();      
    }

    reset();  
  }  
}
