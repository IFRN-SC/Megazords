#include "Estrategia.h"

void Estrategia::seguirLinha() {

  if (sensores.branco_branco_branco_branco()) {          //BBBB
    movimento.seguir();

  } else if (sensores.preto_branco_branco_branco()) {     //PBBB
    movimento.girarParaEsquerda();

  } else if (sensores.branco_preto_branco_branco()) {     //BPBB
    movimento.girarParaEsquerda();

  } else if (sensores.branco_branco_preto_branco()) {     //BBPB
    movimento.girarParaDireita();

  } else if (sensores.branco_branco_branco_preto()) {     //BBBP
    movimento.girarParaDireita();

  } else if (sensores.branco_preto_preto_branco()) {     //BPPB
    movimento.seguir();

  } else if (sensores.preto_preto_branco_branco()) {     //PPBB
    while (!sensores.branco_branco_branco_branco()) {
      movimento.seguir();
    }
    while (!sensores.branco_branco_preto_branco()) {
      movimento.girarParaEsquerda();
    }

  } else if (sensores.branco_branco_preto_preto()) {     //BBPP
    while (!sensores.branco_branco_branco_branco()) {
      movimento.seguir();
    }
    while (!sensores.branco_preto_branco_branco()) {
      movimento.girarParaDireita();
    }

  } else if (sensores.branco_preto_preto_preto()) {      //BPPP
    movimento.girarParaDireita();

  } else if (sensores.preto_preto_preto_branco()) {      //PPPB
    movimento.girarParaEsquerda();

  } else if (sensores.preto_preto_preto_preto()) {       //PPPP
    movimento.seguir();
  }
}
void Estrategia::desviarObstaculo() {
  movimento.parar();
  delay(500);
  movimento.voltar();
  delay(50);
  while (sensores.ehBrancoMaisEsquerdo()) {
    movimento.girarParaDireita();
  }
  movimento.parar();
  delay(500);

  while (sensores.ehBrancoMaisDireito()) {
    movimento.girarSoDireita();
  }
  movimento.parar();
  delay(500);
  while (robo.lerSensorSonarEsq() >= 10) {
    robo.ligarLed(1);
    robo.acionarMotores(30,30);
  } robo.desligarLed(1);
  movimento.parar();
  delay(500);
  while (robo.lerSensorSonarEsq() <= 10) {
    robo.ligarLed(3);
    robo.acionarMotores(30,30);
  } robo.desligarLed(3);
  movimento.seguir();
  delay(150);
  movimento.parar();
  delay(500);

  movimento.girarParaEsquerda();
  delay(450);
  movimento.parar();
  delay(500);

  while (robo.lerSensorSonarEsq() >= 10) {
    robo.ligarLed(1);
    robo.acionarMotores(30,30);
  } robo.desligarLed(1);
  movimento.parar();
  delay(500);
  while (robo.lerSensorSonarEsq() <= 10) {
    robo.ligarLed(3);
    robo.acionarMotores(30,30);
  } robo.desligarLed(3);
  movimento.seguir();
     delay(150);

  movimento.parar();
  delay(500);

  movimento.girarParaEsquerda();
  delay(450);
  movimento.parar();
  delay(500);
  movimento.seguir();
  delay(200);

  while (sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito()) {
    robo.acionarMotores(30, 30);
  }
  /* movimento.parar();
     delay(300);*/


  movimento.parar();
  delay(500);
  robo.acionarMotores(30, 30);
  delay(350);
  movimento.parar();
  delay(500);

  while (sensores.ehBrancoEsquerdo()) {
    movimento.girarParaDireita();
  }

}
void Estrategia::identificarVerde() {
  if(sensores.ehVerdeEsquerdo()){
    robo.ligarLed(2);
    movimento.seguir();
    delay(150);
    while(sensores.ehBrancoDireito()){
      movimento.girarParaEsquerda();    
    }
  }

}
void Estrategia::subirRampa() {
  if (sensores.branco_branco_branco_branco()) {          //BBBB
    robo.acionarMotores(50, 50);
  }
  else if (sensores.preto_branco_branco_branco()) {     //PBBB
    robo.acionarMotores(40, 50);
  }
  else if (sensores.branco_preto_branco_branco()) {     //BPBB
    robo.acionarMotores(40, 50);
  }
  else if (sensores.branco_branco_preto_branco()) {     //BBPB
    robo.acionarMotores(50, 40);
  }
  else if (sensores.branco_branco_branco_preto()) {     //BBBP
    robo.acionarMotores(50, 40);
  }
  else if (sensores.preto_preto_preto_preto()) {       //PPPP
    robo.acionarMotores(50, 50);
    delay(700);
    movimento.girarParaDireita();
    delay(360);

    while (1) {
      movimento.parar();
    }
  }

}
void Estrategia::calibracao() {
}
void Estrategia::executar() {

  if ((robo.lerSensorSonarFrontal() <= 6 && robo.lerSensorSonarFrontal() >= 1)) {
    desviarObstaculo();
  }
  /*else if (sensores.procuraVerde()) {
    identificarVerde();
  }*/
  else if ((robo.lerSensorSonarEsq() <= 20 ) && (robo.lerSensorSonarDir() <= 20)) {
    subirRampa();
  }
  else {
    seguirLinha();
  }
}


