#include <Wire.h>    // Required for I2C communication
#include <RTClib.h>  // RTC library for DS3231int LDr1;

const int led1 =2 ;
const int led2 = 3;
const int led3 = 4;

const int pir1=5;
const int pir2=6;
const int pir3=7;
const int pir4=8;



const int ldr = A0;
const int Trigger_pin = 9;

const int Echo_pin1 = 10;
const int Echo_pin2 = 11;
const int Echo_pin3 = 12;



const int MEASURING_INTERVAL = 100;  // Time interval for taking distance measurements (in milliseconds)

float previousDistance1 = 0;  // Distance measured in the previous iteration
float previousDistance2 = 0;
float previousDistance3 = 0;
float previousDistance4 = 0;
float previousMillis = 0;  // Time of the previous measurement
RTC_DS3231 rtc;            // Create an instance of the RTC_DS3231 class
int ultrasonic_threshhold = 20;
char t[32];



void setup() {
  Wire.begin();
  rtc.begin();
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);
  pinMode(Trigger_pin, OUTPUT);
  pinMode(Echo_pin1, INPUT);
  pinMode(Echo_pin2, INPUT);
  pinMode(Echo_pin3, INPUT);
  rtc.adjust(DateTime(2023,8,25,22, 55, 0));
}


float getDistance1() {
  digitalWrite(Trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_pin, LOW);
  return pulseIn(Echo_pin1, HIGH) / 58.0;
}

float getDistance2() {
  digitalWrite(Trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_pin, LOW);
  return pulseIn(Echo_pin2, HIGH) / 58.0;
}

float getDistance3() {
  digitalWrite(Trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_pin, LOW);
  return pulseIn(Echo_pin3, HIGH) / 58.0;
}


void loop() {
  int Ldr = analogRead(ldr);
  int pirValue1 = digitalRead(pir1);
  int pirValue2= digitalRead(pir2);
  int pirValue3= digitalRead(pir3);
  int pirValue4= digitalRead(pir4);
  DateTime now = rtc.now();
  int currentHour = now.hour();
  float currentMillis = millis();

  float currentDistance1 = getDistance1();
  float distanceChange1 = currentDistance1 - previousDistance1;
  Serial.println(currentDistance1);

  float currentDistance2 = getDistance2();
  float distanceChange2 = currentDistance2 - previousDistance2;
  Serial.println(currentDistance2);

  float currentDistance3 = getDistance3();
  float distanceChange3 = currentDistance3 - previousDistance3;
  Serial.println(currentDistance3);

  if (Ldr>=800) {
    if (currentHour < 22) {
      Serial.println("Street light on before 10pm");
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
     
     else if(currentHour >= 22 && ((currentDistance1 < ultrasonic_threshhold && currentDistance1 != 0.00)|| pirValue1==HIGH )) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2,HIGH);
      Serial.println("Streetlight is on for first condition");
      Serial.println("Motion detected1....");
      }

      else if (currentHour >= 22 && ((currentDistance2 < ultrasonic_threshhold && currentDistance2 != 0.00) || pirValue2==HIGH )){  // Keep the LED ON after 10.00 pm only when there is a motion
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3,HIGH);
        Serial.println("Street light on Second Condition..");
        Serial.println("Motion detected2....");
      }
      else if (currentHour >= 22 && ((currentDistance3 < ultrasonic_threshhold && currentDistance3 != 0.00)|| pirValue3==HIGH)) {  // Keep the LED ON after 10.00 pm only when there is a motion
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led1,LOW);

        Serial.println("Street light on Third condition ");
        Serial.println("Motion detected3....");
      } 
      else {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        Serial.println("Streetlight is off3..");
      }
     
    }
   else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    Serial.println("Streetlight is off (Default).");
  }


  previousDistance1 = currentDistance1;
  previousDistance2 = currentDistance2;
  previousDistance3 = currentDistance3;
  previousMillis = currentMillis;


  sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());
  Serial.print(F("Date/Time: "));
  Serial.println(t);
  Serial.println(Ldr);
  delay(1000);
  
}