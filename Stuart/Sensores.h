#include <robo_hardware2.h>
#include "Calibracao.h"


class Sensores{

  private:
  
  int mediaEsquerdo = 56;
  int mediaDireito = 43;
  int mediaMaisDireito = 45;
  int mediaMaisEsquerdo = 49;
  
  float valor_sensor_frontal;
  
  Calibracao calibracao;

  // Sensores de refletancia
  
  // Funcoes para definir o branco
  
  boolean ehBrancoMaisEsquerdo(){return (robo.lerSensorLinhaMaisEsq() > mediaMaisEsquerdo);}
  boolean ehBrancoMaisDireito() {return (robo.lerSensorLinhaMaisDir() > mediaMaisDireito);}

	public:
 
  boolean ehBrancoEsquerdo()    {return (robo.lerSensorLinhaEsq() > mediaEsquerdo);}
  boolean ehBrancoDireito()     {return (robo.lerSensorLinhaDir() > mediaDireito);}

  // Funcoes para condicoes
  
	boolean branco_branco_branco_branco(){ return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());}  //BBBB
	boolean preto_branco_branco_branco(){	 return (!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //PBBB
	boolean branco_preto_branco_branco(){	 return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //BPBB
	boolean branco_branco_preto_branco(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());} //BBPB
	boolean branco_branco_branco_preto(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && !ehBrancoMaisDireito());} //BBBP
  boolean branco_preto_preto_branco(){   return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());}//BPPB

  // Sonares

  bool detectouObstaculo(){return (robo.lerSensorSonarFrontal() <= 5 && robo.lerSensorSonarFrontal() >= 1);}
 };
