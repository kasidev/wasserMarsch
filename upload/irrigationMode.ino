const int v1 =2;
//v1 - potatoes
const int v2 =3;
const int v3 =4;
//v3 tomatoes
const int v4 =5;
const int pump =6;
int pushButton_s2=12;

int mode = 0;
/*
0 = standby
10 = auto
21 = manual valv1
22 = manual valve2
23 = manual valve3
24 = manual valve4
*/
bool buttonLock = 0;

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
    //EEPROM.clear();
    
    //delay(5*24*60*60*1000);
    //EEPROM.write(0, 1);
    Serial.write("test");
    if(digitalRead(pushButton_s2) == LOW && buttonLock == 0)
     {
        digitalWrite(pump,HIGH);
        delay(500);
        digitalWrite(v3,HIGH);
        delay(10000);
        digitalWrite(v3,LOW);
        digitalWrite(pump,LOW);
        delay(500);
        digitalWrite(pump,HIGH);
        delay(500);
        digitalWrite(v1,HIGH);
        delay(10000);
        digitalWrite(pump,LOW);
        digitalWrite(v1,LOW);
        
       Serial.println("button pressed");
        buttonLock=1;
    } 

    if(digitalRead(pushButton_s2)== HIGH)
    {
        buttonLock =0;
    }

    




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
