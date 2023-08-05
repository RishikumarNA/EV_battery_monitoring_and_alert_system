#define BLYNK_TEMPLATE_ID "TMPLXKD_pLHh"
#define BLYNK_TEMPLATE_NAME "IOT DOMAIN ANALYST"
#define BLYNK_AUTH_TOKEN "UDacAOpwicb0lLvGQvCRNM05VA0P1yd0"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"  

//DHT dht2(2,DHT11);  


char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Galaxy A22C8C3";
char pass[] = "jose1234";


//#define DHT11_PIN 2

int readD2;
int Pin_D1=4;
int Pin_D2=5;
float vout=0.0;
float vout1=0.0;
float R1=30000.0;
float R2=7500.0;
int value =0;

float a;
float b;

long int stime;
long int etime; 
 int v=100;

void setup() {
  
  pinMode(Pin_D1, OUTPUT);
  pinMode(Pin_D2, OUTPUT);
  
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  stime = millis();
}
int analogRead1(){
  digitalWrite(Pin_D1, HIGH);
  digitalWrite(Pin_D2, LOW);
  return analogRead(0);
}
int analogRead2(){
  digitalWrite(Pin_D1, LOW);
  digitalWrite(Pin_D2, HIGH);
  return analogRead(0);
}

void loop() {
  vout = (analogRead2()*5.0)/1024.0;
  vout1=vout/(R2/(R1+R2));
  delay(200);
  
  etime = millis();
  if ((etime - stime) >10000)
  {
    v--;
    stime = etime;
    
  }
  Serial.println(v);
  
  readD2=analogRead1();
  delay(200);
  
  /*a=dht2.readTemperature( );
  b=dht2.readHumidity();
  
  Serial.println("Temperature ");  
  Serial.println(a);  
  Blynk.virtualWrite(V2,a);
  if(a>=30){
    Blynk.logEvent("temp");
  }
  Serial.println("Humidity ");  
  Serial.println(b); 
  Blynk.virtualWrite(V3,b);
  if(b>=20){
    Blynk.logEvent("humi"); 
  }*/
  
  Serial.println("voltage sensor");
  Serial.println(vout1);
  Blynk.virtualWrite(V1,vout1);
  Serial.println("current sensor");
  Serial.println(readD2);
  Blynk.virtualWrite(V0,readD2);
  delay(100);

  Blynk.virtualWrite(V4,v);
  if(v<=90){
    Blynk.logEvent("soc");
  }
  Blynk.run();
  
}
