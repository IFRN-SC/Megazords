#include "Estrategia.h"

  void Estrategia::seguirLinha(){

	   if(sensores.branco_branco_branco_branco()){            //BBBB    
     	 movimento.seguir(); 
      
   	 }else if(sensores.preto_branco_branco_branco()){       //PBBB
       movimento.girarParaEsquerda();
      
   	 }else if(sensores.branco_preto_branco_branco()){       //BPBB
     	 movimento.girarParaEsquerda();
      
   	 }else if(sensores.branco_branco_preto_branco()){       //BBPB
       movimento.girarParaDireita();
      
     }else if(sensores.branco_branco_branco_preto()){       //BBBP
     	 movimento.girarParaDireita(); 
       
     }else if(sensores.branco_preto_preto_branco()){        //BPPB
       movimento.voltar();
       
     }else{
     	 movimento.parar();  	
     }
	}
	void Estrategia::desviarObstaculo(){
    
      robo.acionarMotores(0, 0);
      delay(300);
    robo.acionarMotores(-30, -30);
      delay(300);
    
     while(sensores.ehBrancoEsquerdo()){
       robo.acionarMotores(30, -30); 
     }
        robo.acionarMotores(0, 0);
          delay(300);
          
     while(sensores.ehBrancoDireito()){
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

        while(sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito()){
          robo.acionarMotores(50, 50);  
        }
        robo.acionarMotores(0, 0);  
          delay(300);

        while(!(sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito())){
          robo.acionarMotores(30, -30);    
        }       
    
	}
	void Estrategia::identificarVerde(){
	}
	void Estrategia::subirRampa(){
	}
	void Estrategia::calibracao(){
	}
	void Estrategia::executar(){

    if(sensores.detectouObstaculo()){
    }
    else{
      seguirLinha();
    }
	}

    
	


