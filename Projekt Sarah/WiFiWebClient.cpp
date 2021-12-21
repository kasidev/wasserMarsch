

/*
  Repeating WiFi Web Client

 This sketch connects to a a web server and makes a request
 using a WiFi equipped Arduino board.

 created 23 April 2012
 modified 31 May 2012
 by Tom Igoe
 modified 13 Jan 2014
 by Federico Vanzati

 http://www.arduino.cc/en/Tutorial/WifiWebClientRepeating
 This code is in the public domain.
 */


#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include "arduino_secrets.h" 
#include <StreamUtils.h>
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)
int status = WL_IDLE_STATUS;


// Initialize the WiFi client library
WiFiClient client;

// 
WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

// server address:
//char server[] = "echo.jsontest.com";
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 20; // delay between updates, in milliseconds

  //Initialize serial and wait for port to open:

  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/
//connect to the registed WiFi Network
void connect2Network(){
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  
  
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    timeClient.begin();

    // wait 10 seconds for connection:
    delay(10000);
    printWifiStatus();
  }
  // you're connected now, so print out the status:
  printWifiStatus();
  
}

void httpGetJSON(unsigned long &nextIrrigation,unsigned long &lastRequest,String host, String url) {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  
  while (client.available()) {
    Serial.println("try to get data");
    //skip response header 

    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      return;
      
    }else
    {
      Serial.println(F("Valid response"));
      //Serial.print(client.readString());
      
      const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
      DynamicJsonDocument doc(capacity);
      DeserializationError error = deserializeJson(doc, client);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        client.stop();
        return;
        
      }
      //const char* test = doc["nextIrrigation"];
      long test[3]={doc["autoIntervall"],doc["nextIrrigation"]};
      Serial.println(test[1]);
      Serial.println("test");
      return;

      
      /*
      // if ten seconds have passed since your last connection,
      // then connect again and send data:
      timeClient.update();
      unsigned long currentTime = timeClient.getEpochTime();
      Serial.println(currentTime - lastRequest > postingInterval);
      if (currentTime - lastRequest > postingInterval) {
        httpRequest(host,url);
      }
      */


      
    }
    
  }
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  timeClient.update();
  unsigned long currentTime = timeClient.getEpochTime();
  Serial.println(currentTime - 0 > postingInterval);
  if (currentTime - 0 > postingInterval) {
    httpRequest(host,url);
  }
  //return responseArray; 

  Serial.println("end of function");
  return;

}


// this method makes a HTTP connection to the server:
void httpRequest(String host, String url) {
  // close any connection before send a new request.
  // This will free the socket on the NINA module
  client.stop();
  
  char serverAdress[host.length()+1];
  host.toCharArray(serverAdress,host.length()+1);


  // if there's a successful connection:
  if (client.connect(serverAdress, 80)) {
    Serial.println("connecting....");
    // send the HTTP GET request:
    client.println(url);
    client.println("Host: "+host);
    client.println("User-Agent: ArduinoWiFi/1.1 Sarah");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    delay(1000);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
