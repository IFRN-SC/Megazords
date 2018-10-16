#include <robo_hardware2.h>
#include "Calibracao.h"

class Sensores: public Calibracao{
  
  private:
  
  float valor_sensor_dir;
  float valor_sensor_mais_dir;
  float valor_sensor_esq;
  float valor_sensor_mais_esq;
  
	public:

  // Funcoes para definir o branco e verde
  
  boolean ehBrancoMaisEsquerdo(){
    return (robo.lerSensorLinhaMaisEsq() > mediaMaisEsquerdo);}
  boolean ehBrancoEsquerdo()    {
    return (robo.lerSensorLinhaEsq() > mediaEsquerdo);}
  boolean ehBrancoDireito()     {
    return (robo.lerSensorLinhaDir() > mediaDireito);}
  boolean ehBrancoMaisDireito() {
    return (robo.lerSensorLinhaMaisDir() > mediaMaisDireito);}
  boolean ehVerdeEsquerdo()     {
    return (robo.getHSVEsquerdo().v < 225);}
  boolean ehVerdeDireito()      {
    return (robo.getHSVDireito().v < 225);}  

  // Funcoes para condicoes
  
	boolean branco_branco_branco_branco(){ return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());}   //BBBB
	boolean preto_branco_branco_branco(){	 return (!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());}  //PBBB
	boolean branco_preto_branco_branco(){	 return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());}  //BPBB
	boolean branco_branco_preto_branco(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());}  //BBPB
	boolean branco_branco_branco_preto(){	 return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && !ehBrancoMaisDireito());}  //BBBP
  boolean branco_preto_preto_branco(){   return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());} //BPPB
  boolean preto_preto_branco_branco(){   return (!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());} //PPBB
  boolean branco_branco_preto_preto(){   return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito());} //BBPP
  boolean branco_preto_preto_preto(){   return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito());} //BPPP
  boolean preto_preto_preto_branco(){   return (!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());} //PPPB
  boolean preto_preto_preto_preto(){   return (!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito());} //PPPP
  boolean verde_esquedo(){ return (ehVerdeEsquerdo());}
  boolean verde_direito(){ return (ehVerdeDireito());}
  boolean verde_beco(){ return (ehVerdeEsquerdo() && ehVerdeDireito());}
  
  // Sonares

  bool detectouObstaculo(){return (robo.lerSensorSonarFrontal() <= 5 && robo.lerSensorSonarFrontal() >= 1);}
  bool identificouRampa(){return (robo.lerSensorSonarEsq() < 15 ) && (robo.lerSensorSonarDir() < 15);}
  bool testarVerde(){return (preto_preto_branco_branco()
  || branco_branco_preto_preto() || preto_preto_preto_preto() 
  || branco_preto_preto_preto() || preto_preto_preto_branco());}
};
