const int microPin =2;
const int diodetest = 12;


bool microOn = false;
void setup()
{
    Serial.begin(9600);
    pinMode(microPin, INPUT); 
    attachInterrupt(digitalPinToInterrupt(microPin), HandleMic, RISING);
 
    pinMode(diodetest, OUTPUT); 
}

void loop()
{
    
}

void HandleMic()
{
    microOn = !microOn;

}

