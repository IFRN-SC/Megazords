#include "Garra.h"

Garra::Garra(){
}

void Garra::subir (){
    for (int i = 0; i < 80; i++){
        robo.acionarServoGarra2(i);
        delay(5);
    }
}
void Garra::baixar (){
    for (int i = 80; i > 0; i--){
        robo.acionarServoGarra2(i);
        delay(5);
    }
}
void Garra::abrir (){
    for (int i = 90; i < 180; i++ ){
        robo.acionarServoGarra1 (i);
        delay (5);
    }
}
void Garra::fechar (){
    for (int i = 180; i > 90; i-- ){
        robo.acionarServoGarra1 (i);
    }
}
