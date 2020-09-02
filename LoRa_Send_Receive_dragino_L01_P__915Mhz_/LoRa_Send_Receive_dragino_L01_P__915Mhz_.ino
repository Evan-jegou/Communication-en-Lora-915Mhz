#include <SPI.h>
#include <LoRa.h>
#include <Console.h>
#include <Process.h>
int HEART_LED = A1;

// Set center frequency
uint32_t freq = 915E6;
int SF = 12, Denominator = 5;
long SBW = 125E3;

long old_time = millis();
long new_time;
long status_update_interval = 30000; //update Status every 30 seconds.

//Receiver LoRa packets
void receivepacket() 
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();

  if (packetSize) 
  {
    // received a packet
    Console.print("Received packet '");
    // read packet
    int i = 0;
    char message[256];
    while (LoRa.available()) 
    {
      message[i] = LoRa.read();
      i++;
    }
    Console.println(message);
    
    delay(10);
                              Accuse_reception ();
    delay(10);
   
    old_time = new_time;
  }
}


void Accuse_reception ()
{
    LoRa.beginPacket();
    Console.println("Envoie accusé récéption");
    LoRa.print("Bien_reçu");
    LoRa.endPacket();  
}


void show_config()
{
  Console.print("The frequency is "); Console.print(freq); Console.println("Hz");
  Console.print("The spreading factor is "); Console.println(SF);
  Console.print("The coderate is "); Console.println(Denominator);
  Console.print("The single bandwith is "); Console.print(SBW); Console.println("Hz");
}

void setup() 
{
  Bridge.begin(115200);
  Console.begin();
  //  while (!Console);
  pinMode(HEART_LED, OUTPUT);

  Console.println("LoRa Receiver");

  if (!LoRa.begin(freq)) 
  {
    Console.println("Starting LoRa failed!");
    while (1);
  }
  
  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(SBW);
  LoRa.setCodingRate4(Denominator);
  LoRa.setSyncWord(0x34);
  LoRa.receive(0);
                                  show_config();
}

void loop() 
{
                                  receivepacket();
  new_time = millis();
                                  
  if ((new_time - old_time) > status_update_interval) 
  {
    Console.println("");
    Console.println("not receive overtime");
    
    LoRa.beginPacket();
    LoRa.print("Es-tu-là ?");
    Console.println("Es-tu-là ?");
    LoRa.endPacket();    
    old_time = new_time;
  }
}
