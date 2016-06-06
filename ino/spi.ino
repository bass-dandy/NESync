int led = 13;
int out = 8;
uint8_t data = 0b11111111;
int cycle = 7;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(out, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), latch, RISING);
  attachInterrupt(digitalPinToInterrupt(3), clk, RISING);
}

void latch() {
  cycle = 7;
  digitalWrite(out, bitRead(data, cycle));
}

void clk() {
  cycle--;
  digitalWrite(out, bitRead(data, cycle));
}

void loop() {
  if (Serial.available()) {
    data = ~Serial.read();
    /*
    if(data > 0) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }
    */
  }
}
