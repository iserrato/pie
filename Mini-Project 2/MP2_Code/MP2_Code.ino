#include <Servo.h>

Servo theta_servo;  // create servo object to control a servo
Servo phi_servo;
// twelve servo objects can be created on most boards

int p_pos = 0;    // store the servo phi position
int t_pos = 0;    // store the servo theta position
int sharpIR = A4; // pin for IR Sensor
int STEPSIZE = 2; // increment value for phi and theta position
long avg = 0;      
int i = 0;
int stat = -10;
int mod = 4; // defines the modulus for determining values
int min_ang = 24;
int max_ang = 74;
int num = 0;

void setup() {
  phi_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  theta_servo.attach(10);
  pinMode(2, INPUT_PULLUP);

  long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);
//  myTime = millis();
  attachInterrupt(digitalPinToInterrupt(2), start_rec, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stat == 5) {
    for (t_pos = 10; t_pos <= 50; t_pos += STEPSIZE) { // goes from 20 degrees to 60 degrees
    // in steps of 1 degree
    theta_servo.write(t_pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position

    if (t_pos % mod == 0) {
      for (p_pos = min_ang; p_pos <= max_ang; p_pos += STEPSIZE) {
        phi_servo.write(p_pos);
        delay(15);

        // take an average of 1000 data points
        for (i = 0; i <= 1000; i += 1) {
          num = analogRead(sharpIR);
          avg = avg + num;
        }
        avg = avg / 1001;
        Serial.print(t_pos);  Serial.print(",");
        Serial.print(p_pos);  Serial.print(",");
        Serial.println(avg);
        avg = 0;
      } 
    } 
    if (t_pos % mod != 0) {
      for (p_pos = max_ang; p_pos >= min_ang; p_pos -= STEPSIZE) {
        phi_servo.write(p_pos);
        delay(15);

        // take an average of 1000 data points
        for (i = 0; i <= 1000; i += 1) {
          num = analogRead(sharpIR);
          avg = avg + num;
        }
        avg = avg / 1001;
        Serial.print(t_pos);  Serial.print(",");
        Serial.print(p_pos);  Serial.print(",");
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
