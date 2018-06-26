#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware2.h>

class Calibracao{

  public:

  Calibracao(); // Construtor

  void menuCalibrar();
  void calibrarTodosBrancos();
  void calibrarPretoMaisEsquerdo();
  void calibrarPretoEsquerdo();
  void calibrarPretoMaisDireito();
  void calibrarPretoDireito();
  int dadosCalibracao();

  protected: 

  int mediaEsquerdo;
  int mediaDireito;
  int mediaMaisDireito;
  int mediaMaisEsquerdo;
};
#endif
