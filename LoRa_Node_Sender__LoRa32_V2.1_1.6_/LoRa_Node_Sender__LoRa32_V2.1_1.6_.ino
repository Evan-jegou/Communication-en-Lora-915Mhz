#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  

int SF = 12, Denominator = 5;
long SBW = 125E3;

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     23   // GPIO23 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6


unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;

 

void setup() 
{
  pinMode(16,OUTPUT);
  pinMode(2,OUTPUT);
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  
  if (!LoRa.begin(915E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(SBW);
  LoRa.setCodingRate4(Denominator);
  LoRa.setSyncWord(0x34); 
 
  //LoRa.onReceive(cbk);
 //  LoRa.receive();
  Serial.println("init ok");   
  delay(1500);
}


void loop() 
{
  Serial.println(String(counter));

  // send packet
  LoRa.beginPacket();
  LoRa.print(" hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;           
}
