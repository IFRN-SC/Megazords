void setup() {
  Serial.begin(9600);
  robo.configurar(false);
}

void loop() {

    switch(Serial.read()){
      case 'r':
      case 's':
      case 'm':
    }

}
void testarRefle(){

  valorSensorMaisEsq = robo.lerSensorLinhaMaisEsq();
  valorSensorEsq = robo.lerSensorLinhaEsq();
  valorSensorDir = robo.lerSensorLinhaDir();
  valorSensorMaisDir = robo.lerSensorLinhaMaisDir();

  Serial.print("Sensores refletancia: +esq; esq; dir; +dir ");
  Serial.print(valorSensorMaisEsq);
  Serial.print("; ");
  Serial.print(valorSensorEsq);
  Serial.print("; ");
  Serial.print(valorSensorDir);
  Serial.print("; ");
  Serial.println(valorSensorMaisDir);

  delay(1000);
}

void testar

