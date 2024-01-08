#include <dht11.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT11PIN 3

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// zajete 2-7
const int microPin =2;
const int keyPadRow1 = 4;
const int keyPadColumn1 = 5;
const int keyPadColumn2 = 6;
const int keyPadColumn3 = 7;
const int buzzerPin = 8;

unsigned long actualTime = 0;
unsigned long savedTime = 0;
unsigned long oledIdleTime = 0;

bool oledWorking = false;

dht11 DHT11;

bool microOn = false;
void setup()
{
    Serial.begin(9600);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }
    pinMode(microPin, INPUT);  
  //  attachInterrupt(digitalPinToInterrupt(microPin), HandleMic, RISING); 
    pinMode(keyPadRow1, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(keyPadRow1, HIGH);

    display.clearDisplay();
    display.setTextSize(1);            
    display.setTextColor(SSD1306_WHITE);     
    display.setCursor(0,0);     
    display.display();
}

void loop()
{ 
    display.setCursor(0,0);    
    //Serial.println();
      // wypisywanie informacji na guzik

     actualTime = millis();
     if (actualTime - savedTime >= 200UL)
      { 
        // Dla wcisnietej 1
        if(HandleKey(keyPadColumn1))
        {
            int chk = DHT11.read(DHT11PIN);
            Serial.print("Humidity (%): ");
            Serial.println((float)DHT11.humidity, 2);
            Serial.print("Temperature  (C): ");
            Serial.println((float)DHT11.temperature, 2);

          display.clearDisplay();
          display.println("Pressed 1");
          display.display();
          oledIdleTime = actualTime;
          oledWorking = true;
          digitalWrite(buzzerPin, HIGH);
        }
       // Dla wcisnietej 2
        else if( HandleKey(keyPadColumn2))
        {
          display.clearDisplay();
          display.println("Pressed 2");
          display.display();
          oledIdleTime = actualTime;
          oledWorking = true;
          digitalWrite(buzzerPin, HIGH);
        }
         // Dla wcisnietej 2        
        else if (HandleKey(keyPadColumn3))
        {
          display.clearDisplay();
          display.println("Pressed 3");
          display.display();
          oledIdleTime = actualTime;
          oledWorking = true;
          digitalWrite(buzzerPin, HIGH);
        }
        else
        {
          savedTime = actualTime;
          digitalWrite(buzzerPin, LOW);
        }
      }
      if(microOn)
      {
        microOn = !microOn;
        //for(int i=0; i)
      }

      if(oledWorking)
      {
          if(actualTime - oledIdleTime >= 4000)
          {
            display.clearDisplay();
            display.display();
            oledWorking = false;
            oledIdleTime = actualTime;
          }
      }
}

bool HandleKey(int Pin)
{
  bool val = false;
  pinMode(Pin, INPUT); 
  //Serial.println("in Handle");
  if(digitalRead(Pin) == HIGH)
  {
    val = true;
  }
  pinMode(Pin, OUTPUT);
  return val;
}
void HandleMic()
{
    microOn = !microOn;

}

