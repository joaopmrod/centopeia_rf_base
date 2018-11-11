//#include "EasyOta.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include "RF24.h"
#include <PacketSerial.h>
#include <EEPROM.h>

//PacketSerial_<SLIP, 0, 700> myPacketSerial;
//SLIPPacketSerial myPacketSerial;
PacketSerial_<SLIP, SLIP::END, 2000> myPacketSerial;

RF24 radio(D2,D8);

byte addresses[][6] = {"boias"};

char message[32] = "";

char cores[12][32];

char cor[32]="asdfghjklezxcvbnmqwertyudsiopoi";

//char cores2[][30] = {"asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu","asdfghjklgzxcvbnmqwertyuiopoiu"};

u8_t frame = 0;

void ping(){
    digitalWrite(LED_BUILTIN, 0);
}
void pong(){
    digitalWrite(LED_BUILTIN, 1);
}



void onPacketReceived(const uint8_t* buffer, size_t size)
{digitalWrite(LED_BUILTIN, 0);
  if (size==10*3){
    for(int i=0;i<size;i++){
      cores[i/27][i%27]=buffer[i];
  }
  frame++;
  digitalWrite(LED_BUILTIN, 1);
  }
}

long last=millis();


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 0);
    pinMode(D4, OUTPUT);
    digitalWrite(D4, 0);
    //Serial.begin(115200);
    //Serial.println();
    //Serial.println("Booting... ");
    //myPacketSerial.begin(115200);
    //myPacketSerial.setPacketHandler(&onPacketReceived);

    radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  //radio.setPALevel(RF24_PA_LOW);
  //radio.setDataRate(RF24_250KBPS);  
  radio.setDataRate(RF24_2MBPS);  
  radio.setChannel(60);
  radio.setAutoAck(false);
  radio.openWritingPipe(addresses[0]);

  

  digitalWrite(LED_BUILTIN, 1);
  delay(100);
  digitalWrite(LED_BUILTIN, 0);
  delay(100);
  digitalWrite(LED_BUILTIN, 1);
  delay(100);
  digitalWrite(LED_BUILTIN, 0);
  delay(100);
  digitalWrite(LED_BUILTIN, 1);
  delay(100);
  digitalWrite(LED_BUILTIN, 0);
  delay(100);
  digitalWrite(LED_BUILTIN, 1);

  digitalWrite(D4, 1);

}

void loop() {
    //myPacketSerial.update();
          cor[0]=4;
      cor[1]=frame;
       
    
    for (int i=0;i<12;i++){
      digitalWrite(D4, 0);
      
cor[2]=i;

      for (int k=0;k<27;k++){
        cor[k+5]=cores[i][k];
      }
                 
      radio.writeFast( &cor, sizeof(cor),true );
      radio.writeFast( &cor, sizeof(cor),true );
      radio.writeFast( &cor, sizeof(cor),true );
      radio.txStandBy();
      digitalWrite(D4, 1);
      //radio.write( &cor, sizeof(cor) );

    }

    cor[0]=5;

      radio.writeFast( &cor, sizeof(cor),true );
      //delayMicroseconds(15);
      radio.writeFast( &cor, sizeof(cor),true );
      radio.writeFast( &cor, sizeof(cor),true );
      radio.txStandBy();
      //delayMicroseconds(15);


  
  //for(int i=0;i<32;i++){
  //    cor[i]=random(200);
  //}

  if (millis()-last>16){
    last=millis();
    frame=frame+1;
  }

}








