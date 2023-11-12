/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe
  modified 11 Nov 2023
  by Kailin Luo

  This example code is in the public domain. Not the modified code from 2023.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define RX 3
#define TX 2
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

#define BAUDRATE 9600

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

// constants won't change. They're used here to set pin numbers:
const int onButtonPin = 5;  // the number of the pushbutton pin
const int offButtonPin = 6; // the number of the off button pin
const int LCDbuttonPin = 4;  //the number of the LCD button pin
// const int onPin = 12;    // the number of the on LED pin
// const int offPin = 13;   // the number of the off LED pin
const int LCDpin = 11;   // the number of the LCD pin
// variables will change:
int onButtonState = 0;  // variable for reading the pushbutton status
int offButtonState = 0;
int LCDbutton = 0;
//int switchState = 0;  // variable for keeping switch on/off
int sensePin = A0;
int sensorInput;
double temp;

void setup() {
  Serial.begin(BAUDRATE);
  BTSerial.begin(BAUDRATE);

  // initialize the pin as an output:
  // pinMode(onPin, OUTPUT);
  // pinMode(offPin, OUTPUT);
  pinMode(LCDpin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(onButtonPin, INPUT);
  pinMode(offButtonPin, INPUT);
  pinMode(LCDbuttonPin, INPUT);


}

void loop() {
  // read the state of the pushbutton value:
  onButtonState = digitalRead(onButtonPin);
  offButtonState = digitalRead(offButtonPin);
  LCDbutton = digitalRead(LCDbuttonPin);
  sensorInput = analogRead(A0);
  temp = (double)sensorInput / 1024;
  temp = temp * 5;
  temp = temp - 0.5;
  temp = temp * 100;

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //if the button is pressed AND the switch is OFF,
  if (onButtonState == HIGH) {
    // turn LED on:
    //TODO:
    //code snippet for sending signal to turn on the light switch
    BTSerial.print(1);
    //digitalWrite(onPin, HIGH);
    //switchState = 1; //set it to 1 so that when the on button is pressed again, dont turn it on again
    //delay(500);
  }
  else if(offButtonState == HIGH){
    //TODO:
    //code snippet for sending signal to turn off the light switch
    BTSerial.print(0);
    //digitalWrite(offPin, HIGH); 
    //switchState = 0; //set it to 0 so that when the off button is pressed again, it doesn't try to turn it off again
    //delay(500);
  }
  
  if(LCDbutton == HIGH){
    Serial.print("a");
    Serial.println();
    //digitalWrite(LCDpin, HIGH);
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5,8);
    display.print("Temperature: ");
    display.print("\n");
    display.print(temp);
    display.print("C");
    display.print(" / ");
    delay(100);
    temp = temp * 9/5 + 32;
    display.print(temp);
    display.print("F ");
    display.print("\n");
    display.display();
    delay(1000);
  }
  else if (LCDbutton == LOW){
    //Serial.print("b");
    //digitalWrite(LCDpin, LOW);
    delay(100);
  }
  //display.clearDisplay();

  delay(500);
}
