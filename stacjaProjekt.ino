#include <dht11.h>
#define DHT11PIN 3

// zajete 2-7
const int microPin =2;
const int keyPadRow1 = 4;
const int keyPadColumn1 = 5;
const int keyPadColumn2 = 6;
const int keyPadColumn3 = 7;

unsigned long actualTime = 0;
unsigned long savedTime = 0;

dht11 DHT11;

bool microOn = false;
void setup()
{
    Serial.begin(9600);
    pinMode(microPin, INPUT);  
  //  attachInterrupt(digitalPinToInterrupt(microPin), HandleMic, RISING); 
    pinMode(keyPadRow1, OUTPUT);
    digitalWrite(keyPadRow1, HIGH);
}

void loop()
{ 
    //Serial.println();
      // wypisywanie informacji na guzik
      if(microOn)
      {
        int chk = DHT11.read(DHT11PIN);
        Serial.print("Humidity (%): ");
        Serial.println((float)DHT11.humidity, 2);
        Serial.print("Temperature  (C): ");
        Serial.println((float)DHT11.temperature, 2);
        delay(2000);
      }

     actualTime = millis();
     if (actualTime - savedTime >= 200UL)
      { 
        // Dla wcisnietej 1
        if(HandleKey(keyPadColumn1,1))
        {

        }
       // Dla wcisnietej 2
        if( HandleKey(keyPadColumn1,2))
        {

        }
         // Dla wcisnietej 2        
        if (HandleKey(keyPadColumn1,3);)
        {

        }
        savedTime = actualTime;
      }
}

bool HandleKey(int Pin)
{
  bool val = false;
  pinMode(Pin, INPUT); 
  //Serial.println("in Handle");
  if(digitalRead(Pin) == HIGH)
  {
    Serial.println(num);
    val = true;
  }
  pinMode(Pin, OUTPUT);
  return val;
}
void HandleMic()
{
    microOn = !microOn;

}

