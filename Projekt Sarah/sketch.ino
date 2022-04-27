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


httpGetJSON(currentTime,updateIntervall,nextIrrigation,lastRequest,"wassermarsch.azurewebsites.net","GET /getparams HTTP/1.1");
//Serial.println("this is new code");
Serial.println("---------New Loop--------");
if (currentTime<nextIrrigation)
{
    Serial.print("The next irrigation will take place on: ");
    Serial.println(nextIrrigation);
}
else
{
    Serial.println("no irrigation planned");
    Serial.print("last irrigation took place @");
    Serial.println(lastIrrigation);
}

Serial.print("Update Intervall: ");
Serial.println(updateIntervall);

if (currentTime>nextIrrigation && nextIrrigation > lastIrrigation)
{
    irrigation();
    lastIrrigation = nextIrrigation;
}
delay(10000);



/*
Next step:
-add an off switch in the webapp
-add a stop/start switch in the webapp
-report last irrigation to the webapp via post
- go into sleep mode, not possible
*/
    

}

void irrigation(){

Serial.print("------");
Serial.println("Start the pump ");
digitalWrite(LED_BUILTIN, HIGH);
digitalWrite(pump,HIGH);
delay(40000);
digitalWrite(LED_BUILTIN, LOW);
digitalWrite(pump,LOW);
Serial.println("stop the pump ");

}
