// Programação Carijó - Sumô categoria 500g \ 10cm com PWM:
// Autor: Marcio Figueiredo Garcia
// Co-autores:
//    - Allan Gomes
//    - Maisson Alencar
// BONODORI edição - 2025.
// Arquivo: Config.h
// http://www.expertrobots.com.br
// copyright Expert Robots, 2025.
// Robotics as a form of education. enjoy!

// =============== FUNÇÕES ===============

void frente()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 95);
  //Motor Direito
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 95);
}
void frenteF()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 200);
  //Motor Direito
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 200);
}
void parar()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);
  
  //Motor Direito
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 0);
}
void retorna()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 150);
  //Motor Direito
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 150);
}
void retornaF()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 255);
  //Motor Direito
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 255);
}
void direita()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 180);
  //Motor Direito
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 180);
}
void direitaF()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 255);
  //Motor Direito
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 255);
}
void esquerda()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 150);
  //Motor Direito
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 150);
}
void esquerdaF()
{
  // //Motor Esquerdo
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 255);
  //Motor Direito
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 255);
}
void linha()
{
    valorSensorD = analogRead(QRE1113_PinD);
    valorSensorE = analogRead(QRE1113_PinE);
 
  if((valorSensorD < 700)||(valorSensorE < 700))
    {
      retorna();
      delay(250);
      direita();
      delay(250);
      frente();
      }       
}