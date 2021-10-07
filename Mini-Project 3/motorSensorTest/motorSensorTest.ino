#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
int leftSensor = A0;
long sum = 0;
int sampleSize = 1000;

void setup() {
  Serial.begin(9600);
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Failed to find motor shield");
    while (1);
  }           
}

void loop() {
  rightMotor->setSpeed(0);
  rightMotor->run(FORWARD);
  leftMotor->setSpeed(0);
  leftMotor->run(FORWARD);
  for (int i = 0; i < sampleSize; i++){
    sum = sum + analogRead(leftSensor);
  }
  Serial.println(sum/sampleSize);
  sum = 0;
  delay(500);
}
