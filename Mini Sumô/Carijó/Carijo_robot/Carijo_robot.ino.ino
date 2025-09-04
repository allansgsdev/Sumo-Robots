// Programação Carijó - Sumô categoria 500g \ 10cm com PWM:
// Autor: Marcio Figueiredo Garcia
// Co-autores:
//    - Allan Gomes
//    - Maisson Alencar
// BONODORI edição - 2025.
// http://www.expertrobots.com.br
// copyright Expert Robots, 2025.
// Robotics as a form of education. enjoy!

//#include <QTRSensors.h>
//#include <SparkFun_TB6612.h>
#include "Config.h"

void setup(){

Serial.begin(9600);
pinMode(STBY, OUTPUT);
//Motor Esquerdo
pinMode(PWMA, OUTPUT);
pinMode(AIN1, OUTPUT);
pinMode(AIN2, OUTPUT);
//Motor Direito
pinMode(PWMB, OUTPUT);
pinMode(BIN1, OUTPUT);
pinMode(BIN2, OUTPUT);

pinMode(IRF, INPUT);
pinMode(IRE, INPUT);
pinMode(IRD, INPUT);

pinMode(QRE1113_PinE, INPUT);
pinMode(QRE1113_PinD, INPUT);
pinMode(valorSensorE, INPUT);
pinMode(valorSensorD, INPUT);

  digitalWrite(IRF, HIGH);
  digitalWrite(IRD, HIGH);
  digitalWrite(IRE, HIGH);
  
  digitalWrite(PWMA, HIGH);
  digitalWrite(PWMB, HIGH);
  digitalWrite(STBY, HIGH);

  //inicia funcionamento
parar();
delay(5000);
frente();
}

void loop(){
  linha();
  frente();

if((digitalRead(IRD)==LOW))
{
  direitaF();
}
if(digitalRead(IRF)==LOW)
{
  frenteF();
}
while(digitalRead(IRF)==LOW)
{
  frenteF();
}
if(digitalRead(IRE)==LOW)
{
  esquerdaF();
}
}