/* 
 *  Code is inspired from "Arduino Project Book" included in Arduino
 *  starter kit.
 */

#include <Servo.h>

Servo myServo;

const int piezo = A1;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;

int knockVal;
int switchVal;

const int quietKnock = 0;
const int loudKnock = 1000;

boolean locked = false;
int numberOfKnocks = 0;


void setup() {
  // put your setup code here, to run once:
  
  myServo.attach(9);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);

  digitalWrite(greenLed, HIGH);
  myServo.write(0);
  Serial.println("The box is unlocked!");
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(locked == false){
    switchVal = digitalRead(switchPin);
  }

  if(switchVal == HIGH){
    locked = true;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    myServo.write(90);
    Serial.println("The box is locked.");
    delay(1000);
  }

  if(locked == true){
    knockVal = analogRead(piezo);

    // Can tweak number of knocks here:
    
    if(numberOfKnocks < 2 && knockVal > 20){
      if(checkForKnocks(knockVal) == true){
        numberOfKnocks++;
      }
      
      Serial.print(2-numberOfKnocks);
      Serial.println(" more knocks to go!");
      
    }
    if(numberOfKnocks >= 2){
      
      locked = false;
      myServo.write(0);
      delay(10);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      Serial.println("The box is unlocked!");
      numberOfKnocks = 0;
      
    }
  }
}

boolean checkForKnocks(int value){
  if(value > quietKnock && value < loudKnock){

    digitalWrite(yellowLed, HIGH);
    delay(10);
    digitalWrite(yellowLed, LOW);
    Serial.print("Valid knock of value ");
    Serial.println(value);

    return true;
  }
  else{
    Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
  
}

