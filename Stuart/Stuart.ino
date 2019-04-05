#include <robo_hardware2.h>
#include "Estrategia.h"
#include "Garra.h"

Garra garra1;
Estrategia meuRobo;

void setup (){
    Serial.begin(9600);
    robo.configurar(true);
    garra1.subir ();
    garra1.abrir ();
    robo.habilitaTCS34();
    meuRobo.calibracao();
}


void loop(){
    meuRobo.executar();
}
