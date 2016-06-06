int led = 13;
int firstPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  int i;
  for(i = 0; i < 8; i++) {
    pinMode(firstPin + i, INPUT);
    digitalWrite(firstPin + i, LOW);
  }
}

void loop() {
  if (Serial.available()) {
    uint8_t received = Serial.read();
    bool valid = false;

    int i;
    for(i = 0; i < 8; i++) {
      if(received & 1 << i) {
        pinMode(firstPin + i, OUTPUT);
        digitalWrite(firstPin + i, LOW);
        valid = true;
      } else {
        pinMode(firstPin + i, INPUT);
        digitalWrite(firstPin + i, LOW);
      }
    }
    if(valid) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }
  }
}
