//bool is_new_signal;
char count = 'a';

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);  //Открываем порт
  //is_new_signal = false;
}

void loop() {
  delay(200);
  if (Serial.available() > 0)  //Ждём что-нибудь с порта
  {
    byte serial_in = Serial.read();  //Считываем байт
    if (serial_in == 0x01 /*&& is_new_signal == 0*/) {
      //is_new_signal = 1;
      digitalWrite(13, HIGH);
      Serial.write(count++);
    } else if (serial_in == 0x02) {
      //is_new_signal = 0;
      digitalWrite(13, LOW);
    }
  }
}
