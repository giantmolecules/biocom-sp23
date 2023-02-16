

int reading = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(18);
  // turn on red led if value falls below threshold
  if (reading < 1000) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }

  Serial.print(0);
  Serial.print(",");
  Serial.print(reading);
  Serial.print(",");
  Serial.println(4095);
  delay(100);
}
