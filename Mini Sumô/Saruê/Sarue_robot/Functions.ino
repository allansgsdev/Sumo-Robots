// Programação SARUÊ - Sumô categoria 500g \ 10cm com PWM:
// Autor: Marcio Figueiredo Garcia
// Co-autores:
//    - Allan Gomes
//    - Maisson Alencar
// BONODORI edição - 2025.
// Arquivo: Functions.ino
// http://www.expertrobots.com.br
// Copyright Expert Robots, 2025.
// Robotics as a form of education. enjoy!
//OBSERVAÇÃO: AO PROGRAMAR O ROBÔ, CONSIDERE A FRENTE DO ROBÔ PARA FRENTE DA TELA DO COMPUTADOR
//EXEMPLO: A PLACA DO SARUE E DO CARIJÓ SÃO IGUAIS, ENTÃO SE O ROBÔ ESTÁ DE FRENTE PARA A TELA DO COMPUTADOR A CHAVE DEEP SWITCH ESTÁ NO SEU LADO ESQUERDO.

#include <QTRSensors.h>

// =============== HELPERS ===============
void setMotor(int dirPin, int pwmPin, int speed /* -255..255 */) {
  int pwm = abs(speed);
  if (pwm > 255) pwm = 255;

  // speed >= 0 => frente; speed < 0 => ré
  digitalWrite(dirPin, (speed >= 0) ? HIGH : LOW);
  analogWrite(pwmPin, pwm);
}

void drive(int leftSpeed, int rightSpeed) {
  setMotor(A_DIR, A_PWM, leftSpeed);
  setMotor(B_DIR, B_PWM, rightSpeed);
}

void setMotor2(int dirPin, int pwmPin, int speed /* -255..255 */) {
  int pwm = abs(speed);
  if (pwm > 0) pwm = 0;

  // speed >= 0 => frente; speed < 0 => ré
  digitalWrite(dirPin, (speed >= 0) ? LOW : LOW);
  analogWrite(pwmPin, pwm);
}

void drive2(int leftSpeed, int rightSpeed) {
  setMotor2(A_DIR, A_PWM, leftSpeed);
  setMotor2(B_DIR, B_PWM, rightSpeed);
}

// =============== MOVIMENTOS ===============
void frente() {
  drive(SPEED_CRUISE, SPEED_CRUISE);
}

void frente_forte() {
  drive(SPEED_BOOST, SPEED_BOOST);
}

void retorna() {
  drive(-SPEED_TURN, -SPEED_TURN);
}

void esquerda() {
  // gira para a ESQUERDA: esquerda ré, direita frente
  drive(-SPEED_TURN, SPEED_TURN);
}

void direita() {
  // gira para a DIREITA: esquerda frente, direita ré
  drive(SPEED_TURN, -SPEED_TURN);
}

void parar() {
  // --- COAST (roda livre): mais seguro para sua fiação e ponte H ---
  drive2(SPEED_BREAK, SPEED_BREAK);
  analogWrite(A_PWM, 0);
  analogWrite(B_PWM, 0);

  // As linhas de direção podem ficar no último estado; não importam com PWM=0.
  // digitalWrite(A_DIR, LOW);  // opcional
  // digitalWrite(B_DIR, LOW);  // opcional

  // --- OPÇÃO 1: FREIO ATIVO via ENABLE/STANDBY (se existir) ---
  // #ifdef HAS_ENABLE_PIN
  //   digitalWrite(ENA_PIN, LOW); // desabilita ponte -> freio curto, para “seco”
  // #endif

  // --- OPÇÃO 2: FREIO ATIVO por curto no motor (só para drivers que suportam!) ---
  // Em drivers com dois pinos de direção por motor (ex.: TB6612 com AIN1/AIN2),
  // coloca-se AIN1=AIN2=LOW (ou HIGH) para BRAKE.
  // Como seu esquema é DIR+PWM, NÃO use inversão de PWM/dir para “simular” brake:
  // isso daria comando em sentido oposto (rápido) e pode forçar a ponte.
}

// ==================== FUNÇÕES SENSORES DE LINHA DIREITO E ESQUERDO ====================
void linha()
{
  valorSensorD = analogRead(QRE1113_PinD);
  valorSensorE = analogRead(QRE1113_PinE);

  if((valorSensorD < 600)||(valorSensorE < 600))
  {
  retorna();
  delay(250);
  direita();
  delay(250);
  frente();
  }
}