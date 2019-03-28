#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    for (int i = 180; i >= 70; i--){
        robo.acionarServoGarra2(i);
        delay(DELAY);
    }
    delay(1000);
}

void Garra::baixar (){
    for (int i = 70; i <= 180; i++){
        robo.acionarServoGarra2(i);
        delay(DELAY);
    }
    delay(1000);
}


void Garra::abrir (){
    robo.acionarServoGarra1 (180);
    robo.acionarServoGarra1 (180);
    robo.acionarServoGarra1 (180);
    delay(1000);
}

void Garra::fechar (){
    for (int i = 140; i > 0; i-- ){
        robo.acionarServoGarra1 (i);
    }
    delay(1000);
}
