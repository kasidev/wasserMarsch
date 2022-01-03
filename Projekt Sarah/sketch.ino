#include "WiFiWebClient.h"
unsigned long lastRequest;
unsigned long lastIrrigation;
unsigned long nextIrrigation;
unsigned long updateIntervall;
unsigned long currentTime;
const int pump =6;


void setup(){
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);

pinMode(pump, OUTPUT);
digitalWrite(pump,LOW);

updateIntervall = 30000;
lastIrrigation = 1;

Serial.begin(9600);
connect2Network();

}

void loop(){


httpGetJSON(currentTime,updateIntervall,nextIrrigation,lastRequest,"wassermarsch.azurewebsites.net","GET / HTTP/1.1");
//Serial.println("this is new code");
Serial.println("---------New Loop--------");
Serial.print("The next irrigation will take place on: ");
Serial.println(nextIrrigation);
Serial.print("Update Intervall: ");
Serial.println(updateIntervall);
if (currentTime>nextIrrigation && nextIrrigation > lastIrrigation)
{
    irrigation();
    lastIrrigation = nextIrrigation;
}
delay(updateIntervall);



/*
Next step:
- go into sleep mode, not possible
- let the pump running if it is the time

*/
//https://github.com/n0m1/Sleep_n0m1
    

}

void irrigation(){

Serial.print("------");
Serial.println("Start the pump ");
digitalWrite(LED_BUILTIN, HIGH);
digitalWrite(pump,HIGH);
delay(20000);
digitalWrite(LED_BUILTIN, LOW);
digitalWrite(pump,LOW);
Serial.println("stop the pump ");

}
