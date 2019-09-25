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

void Garra::fecharGarraMovimento (int valMaior, int valMenor){
  long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    while(t < valMaior){
        robo.acionarMotores(40, 38);     
        if(t > valMenor){
            robo.acionarServoGarra1(map(t, valMenor, valMaior, ANG_MAO_ABIR, ANG_MAO_FECHAR));  
        }
        t = (millis() -  ant);
    }
}

void Garra::descerGarra (boolean abrir){
    // sensor de fim de curso não esta precionado
    if (abrir == false){
       robo.acionarMotores (0,0);
       delay (100);
       this -> abrir ();
       this -> baixar ();
       robo.acionarMotores (0,0);
       delay (100);
    }
    
    // sensor de fim de curso esta precionado
    else {
        robo.acionarMotores (0,0);
        delay (100);
        this -> baixar ();
        this -> abrir ();
        robo.acionarMotores (0,0);
        delay (100);
    }
}
