

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RemoteXY.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


Servo Gate;
int temp;
int humi;
int gas;

#define DHTPIN 10  
#define DHTTYPE    DHT22    
DHT_Unified dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 379 bytes
  { 255,5,0,43,0,116,1,16,31,5,2,1,39,46,22,11,1,2,26,31,
  31,79,78,0,79,70,70,0,10,48,23,24,15,15,1,4,26,31,79,112,
  101,110,0,31,67,108,111,115,101,0,2,1,39,59,22,11,1,2,26,31,
  31,79,78,0,79,70,70,0,2,1,39,72,22,11,1,2,26,31,31,79,
  78,0,79,70,70,0,129,0,22,18,16,6,1,27,71,65,84,69,0,2,
  1,39,85,22,11,1,2,26,31,31,79,78,0,79,70,70,0,129,0,1,
  49,33,6,1,28,66,69,68,32,82,79,79,77,0,129,0,1,62,33,5,
  1,28,76,73,86,73,78,71,32,82,79,79,77,0,129,0,1,75,27,6,
  1,28,75,73,84,67,72,69,78,0,129,0,1,87,26,6,1,28,71,65,
  82,65,71,69,0,131,1,4,5,20,7,1,2,31,99,111,110,116,114,111,
  108,0,131,0,28,5,31,7,2,2,31,110,111,116,105,102,105,99,97,116,
  105,111,110,0,66,129,8,38,35,9,2,6,26,70,16,38,16,13,13,2,
  26,37,0,66,129,8,55,34,9,2,4,26,66,129,8,72,34,9,2,36,
  26,69,0,5,86,10,10,2,6,69,0,25,86,10,10,2,4,69,0,46,
  86,10,10,2,1,129,0,9,19,19,6,2,28,77,111,116,105,111,110,0,
  129,0,8,32,36,6,2,6,84,101,109,112,101,114,97,116,117,114,101,0,
  129,0,8,49,25,6,2,4,72,117,109,105,100,105,116,121,0,129,0,8,
  66,11,6,2,36,71,97,115,0,67,4,45,38,12,9,2,2,26,11,67,
  4,45,55,12,9,2,2,26,11,67,4,45,72,12,9,2,2,26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 
  uint8_t switch_4; // =1 if switch ON and =0 if OFF 

    // output variables
  int8_t level_1; // =0..100 level position 
  uint8_t led_1; // led state 0 .. 1 
  int8_t level_2; // =0..100 level position 
  int8_t level_3; // =0..100 level position 
  int16_t sound_1; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  int16_t sound_2; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  int16_t sound_3; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  char text_1[11];  // string UTF8 end zero 
  char text_2[11];  // string UTF8 end zero 
  char text_3[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
   pinMode(4,OUTPUT) ; //relay
  pinMode(5,OUTPUT); //relay
  pinMode(6,OUTPUT);//relay
  pinMode(7,OUTPUT);//relay
  Gate.attach(9); //servo
  pinMode(8,INPUT); //ir
  pinMode(12,OUTPUT); //buzzer
  pinMode(13,OUTPUT); //led


  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);  
  lcd.print("TEMPERATURE: ");
  lcd.setCursor(0, 1);
  lcd.print("HUMIDITY: ");
  dht.begin();

  RemoteXY_Init (); 
  
}

void loop() 
{ 
  RemoteXY_Handler ();

   sensors_event_t event;
   dht.temperature().getEvent(&event);
   temp =  event.temperature ;   
   RemoteXY.level_1 =temp;
   String str = String(temp);
   str.toCharArray(RemoteXY.text_1, 11);
   if (temp >= 50 )  {RemoteXY.sound_1 = 2003; }
   else { RemoteXY.sound_1 = 0; }

  lcd.setCursor(13, 0);
  lcd.print(temp);
  lcd.setCursor(15, 0);
  lcd.print("C");


   dht.humidity().getEvent(&event);
   humi=event.relative_humidity ;
   RemoteXY.level_2 = humi;  
   String str1 = String(humi);
   str1.toCharArray(RemoteXY.text_2, 11);
   if (humi >= 70 )  { RemoteXY.sound_2 = 2003 ; }
   else {RemoteXY.sound_2 = 0;  }

  lcd.setCursor(10, 1);
  lcd.print(humi);
  lcd.setCursor(12, 1);
  lcd.print("%");


   gas = map(analogRead(A0),0,1023,0,100);
   RemoteXY.level_3 = gas;
   String str2 = String(gas);
   str2.toCharArray(RemoteXY.text_3, 11);
   if(gas > 30 ) { RemoteXY.sound_3 = 2012 ;}
   else { RemoteXY.sound_3 = 0 ; }

   if (temp >= 50  ||  humi >= 70  || gas > 30 ) {digitalWrite(12,HIGH);}
   else {digitalWrite(12,LOW); }
  
  
  if (RemoteXY.pushSwitch_1 == 0) {Gate.write(130); }
  if (RemoteXY.pushSwitch_1 == 1 ) {Gate.write(20);  }


  if (RemoteXY.switch_1 == 0 ) {digitalWrite(4,HIGH); }
  if (RemoteXY.switch_1 == 1 ) {digitalWrite(4,LOW); }

  if (RemoteXY.switch_2 == 0 ) {digitalWrite(5,HIGH); }
  if (RemoteXY.switch_2 == 1 ) {digitalWrite(5,LOW); }

  if (RemoteXY.switch_3 == 0) {digitalWrite(6,HIGH); }
  if (RemoteXY.switch_3 == 1 ) {digitalWrite(6,LOW); }

  if (RemoteXY.switch_4 == 0) {digitalWrite(7,HIGH); }
  if (RemoteXY.switch_4 == 1 ) {digitalWrite(7,LOW); }


  if (digitalRead(8) == 0 ) { RemoteXY.led_1 = 1 ; digitalWrite(13,HIGH);}
  else {RemoteXY.led_1 = 0 ; digitalWrite(13,LOW);}




}

