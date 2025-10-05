void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);  //Открываем порт
}

void loop() {
  if (Serial.available() > 0)  //Ждём что-нибудь с порта
  {
    byte serial_in = Serial.read();  //Считываем байт
    if (serial_in == 0x01) {
      digitalWrite(13, HIGH);
    } else if (serial_in == 0x02) {
      digitalWrite(13, LOW);
    }
  }
}
