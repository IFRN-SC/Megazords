#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(23, 110, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(110, 23, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (77, 0, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (0, 77, DELAY);
}
