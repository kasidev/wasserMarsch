#include "WiFiWebClient.h"
unsigned long lastRequest;
void setup(){
Serial.begin(9600);
connect2Network();

}

void loop(){
unsigned long nextIrrigation;


httpGetJSON(nextIrrigation,lastRequest,"wassermarsch.azurewebsites.net","GET / HTTP/1.1");
//Serial.println("this is new code");
delay(5000);
Serial.print("The next irrigation will take place on: ");
Serial.println(nextIrrigation);
delay(5000);
//sleepDelay(6000);
/*
Next step:
- go into sleep mode
- let the pump running if it is the time

*/
//https://github.com/n0m1/Sleep_n0m1
    

}

//void sleepDelay(unsigned long sleepTime){};
