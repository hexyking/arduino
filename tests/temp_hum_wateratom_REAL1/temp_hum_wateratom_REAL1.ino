                                                                                                                                                                                     #include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#define DHT11_PIN 3 //dht11 is NOT NATIVE GROVE, NOTE THE PIN d3-->d2
dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD I2C setup 5Volt
const byte nsum=10;
int tempPin = 0;
int atomizationPin = 4;
int H = 0;
unsigned int sensorValue2 = 0;  // variable to store the value coming from the sensor
unsigned int sensorValue3 = 0;  // variable to store the value coming from the sensor

void setup()
{
Wire.begin();
//Serial.begin(9600);
pinMode(atomizationPin, OUTPUT);
delay(500);
Serial.println("DHT11 Temp&Humidity AND wateratomizer  \n\n");
lcd.begin();
delay(500);
}

void loop()
{

//Serial.print("/********************************");
//Serial.print("\n");
//DHT11 BLUE TEMP SENSOR PRINT LOOP
//Serial.print("DHT11 Temperature = ");
//Serial.print(DHT.temperature);
//Serial.println("C       *");
//Serial.print("DHT11  Humidity =  ");
//Serial.print(DHT.humidity);
//Serial.println("%        *");
//Serial.println();
//Serial.println("H = ");
//Serial.println(H);
//Serial.println(" %           *");
//Serial.print("********************************//");
//Serial.print("\n");

int chk11 = DHT.read11(DHT11_PIN);
lcd.setCursor(0,0);
lcd.print("LadyGraph  DHT11");
lcd.setCursor(0,1);
lcd.print(DHT.humidity);
lcd.print("%    ");
lcd.print(DHT.temperature);
lcd.print("C");

delay(500);

H = (DHT.humidity);

if(H < 95 ){
  digitalWrite(atomizationPin, HIGH);
  delay(10000);
  digitalWrite(atomizationPin, LOW);
    }
    chk11 = 0;
}
//TODO:
// average the value 
//IF LOOP FIX: create functions for atomizer and for lcd and for sensorread

//void runatomizer()
//{
//IF etcetcetc;
//}

//void lcdprint()
//{
//print etcetcetc;
//}

//void loop(){
//runatomizer();
//lcdprint();
//}
