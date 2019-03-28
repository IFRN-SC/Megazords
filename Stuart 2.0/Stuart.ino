#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia meuRobo;

void setup (){
    Serial.begin(9600);
    robo.configurar(true);
    robo.habilitaTCS34();
    meuRobo.calibracao();
    robo.acionarServoGarra2(180);
}


void loop(){
    //Serial.println ("Henrique é mito");	
    meuRobo.executar();
}
