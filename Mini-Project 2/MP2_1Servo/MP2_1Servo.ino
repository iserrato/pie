#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int sharpIR = A0; 

// initialize starting values for our sensor and delay
int sensorValue = 0;
int stat = -10;
int avg = 0;
int i = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);
}
void loop() {
  // put your main code here, to run repeatedly:
  if (stat == 5) {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
  
      // take an average of 1000 data points
      for (i = 0; i <= 1000; i += 1) {
            avg += analogRead(sharpIR);
          }
          avg = avg / 1000;
  
      // send data to python
      Serial.print(pos);  Serial.print(",");
      Serial.println(avg);
      avg = 0;
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
  
      // take an average of 1000 data points
      for (i = 0; i <= 1000; i += 1) {
            avg += analogRead(sharpIR);
          }
          avg = avg / 1000;
  
      // send data to python
      Serial.print(pos);  Serial.print(",");
      Serial.println(avg);
      avg = 0;
    }
  }
}

 void start_rec() {
  // Allow the sending of data
  stat = 5;
 }
