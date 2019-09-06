/*
 php logger
*/

#include <SPI.h>
#include <WiFiNINA.h>
#include <RTCZero.h>
//#include <WiFiNINA.h> //Include this instead of WiFi101.h as needed
#include <WiFiUdp.h>
#include <dht.h>
#define DHT22_PIN 1
dht DHT;

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// server address:
//char server[] = "www.arduino.cc";
char server[] = "www.ladygraph.epizy.com";

bool sendRequest = true; // used to understand if the http request must be sent

/* Create an rtc object 
This solution allows you to do something else between the interrupts 
because the code execution flows without being blocked by any big delay() function. 
You can also combine this tutorial with the WiFi RTC to automatically set the time of the RTC.*/
RTCZero rtc;

/* Change these values to set the current initial time */
const byte seconds = 50;
const byte minutes = 00;
const byte hours = 17;

/* Change these values to set the current initial date */
const byte day = 12;
const byte month = 05;
const byte year = 19;

void setup() {
  Serial.begin(115200);
  Serial.println("DHT22 Temp&Humidity sensor data online php logger \n\n");
  connectToAP();
  printWiFiStatus();
  httpRequest();
  listenToClient();
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  rtc.setAlarmTime(0, 0, 0);    //in this way the request is sent every minute at 0 seconds
  rtc.enableAlarm(rtc.MATCH_SS);

  rtc.attachInterrupt(alarmMatch);
}

void loop() {

   if (sendRequest) {
    sendRequest = false;
    httpRequest();
    listenToClient(); 
   }
//  int chk22 = DHT.read22(DHT22_PIN);
//  Serial.print("DHT22 Temperature = ");
//  Serial.println(DHT.temperature);
//  Serial.print("DHT22  Humidity = ");
//  Serial.print(DHT.humidity);
//  Serial.print("%\n");
//  delay(5000);
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  sendRequest = false;
  // Print request time
  Serial.println();
  Serial.print("Request sent @ ");
  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());
  Serial.println();
  Serial.println();

  if (client.connect(server, 80)) {
    // Make a HTTP request:
          Serial.println("connecting...");
      
          client.println("GET /data_writer.php?value=103 HTTP/1.0");     // Path only, not the complete URI
          client.println("Host: www.ladygraph.epizy.com");
          client.println("User-Agent: ArduinoWiFi/1.1");
          client.println("Connection: close");
          client.println();
    
//    Serial.println("connecting...");
//    client.print("GET /data_writer.php?"); 
//    client.print("value="); 
//    client.print("103"); 
//    client.println(" HTTP/1.1");
//    client.println("Host: www.ladygraph.epizy.com"); 
//    client.println("User-Agent: ArduinoWiFi/1.1");
//    client.println("Connection: close");
//    client.println();
//    client.println();
  
//    client.println("GET /asciilogo.txt HTTP/1.1");
//    client.println("Host: www.arduino.cc");
//    client.println("Connection: close");
//    client.println();
  }
  else {
    Serial.println("connection failed");
  }
}

void listenToClient()
{
  unsigned long startTime = millis();
  bool received = false;

  while ((millis() - startTime < 5000) && !received) { //try to listen for 5 seconds
    while (client.available()) {
      received = true;
      char c = client.read();
      Serial.write(c);
    }
  }
  client.stop();
  Serial.println();
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

//connecting to wifi
void connectToAP(){
  // check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void alarmMatch() {
  sendRequest = true;
}
