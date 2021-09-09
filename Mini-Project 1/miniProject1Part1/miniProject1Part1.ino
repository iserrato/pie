/*
  Project 1 Code

  Part 1 of Mini-Project 1: Build Your Own Bike Light
  Turns three LEDs on/off in different patterns depending on the mode, which can be altered using the switch
*/

// define each of the pins we are using for the LEDs
int  LED1 = 12;
int LED2 = 11;
int LED3 = 10;
int mode = 0;

unsigned long myTime;

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
  // LED behavior based on mode
  switch(mode) {
    case 0: // all on
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      break;
    case 1: // all off
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;
    case 2: // sequential on 
      digitalWrite(LED1, HIGH);
      delay(100); 
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED3, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100); 
      digitalWrite(LED2, LOW);
      delay(100);
      digitalWrite(LED3, LOW);
      delay(100);
      break;
    case 3: // bounce
      digitalWrite(LED1, HIGH);
      delay(100); 
      digitalWrite(LED1, LOW);
      delay(100);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(100);
      digitalWrite(LED3, HIGH);
      delay(100);
      digitalWrite(LED3, LOW);
      delay(100);
      digitalWrite(LED3, HIGH);
      delay(100); 
      digitalWrite(LED3, LOW);
      delay(100);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(100);
      digitalWrite(LED1, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100);
      break;
    case 4: //random on
      int randint = floor(random(10,13));
      digitalWrite(randint, HIGH);
      delay(100);
      digitalWrite(randint, LOW);
      delay(100);
      break;
  } 
}

void update_mode() {
  // Increment mode based on switch
  unsigned long diff = millis()- myTime;
  if (diff > 1000) {
    mode+=1;
    mode = mode % 5;
    Serial.println(mode);
    myTime = millis();
  }

}
