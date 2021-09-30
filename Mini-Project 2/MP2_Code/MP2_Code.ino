#include <Servo.h>

Servo theta_servo;
Servo phi_servo;


int p_pos = 0;    // store the servo phi position
int t_pos = 0;    // store the servo theta position
int sharpIR = A4; // pin for IR Sensor
int STEPSIZE = 2; // increment value for phi and theta position
long avg = 0;     // keep track of average sensor reading
int i = 0;
int stat = -10;
int mod = 4; // defines the modulus for determining values
int min_ang = 24;  // min and max angle for phi
int max_ang = 74;
int num = 0;

void setup() {
  phi_servo.attach(9);
  theta_servo.attach(10);
  
  // set up serial communication
  long baudRate = 9600;
  Serial.begin(baudRate);
  
  // allows us to delay the readings until Python is set up
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), start_rec, RISING);
}

void loop() {
  if (stat == 5) { // checks if button was pressed
    for (t_pos = 10; t_pos <= 50; t_pos += STEPSIZE) { // goes from 10 degrees to 50 degrees
    theta_servo.write(t_pos);              
    delay(15);

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

        // send data to python
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

        // send data to python
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
