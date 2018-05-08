#include <robo_hardware2.h>
#include "Calibracao.h"


class Sensores{

  private:
  
  int mediaEsquerdo = 52;
  int mediaDireito = 44;
  int mediaMaisDireito = 47;
  int mediaMaisEsquerdo = 48;
  
  #define CINZAESQ 38
  #define CINZADIR 42
  
  float valor_sensor_frontal;
  
  Calibracao calibracao;

  // Sensores de refletancia
  
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

  // Sonares

  int detectouObstaculo(){
    
    if(robo.lerSensorSonarFrontal() <= 5 && robo.lerSensorSonarFrontal() >= 1){
    robo.acionarMotores(0, 0);
      delay(300);
    robo.acionarMotores(-30, -30);
      delay(300);
    
     while(robo.lerSensorLinhaEsq() > CINZAESQ){
       robo.acionarMotores(30, -30); 
     }
        robo.acionarMotores(0, 0);
          delay(300);
          
     while(robo.lerSensorLinhaDir() > CINZADIR){
       robo.acionarMotores(0, -30); 
     }
        robo.acionarMotores(0, 0);
          delay(300);
          
        robo.acionarMotores(50, 50);
          delay(700);
        robo.acionarMotores(0, 0);
          delay(300);
          
        robo.acionarMotores(-30, 30);
          delay(500);
        robo.acionarMotores(0, 0);  
          delay(300);
          
        robo.acionarMotores(50, 50);
          delay(1500);
        robo.acionarMotores(0, 0);
          delay(300);
          
        robo.acionarMotores(-30, 30);
          delay(500);
        robo.acionarMotores(0, 0);
          delay(300);

        while(robo.lerSensorLinhaEsq() > CINZAESQ && robo.lerSensorLinhaDir() > CINZADIR){
          robo.acionarMotores(50, 50);  
        }
        robo.acionarMotores(0, 0);  
          delay(300);

        while(!(robo.lerSensorLinhaEsq() > CINZAESQ && robo.lerSensorLinhaDir() > CINZADIR)){
          robo.acionarMotores(30, -30);    
        }       
     }
  }
 };
