#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Set up LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD I2C setup

// Set up Wifi (Grove UART)
const byte rxPin = 0;
const byte txPin = 1;
SoftwareSerial Wifi = SoftwareSerial(rxPin, txPin);

// Command to be tested
char cmd[] = "AT+CWLAP";
//char cmd[] = "AT+CWJAP_CUR=\"UPC241FD79\",\"hzp6mdHxaneb";


// Sends command both to Monitor and Wifi
void sendCmd() {
  Serial.println(cmd);
  Wifi.print(cmd);
}

void setup() {

  // Set up Monitor
  Serial.begin(115200);

  // Set up Wifi
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Wifi.begin(115200);
  //Wifi.print("AT+CWJAP_CUR=\"UPC241FD79\",\"hzp6mdHxaneb");
  // Send command
  //sendCmd();
  
}

void loop() {
   
    sendCmd();
    
  // Read response from Wifi - this is the part that causes issues
  while (Wifi.available() > 0) {
    char c = Wifi.read();
    Serial.print(c);
  }
  delay(5000);
  
}
