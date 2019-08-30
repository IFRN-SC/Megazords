#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(7, 110, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(110, 7, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (83, 5, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (5, 83, DELAY);
}
