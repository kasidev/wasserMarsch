#include "WiFiWebClient.h"

void setup(){
Serial.begin(9600);
}

void loop(){
unsigned long lastRequest;
unsigned long nextIrrigation;

connect2Network();
httpGetJSON(nextIrrigation,lastRequest,"wassermarsch.azurewebsites.net","GET / HTTP/1.1");
//Serial.println("this is new code");
delay(5000);
Serial.println("The next irrigation will take place on: ");
Serial.print(nextIrrigation);
delay(5000);
    

}
