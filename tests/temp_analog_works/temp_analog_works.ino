                                                                                                                                                                                     #include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <Wire.h>
#include <Digital_Light_TSL2561.h>

#define DHT22_PIN 8
dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD I2C setup

int val;
int tempPin = 0;

void setup()
{
Wire.begin();
Serial.begin(9600);
TSL2561.init();
delay(500);
Serial.println("DHT11/DHT22 Temp&Humidity AND TSL2561 digital light sensor data  \n\n");
lcd.begin();
delay(500);
}

void loop()
{
Serial.print("********************************");
Serial.print("%\n");


//DHT22 WHITE TEMP SENSOR LOOP
int chk22 = DHT.read22(DHT22_PIN);
Serial.print("DHT22 Temperature = ");
Serial.println(DHT.temperature);
Serial.print("DHT22  Humidity = ");
Serial.print(DHT.humidity);
Serial.print("%\n");
Serial.println();
lcd.setCursor(0,0);
lcd.print("LadyGraph  DHT22");
lcd.setCursor(0,1);
lcd.print(DHT.humidity);
lcd.print("%    ");
lcd.print(DHT.temperature);
lcd.print("C");
delay(5000);

//TSL2561 LIGHT SENSOR LOOP
Serial.print("Light value is: ");
Serial.println(TSL2561.readVisibleLux());
Serial.print("Lux");
lcd.setCursor(0,0);
lcd.print("LadyGraph  Light");
lcd.setCursor(0,1);
lcd.print(TSL2561.readVisibleLux());
lcd.print(" Lux");
lcd.print("             ");
delay(5000);
}
