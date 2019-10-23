#include <TM1637Display.h>

#define ArduinoAnalogInput A1
#define ledRojo 10
#define ledVerde1 11
#define ledVerde2 12
#define ledVerde3 13
#define CLK 3
#define DIO 2

TM1637Display display(CLK, DIO);
int resistance = 0;
float buff;

void setup() {
  //pinMode(ArduinoAnalogInput, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledVerde3, OUTPUT);
  
  display.setBrightness(0x0f);
  display.showNumberDec(0, false);
  
  Serial.begin(9600);
}

void loop() {
  calcResistance();
  delay(1000);
}

void calcResistance()
{
  int adcVal = analogRead(ArduinoAnalogInput);
  buff = adcVal; buff=buff*5; buff = buff/1024;  
  float voltaje = buff;
  resistance = ((5/voltaje)-1)*1000;
  Serial.println(resistance);
  
  if(resistance < 3)
  {
    //Not readed
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledVerde3, LOW);
    display.showNumberDec(0, false);
  }
  else if(resistance <= 9999)
  {
    //Kilo Ohms
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde1, HIGH);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledVerde3, LOW);
    display.showNumberDec(resistance, false);
  }
  else if(resistance <= 1000000)
  {
    //Mega Ohms
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, HIGH);
    digitalWrite(ledVerde3, LOW);
    display.showNumberDec(resistance/1000, false);
  }
  else if(resistance <= 1000000000)
  {
    //1000 Mega ohms
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledVerde3, HIGH);
    display.showNumberDec(resistance/1000000, false);
  }
}
