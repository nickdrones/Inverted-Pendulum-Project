/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop() {
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

  // Output
  Serial.print(" Roll = ");
  Serial.print(roll);

  Serial.println();

//
//  // Set the spinning direction counterclockwise:
//  digitalWrite(dirPin, LOW);
//
//  //Spin the stepper motor 5 revolutions fast:
//  for (int i = 0; i < 3 * stepsPerRevolution; i++) {
//    // These four lines result in 1 step:
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(450);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(450);
//  }
//
//
  delay(100);
//
//  // Set the spinning direction counterclockwise:
//  digitalWrite(dirPin, HIGH);
//
//  for (int i = 0; i < 3 * stepsPerRevolution; i++) {
//    // These four lines result in 1 step:
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(450);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(450);
//  }
//
//  delay(1000);
}
