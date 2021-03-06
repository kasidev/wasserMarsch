#include "irrigationMode.h"

extern byte outputByte;

int timings[]={7000,2000,5000,4000};

void valveCycler(int startValve, int endValve)
{
    Serial.print(startValve);
    Serial.print(" start valve//");
    Serial.print("end valve ");
    Serial.print(endValve);

    delay(5000);
    bitSet(outputByte,5);
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

    outputByte=0;
    updateShiftRegister();
        
}