#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware2.h>

class Calibracao{

  public:

  Calibracao(); 
  /*
  int mediaEsquerdo();
  int mediaDireito();
  int mediaMaisDireito();
  int mediaMaisEsquerdo();*/
  void calibrar();

  protected: 

  int mediaEsquerdo;
  int mediaDireito;
  int mediaMaisDireito;
  int mediaMaisEsquerdo;
};
#endif
