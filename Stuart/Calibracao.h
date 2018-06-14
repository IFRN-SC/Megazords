#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware2.h>

class Calibracao{

  public:

  Calibracao(); 

  void calibrar();
  int dadosCalibracao();

  protected: 

  int mediaEsquerdo;
  int mediaDireito;
  int mediaMaisDireito;
  int mediaMaisEsquerdo;
};
#endif
