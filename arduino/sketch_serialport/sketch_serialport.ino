bool isEnableAlphabet;
char count = 'a';

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  isEnableAlphabet = false;
}

void loop() {
  delay(1000);
  if (isEnableAlphabet)
  {
    Serial.write(count++);
  }

  if (Serial.available() > 0)//Ждём что-нибудь с порта
  {
    byte serialIn = Serial.read();//Считываем байт
    if (serialIn == 0x01) {
      isEnableAlphabet = isEnableAlphabet == 0 ? 1 : 0;
      digitalWrite(13, HIGH);
    }
    else if (serialIn == 0x02)
    {
      isEnableAlphabet = 0;
      count = 0;
      digitalWrite(13, LOW);
    }
  }
}
