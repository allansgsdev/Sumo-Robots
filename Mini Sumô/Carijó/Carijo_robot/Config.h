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

// =============== CONFIGURAÇÕES ===============

int STBY = 12; //standby

//Motor Esquerdo
int PWMA = 5; //Speed control
int AIN1 = 7; //Direction
int AIN2 = 6; //Direction

//Motor Direito
int PWMB = 10; //Speed control
int BIN1 = 8; //Direction
int BIN2 = 9; //Direction

// Sensores de borda:

//Sensor Analógico Esquerdo:
#define QRE1113_PinD A0
//Sensor Analógico Direito:
#define QRE1113_PinE A3

int valorSensorE = 0;
int valorSensorD = 0;

// Sensores de oponente:
#define IRF 19
#define IRE 3
#define IRD 4

//Sensor IR
#define infrared 2