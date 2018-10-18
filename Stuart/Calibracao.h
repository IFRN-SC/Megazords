#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware2.h>

class Calibracao{

  public:

  Calibracao(); 

  void menuCalibrar();
  int dadosCalibracao();

  protected: 
  
  // Refletancia
  
  int mediaEsquerdo;
  int mediaDireito;
  int mediaMaisDireito;
  int mediaMaisEsquerdo;

  //Cor

  int mediaVerdeEsquerdo;
  int mediaVerdeDireito;
  
};
#endif
