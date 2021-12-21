#include "WiFiWebClient.h"

void setup(){
Serial.begin(9600);
connect2Network();

}

void loop(){
unsigned long lastRequest;
unsigned long nextIrrigation;


httpGetJSON(nextIrrigation,lastRequest,"wassermarsch.azurewebsites.net","GET / HTTP/1.1");
//Serial.println("this is new code");
delay(5000);
Serial.print("The next irrigation will take place on: ");
Serial.println(nextIrrigation);
delay(5000);
    

}
