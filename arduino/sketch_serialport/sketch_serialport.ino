bool isEnable;
char count = '\000';
byte data[2] = {0x0, 0x0};

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  isEnable = false;
  randomSeed(analogRead(0));

}

void loop() {
  delay(1000);
  if (Serial.available() > 0)//Ждём что-нибудь с порта
  {
    byte serialIn = Serial.read();//Считываем байт
    if (serialIn == 0x01) {
      isEnable = isEnable == 0 ? 1 : 0;
      digitalWrite(13, HIGH);
    }
    else if (serialIn == 0x02)
    {
      isEnable = 0;
      digitalWrite(13, LOW);
      Serial.write(count);
      Serial.flush();
    }
  }

  if (isEnable)
  {
    int randomX = random(0, 256);
    int randomY = random(0, 256);
    data[0] = byte(randomX);
    data[1] = byte(randomY);
    Serial.write(data, 2);
    Serial.flush();
  }
}
