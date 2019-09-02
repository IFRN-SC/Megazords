 #include <robo_hardware2.h>
#include "Estrategia.h"
#include "Garra.h"

Garra garra1;
Estrategia meuRobo;

void setup (){
    Serial.begin(9600);
    robo.configurar(true);

    // após o roboô esta ligado, iremos levantar a garra
    robo.acionarServoGarra2(130);
    robo.acionarServoGarra1(77);
    delay(500);
    
    robo.habilitaTCS34();
    meuRobo.calibracao();
    robo.desligarTodosLeds();

}

void loop(){
    meuRobo.executar();
}
