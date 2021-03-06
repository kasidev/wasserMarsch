// Define Pins
const int pinBlue = 5;
const int pinGreen = 6;
const int pinRed = 3;

void setup()
{
pinMode(pinBlue, OUTPUT);
pinMode(pinGreen, OUTPUT);
pinMode(pinRed, OUTPUT);

}

// define variables
int redValue;
int greenValue;
int blueValue;

// main loop
void loop()
{
    setColor(0,255,0,500);//green
    setColor(0,0,0,500);

    setColor(255,0,0,500);//red
    setColor(0,0,0,500);

    setColor(0,0,255,500);//blue
    setColor(0,0,0,500);
 


delay(5000);
setColor(0,255,0,500);
for ( int colorShift = 0; colorShift < 255; colorShift++)
{
    setColor(0 + colorShift,255 - colorShift,0,39);
}
//255,0,0 red

for ( int colorShift = 0; colorShift < 255; colorShift++)
{
    setColor(255 - colorShift,0,0 + colorShift,39);
}
//0,0,255 blue

for ( int colorShift = 0; colorShift < 255; colorShift++)
{
    setColor(0 + colorShift,0 + colorShift,255 - colorShift,39);
}
//255,255,0 yellow

for ( int colorShift = 0; colorShift < 255; colorShift++)
{
    setColor(255,255,0 + colorShift,39);
}

}
void setColor(int red, int green, int blue, int tDelay)
{
    analogWrite(pinRed,red);
    analogWrite(pinGreen,green);
    analogWrite(pinBlue,blue);
    delay(tDelay);
}


