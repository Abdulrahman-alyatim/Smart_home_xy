#include <SoftwareSerial.h>
int setPin = 4;

SoftwareSerial HC12(3, 2);         // HC-12 TX Pin, HC-12 RX Pin
byte incomingByte;
String readBuffer = "";

void setup() {

  Serial.begin(9600);                   // Open serial port to computer
  HC12.begin(9600);                     // Open serial port to HC12
  pinMode(setPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(setPin, LOW);
  delay(250);
  HC12.write("AT+DEFAULT");
  delay(250);
  digitalWrite(setPin, HIGH);          // HC-12 normal, transparent mode
}
void loop() {
  delay(100);
  while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each icoming byte from HC-12
    readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
  }
  delay(100);
  while (Serial.available()) {
    HC12.write(Serial.read());
  }
  if (readBuffer == "Testing, testing...123") {
    digitalWrite(13, HIGH);
    HC12.print(readBuffer);
    delay(1000);
  }
  readBuffer = "";
  delay(1000);
  digitalWrite(13, LOW);
}
