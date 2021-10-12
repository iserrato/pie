#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
int leftSensor = A0;
int rightSensor = A1;

String input = "";

int sensorSampleSize = 100;
long sampleSumLeft = 0;
long sampleSumRight = 0;

float sensorDifference = 0;
int sensorDifferenceCutoff = 50;

float errorMultiplier = .3;
float motorDefaultSpeed = 50; // do not change! use speed scale
float speedScale = .5;

float leftSpeed = 0;
float rightSpeed = 0;

int loopDelay = 100;

void setup() {
  Serial.begin(9600);
  //check coms with motor shield
  if (!AFMS.begin()) {   
    Serial.println("Failed to find motor shield");
    while (1);
  } 
}

void loop() {

  if(Serial.available()){
    input = Serial.readStringUntil('\n');
    if (input[0] == 'l') {
      sampleSumLeft = (input.substring(1)).toInt();
    }
    else if (input[0] == 'r') {
      sampleSumRight = (input.substring(1)).toInt();
    }
    else if (input[0] == 'p') {
      errorMultiplier = (input.substring(1)).toFloat();
    }
    else if (input[0] == 's'){
      speedScale = (input.substring(1)).toFloat();
    }
     else if (input[0] == 't'){
      loopDelay = (input.substring(1)).toInt();
    }
    else {
      Serial.println("Invalid Input");
    }
    Serial.print("got: ");
    Serial.println(input);
  }
    
  //take an average of sensor readings
  sampleSumLeft = 800;
  sampleSumRight = 1200;
  for (int i = 0; i < sensorSampleSize; i++){
    sampleSumLeft = sampleSumLeft + analogRead(leftSensor);
    sampleSumRight = sampleSumRight + analogRead(rightSensor);
  }

  //find difference between sensors (left - right)
  //0 if straight, positive if needs to turn left, negative if needs to turn right
  sensorDifference = (sampleSumLeft/sensorSampleSize) - (sampleSumRight/sensorSampleSize);
  //ignore slight difference in readings
  if (abs(sensorDifference) < sensorDifferenceCutoff){
    sensorDifference = 0;
  }

  //calculate speeds: 0-255
  rightSpeed = speedScale*(motorDefaultSpeed + (sensorDifference*errorMultiplier));
  leftSpeed = speedScale*(motorDefaultSpeed - (sensorDifference*errorMultiplier));

  // make sure speed is within the limits
  rightSpeed = ((rightSpeed < 255) ? rightSpeed : 255);
  leftSpeed = ((leftSpeed < 255) ? leftSpeed : 255);
  rightSpeed = ((rightSpeed > 0) ? rightSpeed : 0);
  leftSpeed = ((leftSpeed > 0) ? leftSpeed : 0);
  
  rightMotor->setSpeed(rightSpeed);
  leftMotor->setSpeed(leftSpeed);
//  Serial.print("rightSpeed ");
//  Serial.println(rightSpeed);
//  Serial.print("leftSpeed ");
//  Serial.println(leftSpeed);
//  Serial.print("sensor left: ");
//  Serial.println(analogRead(leftSensor));
//   Serial.print("sensor right: ");
//  Serial.println(analogRead(rightSensor));
  //set motors
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);

  
}
