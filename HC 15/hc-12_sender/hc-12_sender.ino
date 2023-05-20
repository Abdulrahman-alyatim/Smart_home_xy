#include <SoftwareSerial.h>
#define setPin 4

SoftwareSerial HC12(3, 2);         // HC-12 TX Pin, HC-12 RX Pin
byte incomingByte;
String readBuffer = "";

void setup() {
  Serial.begin(9600);                   // Open serial port to computer
  HC12.begin(9600);                     // Open serial port to HC12
  pinMode(setPin, OUTPUT);
  digitalWrite(setPin, LOW);
  delay(250);
  HC12.write("AT+DEFAULT");
  delay(250);
  digitalWrite(setPin, HIGH);           // HC-12 normal, transparent mode
}
void loop() {
  delay(100);
  Serial.println("///////////////////////");
  while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each incoming byte from HC-12
    readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
  }
  delay(100);
  while (Serial.available()) {
    HC12.write(Serial.read());
  }
  HC12.write("Testing, testing...123");
  Serial.println("Sending Signal...");
  while (HC12.available()) {
    Serial.write(HC12.read());
    Serial.println("");
    Serial.println("***********************");
  }
  readBuffer = "";
  delay(2000);
}
