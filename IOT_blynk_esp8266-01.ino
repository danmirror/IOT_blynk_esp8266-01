
//-----------------------IOT HEADER INITIAL------------------
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

char auth[] = "U593hrI-ELBdSJBygFvAwdmLzQEzEAb-";
char ssid[] = "Redmi Note 9 Pro";
char pass[] = "enterprise";

SoftwareSerial EspSerial(2, 3); // RX, TX
WidgetLCD lcd_widget(V0);

ESP8266 wifi(&EspSerial);
// ----------------------END IOT HEADER---------------


//-------------------ARDUINO HEADER INITIAL------------
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define echoPin 6 //Echo Pin
#define trigPin 5 //Trigger Pin

#define relay 7

long duration, distance; //waktu untuk kalkulasi jarak
float jarak;
float ultrasonic(); //deklarasi function
//--------------------END ARDUINO HEADER------------

void setup() {
//  -----------------IOT SETUP-----------/
  Serial.begin(115200);
  EspSerial.begin(115200);
  
// try connect
  Serial.println("AT");
  EspSerial.println("AT");
  delay(1000);
  
  if(EspSerial.find("OK"))
    Serial.println("ESP8266 connected");
  
  
  Blynk.begin(auth, wifi, ssid, pass);
  lcd_widget.clear();
  lcd_widget.print(0, 0, "TOPAN");

//  ---------------END IOT SETUP------------/

 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(relay, OUTPUT);
    
  lcd.begin();
  lcd.print("Hello, world!");
}
 
void loop(){
  
  Blynk.run();

//  -------------ARDUINO RUNNING-------------
  jarak = ultrasonic();
  Serial.println(jarak);
  if (jarak <= 10){
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
  
}

float ultrasonic(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
   
  //perhitungan untuk dijadikan jarak
  distance = duration/58.2;
   
  return distance;
}
