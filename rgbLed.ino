// Define Pins
#define BLUE 6
#define GREEN 5
#define RED 3

void setup()
{
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, HIGH);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
}

// define variables
int redValue;
int greenValue;
int blueValue;

// main loop
void loop()
{
#define delayTime 100 // fading time between colors

redValue = 255; 
greenValue = 0;
blueValue = 0;

analogWrite(RED, redValue);
analogWrite(GREEN, greenValue);
analogWrite(BLUE, blueValue);
delay(5000);

redValue = 255; 
greenValue = 0;
blueValue = 0;



for(int i = 0; i < 255; i += 1) // fades out red bring green full when i=255
{
redValue -= 1;
greenValue += 1;
analogWrite(RED, redValue);
analogWrite(GREEN, greenValue);
delay(delayTime);
}

}
