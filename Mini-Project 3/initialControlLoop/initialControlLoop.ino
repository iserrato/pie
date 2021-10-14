#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
int leftSensor = A0;
int rightSensor = A1;

String input = "";

// sensor data collection constants
int sensorSampleSize = 100;
long sensorSumLeft = 0;
long sensorSumRight = 0;

float sensorDifference = 0;
int sensorDifferenceCutoff = 50;

// motor speed constants
float errorMultiplier = .3;
float motorDefaultSpeed = 50; 
float speedScale = .5;

float leftSpeed = 0;
float rightSpeed = 0;

void setup() {
  Serial.begin(115200);
  //check coms with motor shield
  if (!AFMS.begin()) {   
    Serial.println("Failed to find motor shield");
    while (1);
  } 
}

void loop() {
  // get serial input to change parameters
  if(Serial.available()){
    input = Serial.readStringUntil('\n');
    // modify turn speed
    if (input[0] == 'p') {
      errorMultiplier = (input.substring(1)).toFloat();
    }
    // modify turn speed
    else if (input[0] == 's'){
      speedScale = (input.substring(1)).toFloat();
    }
    else {
      Serial.println("Invalid Input");
    }
    // output value for record
    Serial.print("got: ");
    Serial.println(input);
  }
    
  //take an average of sensor readings
  sensorSumLeft = 800;
  sensorSumRight = 1200;
  for (int i = 0; i < sensorSampleSize; i++){
    sensorSumLeft = sensorSumLeft + analogRead(leftSensor);
    sensorSumRight = sensorSumRight + analogRead(rightSensor);
  }

  //find difference between sensor averages (left - right)
  //0 if straight, positive if needs to turn left, negative if needs to turn right
  sensorDifference = (sensorSumLeft/sensorSampleSize) - (sensorSumRight/sensorSampleSize);
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

  Serial.println(sensorSumLeft/sensorSampleSize);
  Serial.println(sensorSumRight/sensorSampleSize);
  Serial.println(leftSpeed);
  Serial.println(rightSpeed);

  //set motors
  rightMotor->setSpeed(rightSpeed);
  leftMotor->setSpeed(leftSpeed);
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  
}
