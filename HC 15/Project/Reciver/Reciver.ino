#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
int LED = 3;
int bezo = 8;
int res = 5;
int i = 0; 
int state =0;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(LED,OUTPUT);
  pinMode(bezo,OUTPUT);
  pinMode(res,INPUT);

}
void loop() {
  if (HC12.available()) {       // If HC-12 has data
   int SOS = HC12.read();
   int state =1; } 

  if (Serial.available()) {       // If HC-12 has data
   char SOS = Serial.read();
   int state =1;
       if (SOS =="1")
           state=1; 
                      } 
   
    while (int state = 1)
    {
        for(i = 0; i < 255; i = i + 2)
        {
            analogWrite(LED, i);
            analogWrite(bezo, i);
            delay(10);
        }
        for(i = 255; i > 1; i = i - 2)
        {
            analogWrite(LED, i);
            analogWrite(bezo, i);
            delay(5);
        }
        for(i = 1; i <= 10; i++)
        {
            analogWrite(LED, 255);
            analogWrite(bezo, 200);
            delay(100);
            analogWrite(LED, 0);
            analogWrite(bezo, 25);
            delay(100);
        }
        if (digitalRead(res)){
         int state =0;
         break;
                 }
    }

    
 }




  
   
