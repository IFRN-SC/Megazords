#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(0, 120, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(120, 0, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (90, 170, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (170, 90, DELAY);
}
