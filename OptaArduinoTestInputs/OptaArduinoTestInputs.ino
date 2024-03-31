// Read Opta inputs A0-A7 and print to serial
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.print(analogRead(A0));
  Serial.print(",");
  Serial.print(analogRead(A1));
  // Serial.print(",");
  // Serial.print(analogRead(A2));
  // Serial.print(",");
  // Serial.print(analogRead(A3));
  // Serial.print(",");
  // Serial.print(analogRead(A4));
  // Serial.print(",");
  // Serial.print(analogRead(A5));
  // Serial.print(",");
  // Serial.print(analogRead(A6));
  // Serial.print(",");
  // Serial.print(analogRead(A7));
  Serial.println();

  delay(250);
}
