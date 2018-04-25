#include <robo_hardware2.h>
#include "Calibracao.h"

class Sensores{

  int mediaEsquerdo = 52;
  int mediaDireito = 44;
  int mediaMaisDireito = 47;
  int mediaMaisEsquerdo = 48;

  private:
  
  Calibracao calibracao;
  
  // Funcoes para definir o branco
  
  boolean ehBrancoMaisEsquerdo(){return (robo.lerSensorLinhaMaisEsq() > mediaMaisEsquerdo);}
  boolean ehBrancoEsquerdo()    {return (robo.lerSensorLinhaEsq() > mediaEsquerdo);}
  boolean ehBrancoDireito()     {return (robo.lerSensorLinhaDir() > mediaDireito);}
  boolean ehBrancoMaisDireito() {return (robo.lerSensorLinhaMaisDir() > mediaMaisDireito);}

	public:

  // Funcoes para condicoes
  
	boolean branco_branco_branco_branco(){ return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());}  //BBBB
	boolean preto_branco_branco_branco(){	 return (!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //PBBB
	boolean branco_preto_branco_branco(){	 return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //BPBB
	boolean branco_branco_preto_branco(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());} //BBPB
	boolean branco_branco_branco_preto(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && !ehBrancoMaisDireito());} //BBBP
  boolean branco_preto_preto_branco(){   return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());}//BPPB
  
};
