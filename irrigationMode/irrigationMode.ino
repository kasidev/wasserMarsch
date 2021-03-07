
#include "modeCode.h"

const int latchPin =4;
const int dataPin =2;
const int clockPin =7;
int pushButton_s2=12;

byte outputByte = 0;
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
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(pushButton_s2, INPUT_PULLUP);
    Serial.begin(9600);
    blinkAll(4);

}

void loop()
{

    if(digitalRead(pushButton_s2) == LOW && buttonLock == 0)
    {
        Serial.println("Button pressed");
        switch (mode)
        {
        case 0:
            mode = 10;
            break;
        case 10:
            mode = 21;
            break;
        case 21:
            mode = 22;
            break;
        case 22:
            mode = 23;
            break;
        case 23:
            mode = 24;
            break;
        case 24:
            mode = 0;
            break;

        default:
            changeMode();
            break;
        
        }
        changeMode();
        buttonLock=1;
        
    }

    if(digitalRead(pushButton_s2)== HIGH)
    {
        buttonLock =0;
    }


    if (Serial.available())

    {
        char charSerial = Serial.read(); 
        
        if(charSerial >= '0' && charSerial <= '7')
        {
            int modeUpdate = charSerial - '0';
            Serial.print("character received ");
            Serial.print(modeUpdate);
            bitSet(outputByte,modeUpdate);
            updateShiftRegister();
        }

        if (charSerial == 'x')
        {
            outputByte=0;
            updateShiftRegister();
        }        
    }
}

void updateShiftRegister()
{
    digitalWrite(latchPin,LOW);
    //Serial.print(" outputByte update: ");
    //Serial.println(outputByte,BIN);
    shiftOut(dataPin,clockPin,LSBFIRST,outputByte);
    digitalWrite(latchPin, HIGH);

}

void changeMode()
{
    Serial.print("mode changed to: ");
    Serial.println(mode);
    switch (mode)
    {
    case 10:
        blinkAutoMode();
        if (digitalRead(pushButton_s2) == LOW && buttonLock == 0)
        {
            valveCycler(1,4);
        }     
        break;

    case 21:
        valveCycler(1,1);
        break;
    case 22:
        valveCycler(2,2);     
        break;
    case 23:
        valveCycler(3,3);     
        break;
    case 24:
        valveCycler(4,4);
        break;
    
    }
    
    

}

void blinkAll(int blinkies)
{
    int counter = 0;
    do
    {
        bitSet(outputByte,1);
        bitSet(outputByte,2);
        bitSet(outputByte,3);
        bitSet(outputByte,4);
        bitSet(outputByte,5);
        updateShiftRegister();
        delay(1000);
        outputByte=0;
        updateShiftRegister();
        delay(1000);
        counter ++;
    } while (counter < blinkies);

}

void blinkAutoMode()
{
    int counter = 0;
    do
    {
        for (int i = 1; i <= 4; i++)
            {
            bitSet(outputByte,i);
            updateShiftRegister();
            delay(100);
            bitClear(outputByte,i);
            updateShiftRegister(); 
            }
    
        for (int i = 4; i >= 1; i--)
            {
            bitSet(outputByte,i);
            updateShiftRegister();
            delay(100);
            bitClear(outputByte,i);
            updateShiftRegister(); 
            }

        counter ++;
    } while (counter < 5);
    
          
    

}