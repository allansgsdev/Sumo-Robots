// Programação SARUÊ - Sumô categoria 500g \ 10cm com PWM:
// Autor: Marcio Figueiredo Garcia
// Co-autores:
//    - Allan Gomes
//    - Maisson Alencar
// BONODORI edição - 2025.
// http://www.expertrobots.com.br
// Copyright Expert Robots, 2025.
// Robotics as a form of education. enjoy!
// OBSERVAÇÃO: AO PROGRAMAR O ROBÔ, CONSIDERE A FRENTE DO ROBÔ PARA FRENTE DA TELA DO COMPUTADOR
// EXEMPLO: A PLACA DO SARUE E DO CARIJÓ SÃO IGUAIS, ENTÃO SE O ROBÔ ESTÁ DE FRENTE PARA A TELA DO COMPUTADOR A CHAVE DEEP SWITCH ESTÁ NO SEU LADO ESQUERDO.

#include <QTRSensors.h>
#include <IRremote.h>
#include "Config.h"

// ==================== SETUP ====================
void setup()
{
  // definição dos terminais de sinais de entrada dos motores:
  // Motor Esquerdo
  pinMode(A_DIR, OUTPUT);
  pinMode(A_PWM, OUTPUT);
  // Motor Direito
  pinMode(B_DIR, OUTPUT);
  pinMode(B_PWM, OUTPUT);

  // definição dos terminais de entrada dos sensores de linha:
  pinMode(QRE1113_PinD, INPUT);
  pinMode(QRE1113_PinE, INPUT);

  // definição dos terminais de entrada dos sensores de oponente:
  pinMode(IRE, INPUT);
  pinMode(IRF, INPUT);
  pinMode(IRD, INPUT);

 // Sensores de oponente devem começar combate em nível lógico alto, mas quando encontra oponente, sinal altera para LOW
  digitalWrite(IRE, HIGH);
  digitalWrite(IRF, HIGH);
  digitalWrite(IRD, HIGH);

 // Inicializa motores parados
  parar();

  // Inicializa IR
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  Serial.begin(9600);
  Serial.println(F("Robo aguardando comando IR para ligar..."));
}

void loop(){
  //===============COMBATE==================
  // --- Controle IR ---
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.print(F("Codigo IR recebido: 0x"));
    Serial.println(code, HEX);

    if (code == IR_CODE_TOGGLE) {
      enabled = !enabled;
      if (!enabled) parar();
      Serial.println(enabled ? F("ROBO LIGADO") : F("ROBO DESLIGADO"));
      delay(200); // debounce
    }
    IrReceiver.resume();
  }

  // --- Se desligado, não faz nada ---
  if (!enabled) {
    parar();
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