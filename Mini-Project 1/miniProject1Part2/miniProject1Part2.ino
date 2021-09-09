/*
  Project 1 Code

  Part 2 of Mini-Project 1: Build Your Own Bike Light
  Uses an infrared distance senseor to modulate the delay between our lights turning on/off.
  
*/

// define each of the pins we are using for the LEDs
int  LED1 = 12;
int LED2 = 11;
int LED3 = 10;
int mode = 0;

unsigned long myTime;

// define pin for IR sensor
int sharpIR = A0; 

// initialize starting values for our sensor and delay
int sensorValue = 0;
int dVal = 500;

void setup() 
{
  // initialize digital pins as an outputs.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  // initialize digital pin as an input that is held high
  pinMode(2, INPUT_PULLUP);

  // initialize the start time
  myTime = millis();

  Serial.begin(9600);

  // enables interrupts to allow us to increment the mode whenever switch is pressed
  attachInterrupt(digitalPinToInterrupt(2), update_mode, RISING);
}

void loop() {
  sensorValue = analogRead(sharpIR);
  Serial.println(sensorValue);
  // LED behavior based on mode
  dVal = 650 - sensorValue;
  
  switch(mode) {
    case 0: // all on
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      delay(dVal);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      delay(dVal);
      break;
    case 1: // sequential on 
      digitalWrite(LED1, HIGH);
      delay(dVal); 
      digitalWrite(LED2, HIGH);
      delay(dVal);
      digitalWrite(LED3, HIGH);
      delay(dVal);
      digitalWrite(LED1, LOW);
      delay(dVal); 
      digitalWrite(LED2, LOW);
      delay(dVal);
      digitalWrite(LED3, LOW);
      delay(dVal);
      break;
    case 2: // bounce
      digitalWrite(LED1, HIGH);
      delay(dVal); 
      digitalWrite(LED1, LOW);
      delay(dVal);
      digitalWrite(LED2, HIGH);
      delay(dVal);
      digitalWrite(LED2, LOW);
      delay(dVal);
      digitalWrite(LED3, HIGH);
      delay(dVal);
      digitalWrite(LED3, LOW);
      delay(dVal);
      digitalWrite(LED3, HIGH);
      delay(dVal); 
      digitalWrite(LED3, LOW);
      delay(dVal);
      digitalWrite(LED2, HIGH);
      delay(dVal);
      digitalWrite(LED2, LOW);
      delay(dVal);
      digitalWrite(LED1, HIGH);
      delay(dVal);
      digitalWrite(LED1, LOW);
      delay(dVal);
      break;
    case 3: // random on
      int randint = floor(random(10,13));
      digitalWrite(randint, HIGH);
      delay(dVal);
      digitalWrite(randint, LOW);
      delay(dVal);
      break;
    case 4: // all off
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;
  } 
}

void update_mode() {
  // Increment mode based on switch. diff ensures the switch does not happen if the sensor reads a change withing one second of the last change
  unsigned long diff = millis()- myTime;
  if (diff > 1000) {
    mode+=1;
    mode = mode % 5;
    Serial.println(mode);
    myTime = millis();
  }

}
