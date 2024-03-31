static int myCounter = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USER_BTN, INPUT_PULLUP);

  myCounter = 0;
  Serial.begin(9600);
}

void loop() {
  int btnStatus = !digitalRead(USER_BTN);
  digitalWrite(LED_BUILTIN, btnStatus);

  myCounter += 1;
  Serial.println(myCounter);
  delay(50);
}
