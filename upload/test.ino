const int vx1 =2;
const int vx2 =3;
const int vx3 =4;
const int vx4 =5;
const int pump =6;
int pushButton_s2=12;

int mode = 0;
/*
0 = standby
10 = auto
21 = manual valvx1
22 = manual valve2
23 = manual valve3
24 = manual valve4
*/
bool buttonLock = 0;

void setup()
{
    pinMode(vx1, OUTPUT);
    pinMode(vx2, OUTPUT);
    pinMode (vx3, OUTPUT);
    pinMode(vx4, OUTPUT);
    pinMode(pump, OUTPUT);
    pinMode(pushButton_s2, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.print("this is a new progrramm");
  

}

void loop()
{

digitalWrite(vx4, HIGH);
 delay(5000);
 digitalWrite(vx4,LOW);
 delay(5000);
/*digitalWrite(x2 HIGH);
delay(1000);
digitalWrite vx3, HIGH);
delay(1000);
digitalWrite(vx4, HIGH);
delay(1000);
digitalWrite(pump, HIGH);
delay(1000);
digitalWrite(vx1, LOW);
delay(1000);
digitalWrite(x2 LOW);
delay(1000);
digitalWrite vx3, LOW);
delay(1000);
digitalWrite(vx4, LOW);
delay(1000);
digitalWrite(pump, LOW);
delay(1000); */



}
