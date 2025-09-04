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

void esquerda_forte() {
  // gira para a ESQUERDA: esquerda ré, direita frente
  drive(-SPEED_BOOST, SPEED_BOOST);
}

void direita() {
  // gira para a DIREITA: esquerda frente, direita ré
  drive(SPEED_TURN, -SPEED_TURN);
}

void direita_forte() {
  // gira para a DIREITA: esquerda frente, direita ré
  drive(SPEED_BOOST, -SPEED_BOOST);
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

// ==================== CONTAGEM DE SEGUNDOS ====================
void contagem(int time)
{
  const int timeS = time/1000;
  if (!enabled)
      {
        Serial.print("Preparado para a luta. Aguardando os ");
        Serial.print(tempoInicial/1000, DEC);
        Serial.println("s para iniciar.");
        for(int i = timeS; i>=1; i--)
        {
          Serial.println(i, DEC);
          digitalWrite(LED_BUILTIN, HIGH);
          delay(i>=1 ? 1000/2 : i*1000/2);
          digitalWrite(LED_BUILTIN, LOW);
          delay(i>=1 ? 1000/2 : i*1000/2);
        }
        Serial.println("GO!");
      }
}

// ==================== INICAR COMBATE ====================
void start()
{
  contagem(tempoInicial); // Delay de 5s para iniciar (Conforme regra do campeonato);
  enabled = !enabled;
  if (!enabled) parar();
  Serial.println(enabled ? F("ROBO LIGADO") : F("ROBO DESLIGADO"));
  delay(200); // debounce
}

// ==================== ESTRATÉGIAS DE COMBATE ====================
void lateralE()
{
  Serial.println("Estratégia 'Socialista' acionada.");
  start();
  esquerda();
  delay(250);
  combate();
}

void lateralD()
{
  Serial.println("Estratégia 'Capitalista' acionada.");
  start();
  direita();
  delay(250);
  combate();
}

void costas()
{
  Serial.println("Estratégia 'Foguete não dá ré' acionada.");
  start();
  direita();
  delay(500);
  combate();
}

void estrategias(unsigned long cod)
{
  //===============IDENTIFICAÇÃO DE ESTRATÉGIAS==================
    if (cod == IR_CODE_TOGGLE || cod == IR_CODE_UP || cod == IR_CODE_SOURCE) start();

    else if (!enabled)
    {
      if(cod == IR_CODE_LEFT)
      {
        stage = 1;
        lateralE();
      }

      else if(cod == IR_CODE_RIGHT)
      {
        stage = 2;
        lateralD();
      }

      else if(cod == IR_CODE_DOWN)
      {
        stage = 3;
        costas();
      }
    }
}

void combate()
{
  //===============COMBATE==================

  // --- Se desligado, não faz nada ---
  if (!enabled) {
    parar();
    delay(500);
    return;
  }

    frente();
    linha();
    
  if(digitalRead(IRD)==LOW)
  {
    direita();
  }
  if(digitalRead(IRE)==LOW)
  {
    esquerda();
  }
  if(digitalRead(IRF)==LOW)
  {
    frente_forte();
  }
}