#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(9, 110, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(110, 9, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (83, 0, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (0, 83, DELAY);
}
