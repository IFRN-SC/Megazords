#include <robo_hardware2.h>
#include "Estrategia.h"
#include "Garra.h"

Garra garra;
Estrategia meuRobo;

void setup (){
    Serial.begin(9600);
    robo.configurar(true);
    garra.comecar ();
    robo.habilitaTCS34();
    meuRobo.calibracao();
    robo.desligarTodosLeds();
}

void loop(){
    meuRobo.executar();
}
