#include <ESP32Servo.h>
#include "BluetoothSerial.h"
BluetoothSerial bluetooth;

const double alpa = 0.7;

// Motor A pins
const int motorA_IN1 = 26;
const int motorA_IN2 = 27;
const int motorA_EN  = 14;  // PWM
// Motor B pins
const int motorB_IN1 = 25;
const int motorB_IN2 = 33;
const int motorB_EN  = 32;  // PWM

ESP32PWM pwmA;
ESP32PWM pwmB;

Servo myServo;
const int servo = 13;

const int GRIP_ANGLE    = 15;    // try 15-20 if the servo strains/doesn't reach 0
const int RELEASE_ANGLE = 92;

bool isgrip = false;

double speedVal = 200.0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("=== ESP32 BOOT ===");
  bluetooth.begin("faiznicoanton");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Motor A
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);

  // Motor B
  pinMode(motorB_IN1, OUTPUT);
  pinMode(motorB_IN2, OUTPUT);

  myServo.setPeriodHertz(50);
  myServo.attach(servo, 500, 2400);
  myServo.write(RELEASE_ANGLE);

  pwmA.attachPin(motorA_EN, 1000, 8);
  pwmB.attachPin(motorB_EN, 1000, 8);
}

void loop() {
  if (bluetooth.available()) {
    char movement = bluetooth.read();

    Serial.print("Got: ");
    Serial.println(movement);

    if (movement == 'F'){
      maju();
    }
    else if (movement == 'B'){
      mundur();
    }
    else if (movement == 'L'){
      kiri();
    }
    else if (movement == 'R'){
      kanan();
    }
    else if (movement == 'S'){
      stop();
    }
    else if (movement == 'G' && isgrip == false){
      grip();
    }
    else if (movement == 'G' && isgrip == true){
      release();
    }
    else if (movement >= '0' && movement <= '9') {
      speed(movement);
    }
  }
}

void maju(){
  // Motor A forward
  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  pwmA.write(speedVal * alpa);   

  // Motor B forward
  digitalWrite(motorB_IN1, HIGH);
  digitalWrite(motorB_IN2, LOW);
  pwmB.write(speedVal);       
}

void mundur(){
  // Motor A backward
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);
  pwmA.write(speedVal * alpa);  

  // Motor B backward
  digitalWrite(motorB_IN1, LOW);
  digitalWrite(motorB_IN2, HIGH);
  pwmB.write(speedVal);   
}

void kiri(){
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, LOW);
  pwmA.write(speedVal);  

  digitalWrite(motorB_IN1, HIGH);
  digitalWrite(motorB_IN2, LOW);
  pwmB.write(speedVal);         
}

void kanan(){
  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  pwmA.write(speedVal);          

  digitalWrite(motorB_IN1, LOW);
  digitalWrite(motorB_IN2, LOW);
  pwmB.write(speedVal);          
}

void stop(){
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, LOW);
  pwmA.write(0);                 

  digitalWrite(motorB_IN1, LOW);
  digitalWrite(motorB_IN2, LOW);
  pwmB.write(0);                
}

void grip(){
  myServo.write(GRIP_ANGLE);
  isgrip = true;
  Serial.print("Grip -> ");
  Serial.println(myServo.read());
}

void release(){
  myServo.write(RELEASE_ANGLE);
  isgrip = false;
  Serial.print("Release -> ");
  Serial.println(myServo.read());
}

void speed(char c){
  int move = c - '0'; // convert ascii to number
  speedVal = map(move, 0, 9, 0, 255);
}