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
  
  boolean ehBrancoMaisEsquerdo(){return (valor_sensor_mais_esq > mediaMaisEsquerdo);}
  boolean ehBrancoEsquerdo()    {return (valor_sensor_esq > mediaEsquerdo);}
  boolean ehBrancoDireito()     {return (valor_sensor_dir > mediaDireito);}
  boolean ehBrancoMaisDireito() {return (valor_sensor_mais_dir > mediaMaisDireito);}

	public:

  // Funcoes para condicoes
  
	boolean branco_branco_branco_branco(){ return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());}  //BBBB
	boolean preto_branco_branco_branco(){	 return (!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //PBBB
	boolean branco_preto_branco_branco(){	 return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //BPBB
	boolean branco_branco_preto_branco(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());} //BBPB
	boolean branco_branco_branco_preto(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && !ehBrancoMaisDireito());} //BBBP
  
};
