#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define YOUR_SSID "Test1"
#define YOUR_PASS "12345678"
#define FIREBASE_HOST "test-v-8c12d.firebaseio.com"
#define FIREBASE_AUTH "38Hpq2QZWmyGJchbuILX6TL2WdoAeCQHwbHYemPw"
int c=0;
float d=0;
 void setup()
 {
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  WiFi.begin(YOUR_SSID,YOUR_PASS);
Serial.print("Connecting,,,");
while(WiFi.status() !=WL_CONNECTED)
{
  Serial.print(",");
  //delay(500);
  digitalWrite(D0,HIGH);
  delay(500);
  digitalWrite(D0,LOW);
  delay(500);
}
Serial.println(" ");
Serial.print("connected");
delay(1000);
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
}
 void loop(){
   float duration,distance, meter;
   digitalWrite(D1,LOW);
   delayMicroseconds(2);
   digitalWrite(D1,HIGH);
   delayMicroseconds(10);
   digitalWrite(D1,LOW);
   duration=pulseIn(D2,HIGH);
   distance=(duration/2)/29.1;
   meter=distance/100;
   Serial.print(distance);
   Serial.print("cm \n");
   Serial.print(meter);
   Serial.print("M\n");
   d=(distance/.1);
   Serial.print(d);
   Serial.println(" % ");
   if(c==0)
   {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root=jsonBuffer.createObject();
  root["meter"]=meter;
  root["distance"]=distance;
  root["dust"]=d;
  Firebase.set("Ultrasonic",root);
  }
  if(distance<=5)
  {
    digitalWrite(D3,HIGH);
    digitalWrite(D4,LOW);
  }
  if(distance>=6)
  {
    digitalWrite(D3,LOW);
    digitalWrite(D4,HIGH);
  }
   delay(500);
   
     
 }
 
   
