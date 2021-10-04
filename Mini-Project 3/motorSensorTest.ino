#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);
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
//  rightMotor->setSpeed(150);
//  rightMotor->run(FORWARD);
  for (int i = 0; i < sampleSize; i++){
    sum = sum + analogRead(leftSensor);
  }
  Serial.println(sum/sampleSize);
  sum = 0;
  delay(500);
}
