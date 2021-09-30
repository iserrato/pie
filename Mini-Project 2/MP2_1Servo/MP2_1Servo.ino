#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int sharpIR = A4; 

// initialize starting values
int sensorValue = 0;
int stat = -10;
long avg = 0;
int i = 0;

void setup() {
  myservo.attach(10);
  long baudRate = 9600;
  Serial.begin(baudRate);
  // allows us to delay the readings until Python is set up
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), start_rec, RISING);
}
void loop() {
  if (stat == 5) { // checks if button is pressed
    for (pos = 10; pos <= 50; pos += 1) { // goes from 10 degrees to 50 degrees
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
      avg = 0; // reset avg
    }
    for (pos = 60; pos >= 10; pos -= 1) { // goes from 60 degrees to 10 degrees
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
