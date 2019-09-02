#include <robo_hardware2.h>
#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    robo.acionarServoGarra2(ANG_BRACO_BAIXAR, ANG_BRACO_SUBIR, DELAY);
}
void Garra::baixar (){
    robo.acionarServoGarra2(ANG_BRACO_SUBIR, ANG_BRACO_BAIXAR, DELAY);
}

void Garra::abrir (){
    robo.acionarServoGarra1 (ANG_MAO_FECHAR, ANG_MAO_ABIR, DELAY);
}
void Garra::fechar (){
    robo.acionarServoGarra1 (ANG_MAO_ABIR, ANG_MAO_FECHAR, DELAY);
}
