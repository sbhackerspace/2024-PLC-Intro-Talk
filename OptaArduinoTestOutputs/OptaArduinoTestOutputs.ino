const unsigned long duration_ms = 2000;

void setup() {
  // relay outputs
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

void lightOneAndDelay(int pinToLight) {
  // turn all off
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);

  digitalWrite(pinToLight, HIGH);

  delay(duration_ms);
}

// the loop function runs over and over again forever
void loop() {
  lightOneAndDelay(D0);
  lightOneAndDelay(D1);
  lightOneAndDelay(D2);
  lightOneAndDelay(D3);
}
