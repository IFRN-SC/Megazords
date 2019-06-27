#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(18, 130, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(130, 18, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (8);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (8, 55, DELAY);
}
