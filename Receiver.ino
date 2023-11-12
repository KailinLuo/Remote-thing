// Basic serial communication with Bluetooth HM-10
// Receive a trivial string through the Bluetooth HM-10
//
//  Arduino to HM-10 connections
//  Arduino 3.3V or 5V to VCC of HM-10
//  Arduino pin 2 (TX) to voltage divider then to HM-10 RX
//  Arduino pin 3 to HM-10 TX
//  Connect GND from the Arduino to GND on the HM-10
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay the command to the HM-10


// Library to make a Software UART
#include <SoftwareSerial.h>
#define RX 3
#define TX 2

#define BAUDRATE 9600

int c = 0;
int switchState = 0;
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)
 
void setup() {
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 default speed in AT command mode
  BTSerial.begin(BAUDRATE);
  
}
 
void loop() {
  
  // Keep reading from HM-10 and send to Arduino Serial Monitor  
  if(BTSerial.available() > 0) {

    // Read from the bluetooth buffer
    c = BTSerial.read();
    if(c == 49 && switchState == 0){
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      Serial.print(c);
      delay(490);
      digitalWrite(10, LOW);

      switchState = 1;
    }
    else if(c == 48 && switchState == 1) {
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      Serial.print(c);
      delay(490);
      digitalWrite(11, LOW);

      switchState = 0;
    }
    //Write the received bluetooth data to the Serial Monitor
    //Serial.println(c == 49);
  }

  delay(1000);
}