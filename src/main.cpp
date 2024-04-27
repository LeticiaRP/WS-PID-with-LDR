#include <Arduino.h>
#include "controller.h"

// Configuração dos pinos
#define LDR_pin 15
#define POT_pin 4 
#define LED_pin 2 

// Propriedades PWM
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

double luminosidade; 
double luminosidade_input; 

int KP = 0; 
int KI = 0; 
int KD = 0; 
int setpoint; 

Controller controle_luminosidade(KP, KI, KD);

void setup() {
    pinMode(LDR_pin, INPUT); 
    pinMode(POT_pin, INPUT); 
    pinMode(LED_pin, OUTPUT); 

    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(LED_pin, ledChannel);

    Serial.begin(9600); 
 }
  
void loop() {
    setpoint = map(analogRead(POT_pin), 0, 4095, 0, 255); 

    luminosidade = analogRead(LDR_pin);                
    luminosidade_input = map(luminosidade, 0, 4095, 0, 255);         
 
    int output = controle_luminosidade.output(luminosidade_input, setpoint);
    
    ledcWrite(ledChannel, output);

    controle_luminosidade.debug();
    Serial.println('\n');

}
