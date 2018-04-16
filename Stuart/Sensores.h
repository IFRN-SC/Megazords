#include <robo_hardware2.h>

class Sensores{

  float valor_sensor_dir;
  float valor_sensor_mais_dir;
  float valor_sensor_esq;
  float valor_sensor_mais_esq;
  
  int mediaEsquerdo = 45;
  int mediaDireito = 45;
  int mediaMaisDireito = 45;
  int mediaMaisEsquerdo = 45;

  private:
  
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
  
};
