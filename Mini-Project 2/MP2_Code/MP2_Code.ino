#include <Servo.h>

Servo theta_servo;  // create servo object to control a servo
Servo phi_servo;
// twelve servo objects can be created on most boards

int p_pos = 0;    // variable to store the servo position
int t_pos = 0;
int sharpIR = A0;
int STEPSIZE = 5;
int avg = 0; 
int i = 0;
int stat = -10;


void setup() {
  theta_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  phi_servo.attach(10);
  pinMode(2, INPUT_PULLUP);

  long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);
//  myTime = millis();
  attachInterrupt(digitalPinToInterrupt(2), start_rec, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stat == 5) {
    for (p_pos = 0; p_pos <= 90; p_pos += STEPSIZE) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    phi_servo.write(p_pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position

    if (p_pos % 20 == 0) {
      for (t_pos = 0; t_pos <= 90; t_pos += STEPSIZE) {
        theta_servo.write(t_pos);
        delay(15);

        for (i = 0; i <= 1000; i += 1) {
          avg += analogRead(sharpIR);
        }
        avg = avg / 1000;
        Serial.print(p_pos);  Serial.print(",");
        Serial.print(t_pos);  Serial.print(",");
        Serial.println(avg);
        avg = 0;
      } 
    } 
    if (p_pos % 20 == 10) {
      for (t_pos = 90; t_pos >= 0; t_pos -= STEPSIZE) {
        theta_servo.write(t_pos);
        delay(15);
        
        for (i = 0; i <= 1000; i += 1) {
          avg += analogRead(sharpIR);
        }
        avg = avg / 1000;
        Serial.print(p_pos);  Serial.print(",");
        Serial.print(t_pos);  Serial.print(",");
        Serial.println(avg);
        avg = 0;
      }
    }
  }
  }
}
 void start_rec() {
  // Allow the sending of data
  stat = 5;
 }
