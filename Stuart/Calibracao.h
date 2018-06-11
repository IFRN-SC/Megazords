#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware2.h>

class Calibracao{
  
  public:
  /*
  int mediaEsquerdo();
  int mediaDireito();
  int mediaMaisDireito();
  int mediaMaisEsquerdo();*/
  void calibrar();

  protected: 

  int mediaEsquerdo = 47;
  int mediaDireito = 47;
  int mediaMaisDireito = 47;
  int mediaMaisEsquerdo = 47;
};
#endif
