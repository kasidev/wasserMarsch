#include <EEPROM.h>

const int v1 =2;
//v1 - potatoes
const int v2 =3;
const int v3 =4;
//v3 tomatoes
const int v4 =5;
const int pump =6;
int pushButton_s2=12;

int mode = 0;

bool buttonLock = 0;
bool irrigationStart = 0;
unsigned long shift = 0;

void setup()
{
    pinMode(v1, OUTPUT);
    pinMode(v2, OUTPUT);
    pinMode (v3, OUTPUT);
    pinMode(v4, OUTPUT);
    pinMode(pump, OUTPUT);
    pinMode(pushButton_s2, INPUT_PULLUP);
    Serial.begin(9600);
    blinkAll(1);
    
  

}

void loop()
{
    
    irrigationStart=checkTime(millis()-shift);

    if(irrigationStart == 1)
     {
        off();
        blinkAll(1);        
        digitalWrite(pump,HIGH);
        delay(500);
        digitalWrite(v3,HIGH);
        delay(600000);
        digitalWrite(v3,LOW);
        digitalWrite(pump,LOW);
        delay(500);
        digitalWrite(pump,HIGH);
        delay(500);
        digitalWrite(v1,HIGH);
        delay(600000);
        digitalWrite(pump,LOW);
        digitalWrite(v1,LOW);
        shift = millis();
    } 

    if (digitalRead(pushButton_s2) == LOW && buttonLock == 0)
    {
         //shift = millis();
         Serial.println("button pressed");
         buttonLock = 1;
         
    }
    if (digitalRead(pushButton_s2) == HIGH && buttonLock == 1)
    {
        buttonLock = 0;
        off();
    }

}

bool checkTime(unsigned long time)
{
    bool result = 0;
    unsigned long interval = ((56.0 * 60 * 60) * 1000) / 4.0;
    //unsigned long interval = ((20) * 1000) / 4.0;
    //Serial.println(interval);
    if (time<interval*1)
    {
        showStatus(0);
    }
    if (time>interval*1)
    {
        showStatus(1);
    }

    if (time>interval*2)
    {
        showStatus(2);
        //digitalWrite(v2,HIGH);
    }
    if (time>interval*3)
    {
        showStatus(3);
        //digitalWrite(v3,HIGH);
    }
    if (time>interval*4)
    {
        showStatus(4);
        //digitalWrite(v4,HIGH);
        result = 1;
    }
    return result;
    
}

void showStatus(int status)
{
    switch (status)
    {
    case 1:
        if (buttonLock == 1)
        {
            digitalWrite(v1,HIGH);
        }
        break;
    case 2:
        if (buttonLock == 1)
        {
            digitalWrite(v1,HIGH);
            digitalWrite(v2,HIGH);
        }
        break;
    case 3:
        if (buttonLock == 1)
        {
            digitalWrite(v1,HIGH);
            digitalWrite(v2,HIGH);
            digitalWrite(v3,HIGH);
        }
        break;
    case 0:
        if (buttonLock == 1)
        {
            digitalWrite(v1,HIGH);
            digitalWrite(v2,HIGH);
            digitalWrite(v3,HIGH);
            digitalWrite(v4,HIGH);
        }
        break;
 
    
    default:
        break;
    }
}

void off()
{
    digitalWrite(v1,LOW);
    digitalWrite(v2,LOW);
    digitalWrite(v3,LOW);
    digitalWrite(v4,LOW);
    digitalWrite(pump,LOW);
}

void blinkAll(int blinkies)
{
    int counter = 0;
    do
    {
        digitalWrite(v1, HIGH);
        delay(500);
        digitalWrite(v2, HIGH);
        delay(500);
        digitalWrite(v3, HIGH);
        delay(500);
        digitalWrite(v4, HIGH);
        delay(500);
        digitalWrite(v4, LOW);
        delay(500);
        digitalWrite(v3, LOW);
        delay(500);
        digitalWrite(v2, LOW);
        delay(500);
        digitalWrite(v1, LOW);
        delay(500);
        counter ++;
    } while (counter < blinkies);

}
