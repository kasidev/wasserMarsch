#include "irrigationMode.h"

extern byte outputByte;
extern int pushButton_s2;
extern bool buttonLock;

int timings[]={7000,2000,5000,4000};

void valveCycler(int startValve, int endValve)
{
    
    for (int i = startValve; i <= endValve; i++)
    {
        bitSet(outputByte,i);        
        
    }
    updateShiftRegister();
    delay(3000);

    if (digitalRead(pushButton_s2) == LOW && buttonLock == 0)
    {
        outputByte=0;
        bitSet(outputByte,6);
        updateShiftRegister();
        Serial.print(startValve);
        Serial.print(" start valve//");
        Serial.print("end valve ");
        Serial.println(endValve);


        delay(5000);
        
        bitClear(outputByte,6);
        updateShiftRegister();
        delay(1000);


        for (int i = startValve; i <= endValve; i++)
        {
            bitSet(outputByte,i);
            updateShiftRegister();
            delay(timings[i-1]);
            bitClear(outputByte,i);
            updateShiftRegister();
            delay(500);
        }

    }
    outputByte=0;
    bitSet(outputByte,6);
    updateShiftRegister();

    

        
}