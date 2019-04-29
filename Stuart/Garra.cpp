#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(15, 130, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(130, 15, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (55, 5, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (5, 55, DELAY);
}
