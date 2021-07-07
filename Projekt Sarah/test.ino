//In diesem Beispiel sind IN1 und IN2 mit den Arduino™ digital Pins 4 und 5 verbunden.
int IN1 = 4;
int IN2 = 5;
#define ON 1
#define OFF 0
void setup()
{//initialize the relay
relay_init();
}
void loop()
{//turn on RELAY_1
relay_SetStatus(ON, OFF);
//delay 2s
delay(2000);
//turn on RELAY_2
relay_SetStatus(OFF, ON);
//delay 2s
delay(2000);
}

//initialize the relay
void relay_init(void)
{//set all the relays  OUTPUT
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
//turn off all the relay
relay_SetStatus(OFF, OFF);
}

//set the status of relays
void relay_SetStatus(unsigned char status_1, unsigned char status_2)
{digitalWrite(IN1, status_1);
digitalWrite(IN2, status_2);
}