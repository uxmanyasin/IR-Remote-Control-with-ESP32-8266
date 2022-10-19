#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <EEPROM.h>

uint16_t RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;


int relay1 = 5;
int relay2 = 4;
int relay3 = 15;
int relay4 = 13;

int L1, L2, L3, L4, stop=0;

int touch1 = 14;
int touch2 = 12;
int touch3 = A0;
int touch4 = 16;


String Signal = ""; 

void dump(decode_results *results) {
  if (results->decode_type == NEC) {
    Signal =  uint64ToString(results->value, 16);
   
  if(Signal == "1FE807F")   //btn OFF
    {
      L1 =0 ;
      L2 =0 ;
      L3 =0 ;
      L4 =0 ;
     
      EEPROM.write(1, L1);
      Serial.println("****** Button OFF Pressed*****");
      delay(100);
    }
    else if(Signal == "1FE58A7") //btn 1
    {
      L1 = L1+1;
      if(L1>1){L1=0;} 
      EEPROM.write(1, L1);
      Serial.println("****** Button1 Pressed*****");
      delay(100);
    }
    else if(Signal == "1FE40BF") //btn 2
    {
      L2 = L2+1;
      if(L2>1){L2=0;} 
      EEPROM.write(1, L2);
      Serial.println("****** Button2 Pressed*****");
      delay(100);
    }
    else if(Signal == "1FEC03F") //btn 3
    {
       L3 = L3+1;
      if(L3>1){L3=0;} 
      EEPROM.write(1, L3);
      Serial.println("****** Button3 Pressed*****");
      delay(100);
    }
    else if(Signal == "1FE609F") //btn 4
    {
      L4 = L4+1;
      if(L4>1){L4=0;} 
      EEPROM.write(1, L4);
      Serial.println("****** Button4 Pressed*****");
      delay(100);
    }
    
  } 

}

void setup() {

L1 = EEPROM.read(1);
L2 = EEPROM.read(2);
L3 = EEPROM.read(3);
L4 = EEPROM.read(4); 

irrecv.enableIRIn();  

pinMode(touch1, INPUT);
pinMode(touch2, INPUT);
pinMode(touch3, INPUT);
pinMode(touch4, INPUT);

pinMode(relay1, OUTPUT); 
pinMode(relay2, OUTPUT); 
pinMode(relay3, OUTPUT); 
pinMode(relay4, OUTPUT); 


Serial.begin(115200);
}

void loop() {

if (irrecv.decode(&results)) {
    dump(&results);
    
    irrecv.resume();  
  }

int x = analogRead(touch3);

if (digitalRead (touch1) == HIGH){
digitalWrite(relay1, HIGH);
Serial.println("****** Touch 1 ON*****");
delay(100);
}

else if(digitalRead (touch1) == LOW)
{
digitalWrite(relay1, LOW);
Serial.println("****** Touch 1 OFF*****");
delay(100);
}


if (digitalRead (touch2) == HIGH){
digitalWrite(relay2, HIGH);
Serial.println("****** Touch 2 ON*****");
delay(100);
}
else if (digitalRead (touch2) == LOW){
digitalWrite(relay2, LOW);
Serial.println("****** Touch 2 OFF*****");
delay(100);
}
if (x > 600){
digitalWrite(relay3, HIGH);
Serial.println("****** Touch 3 ON*****");
delay(100);
}

else if (x <400){
digitalWrite(relay3, LOW);
Serial.println("****** Touch 3 OFF*****");
delay(100);
}
if (digitalRead (touch4) == HIGH){
digitalWrite(relay4, HIGH);
Serial.println("****** Touch 4 ON*****");
delay(100);
}

if (digitalRead (touch4) == LOW){
digitalWrite(relay4, LOW);
Serial.println("****** Touch 4 OFF*****");
delay(100);
}


}
