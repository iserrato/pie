String input;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    input = Serial.readStringUntil('\n');
    Serial.print("got: ");
    Serial.println(input);
  }
}
