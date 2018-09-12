#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia e;
Sensores s;

void setup() {
  robo.configurar(false);
  robo.habilitaTCS34();
  Serial.begin(9600);
}
void loop() {
  //e.executar();
  /*if (s.ehVerdeEsquerdo()) Serial.println("EH VERDE ESQUERDOOOO");
  Serial.println(robo.getHSVEsquerdo().v);
  delay(200);
*/
  if(s.branco_branco_branco_branco()){
    robo.acionarMotores(30, 30);
  }else if (s.branco_preto_branco_branco()) {     //BPBB
    robo.acionarMotores(-30, 30);
  }else if (s.branco_branco_preto_branco()) {     //BPBB
    robo.acionarMotores(30, -30);
  }else if (s.preto_preto_branco_branco()) {     //BPBB
    while(!s.ehBrancoMaisEsquerdo()){
      robo.acionarMotores(20, 20);
    }
    robo.acionarMotores(0,0);
    delay(300);
    while(s.ehBrancoMaisEsquerdo()){
      robo.acionarMotores(-20, -20);
    }
    if (s.ehVerdeEsquerdo()) {
      robo.acionarMotores(20, 20);
      delay(500);
      robo.acionarMotores(-35, 35);
      delay(350);
    }else{
      robo.ligarTodosLeds();
    }
    robo.desligarTodosLeds();
    //while(1){robo.acionarMotores(0,0);}
  }else if (s.branco_branco_preto_preto()) {     //BPBB
    while(!s.ehBrancoMaisDireito()){
      robo.acionarMotores(20, 20);
    }
    robo.acionarMotores(0,0);
    delay(300);
    while(s.ehBrancoMaisDireito()){
      robo.acionarMotores(-20, -20);
    }
    if (s.ehVerdeDireito()) {
      robo.acionarMotores(20, 20);
      delay(500);
      robo.acionarMotores(35, -35);
      delay(350);
    }else{
      robo.ligarTodosLeds();
    }
    robo.desligarTodosLeds();
    //while(1){robo.acionarMotores(0,0);}
  }
  
}
