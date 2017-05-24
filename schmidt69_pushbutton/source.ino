
const unsigned int LED0 = 13;
const unsigned int BUTTON0 = 12;

void setup() {

  pinMode(LED0, OUTPUT);
  pinMode(BUTTON0, INPUT);
}

void loop() {

  digitalWrite(LED0, digitalRead(BUTTON0));
}

