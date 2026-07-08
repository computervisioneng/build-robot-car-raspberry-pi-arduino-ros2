#include <ArduinoJson.h>

const int ena = 3; 
const int enb = 5; 
const int enc = 6; 
const int end = 9;

const int in1 = A5; 
const int in2 = A4; 
const int in3 = 7; 
const int in4 = 8; 

const int in5 = 10;
const int in6 = 11;
const int in7 = 12;
const int in8 = 13;

JsonDocument doc;

void setup() {

  Serial.begin(115200);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(enc, OUTPUT);
  pinMode(end, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);

  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
}


void forward(){

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);

  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  
}

void right(){

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(in5, HIGH);
  digitalWrite(in6, HIGH);

  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  
}

void left(){

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);

  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  
}

void backward(){

  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);

  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);

  digitalWrite(in6, HIGH);
  digitalWrite(in5, LOW);

  digitalWrite(in8, HIGH);
  digitalWrite(in7, LOW);
  
}

void stop(){

  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);

  digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);

  digitalWrite(in6, LOW);
  digitalWrite(in5, LOW);

  digitalWrite(in8, LOW);
  digitalWrite(in7, LOW);
  
}

void clearSerialBuffer(){

  while (Serial.available()){

    Serial.read();

  }

}

int speed;
int duration;
int direction;

void loop() {

  if (Serial.available() > 0){

    String pulse_info = Serial.readStringUntil('\n');
    // Serial.println("pulse_info: " + pulse_info);

    deserializeJson(doc, pulse_info);

    speed = doc["speed"];
    duration = doc["duration"];
    direction = doc["direction"];

    clearSerialBuffer();

    // Serial.println("speed: " + String(speed) + " " + "duration: " + String(duration) + " " + "direction: " + String(direction));
  }
  else {
    speed = 0;
    duration = 50;
    direction = 4;
  }

  analogWrite(ena, speed);
  analogWrite(enb, speed);
  analogWrite(enc, speed);
  analogWrite(end, speed);

  if (direction == 0){
    forward();
  }
  else if (direction == 1){
    backward();
  }
  else if (direction == 2){
    left();
  }
  else if (direction == 3){
    right();
  }
  else if (direction == 4){
    stop();
  }
  else{
    stop();
  }

  delay(duration);

}
