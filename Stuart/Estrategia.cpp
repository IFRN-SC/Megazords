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

     }else if(sensores.branco_preto_preto_branco()){       //BPPB
       movimento.seguir(); 
        
     }else if(sensores.preto_preto_branco_branco()){       //PPBB
       while(!sensores.branco_branco_branco_branco()){
         movimento.seguir();   
       }
       while(!sensores.branco_branco_preto_branco()){
         movimento.girarParaEsquerda(); 
       }
     
     }else if(sensores.branco_branco_preto_preto()){       //BBPP
       while(!sensores.branco_branco_branco_branco()){
         movimento.seguir();   
       }
       while(!sensores.branco_preto_branco_branco()){
         movimento.girarParaDireita(); 
       }
      
     }else if(sensores.branco_preto_preto_preto()){        //BPPP
       movimento.girarParaDireita();
      
     }else if(sensores.preto_preto_preto_branco()){        //PPPB
       movimento.girarParaEsquerda();
      
     }else if(sensores.preto_preto_preto_preto()){         //PPPP
     	 movimento.seguir();  	
     }
	}
	void Estrategia::desviarObstaculo(){
    robo.acionarMotores(0, 0);
      delay(1000);
    /*robo.acionarMotores(-30, -30);
      delay(300);*/
    
     while(!sensores.ehBrancoMaisEsquerdo()){
       robo.acionarMotores(30, -30); 
     }
        robo.acionarMotores(0, 0);
          delay(300);
          
     while(!sensores.ehBrancoMaisDireito()){
       robo.acionarMotores(0, -30); 
     }
        robo.acionarMotores(0, 0);
          delay(300);
          
        robo.acionarMotores(50, 50);
          delay(400);
        robo.acionarMotores(0, 0);
          delay(100);
          
        robo.acionarMotores(-30, 30);
          delay(200);
        robo.acionarMotores(0, 0);  
          delay(100);
          
        robo.acionarMotores(50, 50);
          delay(600);
        robo.acionarMotores(0, 0);
          delay(100);
          
        robo.acionarMotores(-30, 30);
          delay(200);
        robo.acionarMotores(0, 0);
          delay(100);

        while(!sensores.ehBrancoMaisEsquerdo() && !sensores.ehBrancoEsquerdo() && !sensores.ehBrancoDireito() && !sensores.ehBrancoMaisDireito()){
          robo.acionarMotores(50, 50);  
        }
        robo.acionarMotores(0, 0);  
          delay(100);

        while(!(sensores.ehBrancoMaisEsquerdo() && sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito() && sensores.ehBrancoMaisDireito())){
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

    if((robo.lerSensorSonarFrontal() <= 5 && robo.lerSensorSonarFrontal() >= 1)){
      desviarObstaculo();
    }
    else{
      seguirLinha();
    }


    
	}


