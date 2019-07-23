#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(28, 110, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(110, 28, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (70, 0, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (0, 70, DELAY);
}
