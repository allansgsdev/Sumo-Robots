// ## Programação SARUÊ - Sumô categoria 500g \ 10cm com PWM: ##
// Autor: Marcio Figueiredo Garcia
// Co-autores:
//    - Allan Gomes
//    - Maisson Alencar
// BONODORI edição - 2025.
// Arquivo: Config.h
// http://www.expertrobots.com.br
// Copyright Expert Robots, 2025.
// Robotics as a form of education. enjoy!
// OBSERVAÇÃO: AO PROGRAMAR O ROBÔ, CONSIDERE A FRENTE DO ROBÔ PARA FRENTE DA TELA DO COMPUTADOR
// EXEMPLO: A PLACA DO SARUE E DO CARIJÓ SÃO IGUAIS, ENTÃO SE O ROBÔ ESTÁ DE FRENTE PARA A TELA DO COMPUTADOR A CHAVE DEEP SWITCH ESTÁ NO SEU LADO ESQUERDO.

#include <QTRSensors.h>
#include <IRremote.h>

//Definição dos terminais dos motores:
// Pinos para o Motor A - Esquerdo
#define A_DIR  3    // Direção do Motor A
#define A_PWM  5    // PWM do Motor A

// Pinos para o Motor B - Direito
#define B_DIR  6    // Direção do Motor B
#define B_PWM  9    // PWM do Motor B

// --- CONFIGURÁVEIS ---
const int SPEED_BREAK = 0;   // parar -- Função extra criada separadamente
const int SPEED_CRUISE = 50;   // frente "normal"
const int SPEED_TURN   = 200;  // curvas/giros
const int SPEED_BOOST  = 255;  // frente forte / ataque

// Se seu driver tiver pino de enable/standby, você pode usá-lo para freio ativo.
// #define HAS_ENABLE_PIN
// const int ENA_PIN = /* seu pino enable/standby */;

// Definição dos sensores de linha:
#define QRE1113_PinE A2
#define QRE1113_PinD A4
int valorSensorD = 0;
int valorSensorE = 0;

// Definição dos sensores de oponente:
#define IRE 4 // sensor infrared da frente esquerdo
#define IRF 8 // sensor infrared da frente direito 
#define IRD 7  // sensor infrared lateral direito

// ---------------- Controle remoto IR ----------------
#define IR_PIN 2   // pino do receptor IR
unsigned long IR_CODE_TOGGLE = 0x8E8F; // seu botão configurado
bool enabled = false; // estado inicial (desligado)