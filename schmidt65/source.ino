
const unsigned int LED0 = 12;
const unsigned int LED1 = 11;
const unsigned int LED2 = 10;

void setup() {

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  randomSeed(analogRead(A0));
  long r = random(1, 7);

  digitalWrite(LED0, r & B001);
  digitalWrite(LED1, r & B010);
  digitalWrite(LED2, r & B100);
}

void loop() {
}

