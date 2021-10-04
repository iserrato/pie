#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);
int leftSensor = A0;
int rightSensor = A1;

int sensorSampleSize = 100;\
long sampleSumLeft = 0;
long sampleSumRight = 0;

float sensorDifference = 0;
int sensorDifferenceCutoff = 50;

int errorRatio = .25;

int motorSpeed = 100;

void setup() {
  Serial.begin(9600);
  //check coms with motor shield
  if (!AFMS.begin()) {   
    Serial.println("Failed to find motor shield");
    while (1);
  } 
}

void loop() {
  //take an average of sensor readings
  for (int i = 0; i < sensorSampleSize; i++){
    sampleSumLeft = sampleSumLeft + analogRead(leftSensor);
    sampleSumRight = sampleSumRight + analogRead(rightSensor);
  }
  
  //find difference between sensors (left - right)
  //0 if straight, positive if needs to turn left, negative if needs to turn right
  sensorDifference = (sampleSumLeft/sensorSampleSize) - (sampleSumRight/sensorSampleSize)
  //ignore slight difference in readings
  if (abs(sensorDifference) < sensorDifferenceCutoff){
    sensorDifference = 0;
  }

  //calculate speeds
  rightMotor->setSpeed(motorSpeed + (sensorDifference*errorRatio));
  leftMotor->setSpeed(motorSpeed - (sensorDifference*errorRatio));
  //set motors
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
}
