#include <ESP32Servo.h>  
#include "BluetoothSerial.h"
BluetoothSerial bluetooth;

// Motor A pins 
const int motorA_IN1 = 26;
const int motorA_IN2 = 27;
const int motorA_EN  = 14;  // PWM

// Motor B pins
const int motorB_IN1 = 25;
const int motorB_IN2 = 33;
const int motorB_EN  = 32;  // PWM

Servo myServo;
const int servo = 13;

bool isgrip = false;

void setup() {
  bluetooth.begin("faiznicoanton");

  // Motor A
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorA_EN, OUTPUT);

  // Motor B
  pinMode(motorB_IN1, OUTPUT);
  pinMode(motorB_IN2, OUTPUT);
  pinMode(motorB_EN, OUTPUT);

  // Servo
  myServo.attach(servo); 
  myServo.write(0);

  Serial.begin(115200);
}

void loop() {
  if (bluetooth.available()) {
    char movement = bluetooth.read();

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
      detach()
    }
    else if (movement == 'G' && isgrip == false){
      grip();
      isgrip = true;
    }
    else if (movement == 'G' && isgrip == true){
      release();
      isgrip = false;
    }
    else {
      speed();
    }
  }
}

void maju(){


}
void mundur(){


}
void kiri(){


}
void kanan(){


}
void detach(){


}
void grip(){


}
void release(){


}
void speed(){
  int movement = atoi(movement);
  int speed = map(movement, 0, 9, 0, 255);
}