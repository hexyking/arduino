#include <Wire.h>
#include <dht.h>
#define DHT22_PIN 7 // Pin sensor is connected to
dht DHT;  // Creats a DHT object

void setup()
{
Serial.begin(9600);
delay(500);
Serial.println("DHT22 Temp & Humidity to UART Wifi \n\n");
delay(500);
}

void loop()
{

int readsensor = DHT.read22(DHT22_PIN);
Serial.print("DHT22 Temperature = ");
Serial.println(DHT.temperature);
Serial.print("DHT22  Humidity = ");
Serial.print(DHT.humidity);
Serial.print("%\n");
Serial.println();


delay(5000);
}
