
const unsigned int LED0 = 12;
const unsigned int LED1 = 11;
const unsigned int LED2 = 10;

void show(const long i) {

  digitalWrite(LED0, i & B001);
  digitalWrite(LED1, i & B010);
  digitalWrite(LED2, i & B100);
}

void setup() {

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  show(1 + 2 + 4); delay(100);
  show(0); delay(500);
  show(1); delay(500);
  show(2); delay(500);
  show(4); delay(500);
  show(1 + 2 + 4); delay(300);

  randomSeed(analogRead(A0));

  show(random(1, 7));
}

void loop() {
}

