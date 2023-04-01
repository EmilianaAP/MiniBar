#include <SoftwareSerial.h>

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
// Arduino id:
int id = 0;

#define rxPinFrom 5
#define txPinFrom 4
#define rxPinTo 2
#define txPinTo 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerialTo =  SoftwareSerial(rxPinTo, txPinTo);
SoftwareSerial mySerialFrom = SoftwareSerial(rxPinFrom, txPinFrom);

void generatePouringFromBottlePacket(char bottleId, char quantity) {
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

void setup(){ 
  clearTxBuffer();
  mySerialTo.begin(9600);
  mySerialFrom.begin(9600);
  Serial.begin(9600);

  Serial.println("\nThis arduino id: ");
  Serial.println(id);

  char id_ = '3';
  char quantity = '8';
  //generatePouringFromBottlePacket(id_, quantity);      
}

void loop() {
    /*if(mySerialTo.available()){
      tmpRx = mySerialTo.read();
      
    if(nextFree == 0 && tmpRx == PACKET_HEADER) {
      clearRxBuffer();
    }

    if(nextFree == 2) {
      dataToReceive = tmpRx-'0';  // store how many bytes we have to receive - data len   
    }

    bufferRx[nextFree++] = tmpRx;  

    //Serial.println("abababba ");

    if(dataToReceive == (nextFree - 3)){    
      // trqbva da go obrabotim i izpratim na sledvashtiq paketa 
      //receivePacket();
    }  
  }*/

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

    //state = Serial.read()    

    //Coctails:
    /*
    if(state == 'a'){
      Serial.println("<First coctail name> is making");
      char id_ = '3';
      char quantity = '8';
      generatePouringFromBottlePacket(id_, quantity); 
      id_ = '2';
      quantity = '3';
      generatePouringFromBottlePacket(id_, quantity);       
                  
    }    

    */

  }
}
