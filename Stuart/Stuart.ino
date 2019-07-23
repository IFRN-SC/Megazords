#include <robo_hardware2.h>
#include "Estrategia.h"
#include "Garra.h"

Garra garra1;
Estrategia meuRobo;

void setup (){
    Serial.begin(9600);
    robo.configurar(true);
    robo.acionarServoGarra2(130);
    robo.acionarServoGarra1(70);
    delay(1000);
    robo.habilitaTCS34();
    meuRobo.calibracao();
    robo.desligarTodosLeds();
}

void loop(){
    meuRobo.executar();
}
