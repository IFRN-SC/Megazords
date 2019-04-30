#include <robo_hardware2.h>
#include "Calibracao.h"

class Sensores: public Calibracao{
    private:
        float valor_sensor_dir;
        float valor_sensor_mais_dir;
        float valor_sensor_esq;
        float valor_sensor_mais_esq;
  
	  public:
        // Sonares      
        bool identificouRampa(){
        	return (robo.lerSensorSonarEsq() < 15 ) && (robo.lerSensorSonarDir() < 15);}
        bool detectouObstaculo(){
        	return (robo.lerSensorSonarFrontal() <= 5 && robo.lerSensorSonarFrontal() >= 1);}

        // Funcoes para definir o branco
        boolean ehBrancoMaisEsquerdo(){
            return (robo.lerSensorLinhaMaisEsqSemRuido() > mediaMaisEsquerdo);}
        boolean ehBrancoEsquerdo()    {
            return (robo.lerSensorLinhaEsqSemRuido() > mediaEsquerdo);}
        boolean ehBrancoDireito()     {
            return (robo.lerSensorLinhaDirSemRuido() > mediaDireito);}
        boolean ehBrancoMaisDireito() {
            return (robo.lerSensorLinhaMaisDirSemRuido() > mediaMaisDireito);}
        

        // Funcoes para condicoes      	
      	boolean branco_branco_branco_branco(){ return (ehBrancoMaisEsquerdo()  && ehBrancoEsquerdo()  && ehBrancoDireito()  && ehBrancoMaisDireito());}  //BBBB
      	boolean preto_branco_branco_branco(){  return (!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo()  && ehBrancoDireito()  && ehBrancoMaisDireito());}  //PBBB
      	boolean branco_preto_branco_branco(){  return (ehBrancoMaisEsquerdo()  && !ehBrancoEsquerdo() && ehBrancoDireito()  && ehBrancoMaisDireito());}  //BPBB
      	boolean branco_branco_preto_branco(){  return (ehBrancoMaisEsquerdo()  && ehBrancoEsquerdo()  && !ehBrancoDireito() && ehBrancoMaisDireito());}  //BBPB
      	boolean branco_branco_branco_preto(){  return (ehBrancoMaisEsquerdo()  && ehBrancoEsquerdo()  && ehBrancoDireito()  && !ehBrancoMaisDireito());} //BBBP
        boolean branco_preto_preto_branco(){   return (ehBrancoMaisEsquerdo()  && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());}  //BPPB
        boolean preto_preto_branco_branco(){   return (!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito()  && ehBrancoMaisDireito());}  //PPBB
        boolean branco_branco_preto_preto(){   return (ehBrancoMaisEsquerdo()  && ehBrancoEsquerdo()  && !ehBrancoDireito() && !ehBrancoMaisDireito());} //BBPP
        boolean branco_preto_preto_preto(){    return (ehBrancoMaisEsquerdo()  && !ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito());} //BPPP
        boolean preto_preto_preto_branco(){    return (!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito());}  //PPPB
        boolean preto_preto_preto_preto(){     return (!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito());} //PPPP

        // PARA O SENSOR DE COR 
        boolean ehVerdeDireito (){ return robo.getHSVDireito().s > cor_direito;}          
        boolean ehVerdeEsquerdo (){ return robo.getHSVEsquerdo().s > cor_esquerdo;} 
        boolean detectouVerde (){ return (ehVerdeDireito() || ehVerdeEsquerdo());}            
        
        boolean verde_outro (){return ( ehVerdeDireito() &&!ehVerdeEsquerdo());}
        boolean outro_verde (){return (!ehVerdeDireito() && ehVerdeEsquerdo());}
        boolean verde_verde (){return ( ehVerdeDireito() && ehVerdeEsquerdo());}
        boolean outro_outro (){return (!ehVerdeDireito() &&!ehVerdeEsquerdo());}

        boolean testarVerde (){return (preto_preto_branco_branco() || preto_preto_preto_branco() ||branco_branco_preto_preto() || branco_preto_preto_preto() || preto_preto_preto_preto());}
        
};
