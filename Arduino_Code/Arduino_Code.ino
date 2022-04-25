/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */
#define WINDOW_SIZE 5

int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

// Define stepper motor connections and steps per revolution:
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200
float pitch = 0;
float roll = 0;
float yaw = 0;

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
  Serial.println("Calibrating GYRO");
  mpu.calibrateGyro();
  Serial.println("Initialize done");
  mpu.setThreshold(3);


}

void loop() {
  timer = millis();

  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch & Roll
  yaw = yaw + norm.ZAxis * timeStep;

  // Output
  Serial.print(" yaw = ");
  Serial.print(yaw);
  Serial.println();
//  Serial.print(" calcpower = ");
//  Serial.print(calcPower(yaw));
//  Serial.println();
  moveStepper(calcPower(yaw));


  //  Serial.println("test");
  //  for(int i = 0; i<400; i++){
  //  }


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
  //delay(100);
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

  //delay(1000);
  Serial.println();
  delay((timeStep * 1000) - (millis() - timer));

}


int calcPower(float sensor) {
  if (sensor > -50 && sensor < 50) {
    return sensor * 2;
  }
  else if (sensor < -50) {
    return -100;
  }
  else if (sensor > 50) {
    return 100;
  }
}
//infinity delay is 0, 450 delay is 100
void moveStepper(int power) {
  int delaytime = map(abs(power), 0, 100, 1000, 500);
//  Serial.print(" delaytime = ");
//  Serial.print(delaytime);
//  Serial.println();
  if (power < 0) {  //move left
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delaytime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delaytime);
//    Serial.println("left");
  }
  if (power > 0) {  //move right
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delaytime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delaytime);
//    Serial.println("right");

  }
  if (power == 0) {
    return;
  }

}

int calculateP_Delay(int pitch) {
  return 0;
}
int calculatePI_Delay(int pitch) {
  return 0;
}
int calculatePD_Delay(int pitch) {
  return 0;
}
int calculatePID_Delay(int pitch) {
  return 0;
}
