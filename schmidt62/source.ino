
const unsigned int LED_PIN = 12;
const unsigned int BAUD_RATE = 9600;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  if ( ! Serial.available() > 0) return;
  int c = Serial.read();
  if (c == '0') {
    digitalWrite(LED_PIN, LOW);
    Serial.println("low");
  }
  else if (c == '1') {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("hi");
  }
  else {
    //digitalWrite(LED_PIN, LOW);
  }
}

