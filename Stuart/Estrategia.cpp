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
    movimento.parar();
      delay(500);
    movimento.voltar();
      delay(100);
    
     while(sensores.ehBrancoMaisEsquerdo()){
       movimento.girarParaDireita(); 
     }
        movimento.parar();
          delay(500);
          
     while(sensores.ehBrancoMaisDireito()){
       movimento.girarSoDireita(); 
     }
        movimento.parar();
          delay(500);
          
        movimento.seguir();
          delay(550);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(400);
        movimento.parar();  
          delay(500);
          
        movimento.seguir();
          delay(850);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(400);
        movimento.parar();
          delay(500);

        while(!sensores.ehBrancoMaisEsquerdo() && !sensores.ehBrancoEsquerdo() && !sensores.ehBrancoDireito() && !sensores.ehBrancoMaisDireito()){
          movimento.seguir();  
        }
        movimento.parar();  
          delay(500);

        while(!(sensores.ehBrancoMaisEsquerdo() && sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito() && sensores.ehBrancoMaisDireito())){
          movimento.girarParaDireita();    
        }
          delay(500);
	}
	void Estrategia::identificarVerde(){
	}
	void Estrategia::subirRampa(){
	}
	void Estrategia::calibracao(){
	}
	void Estrategia::executar(){

    if(sensores.detectouObstaculo()){
      desviarObstaculo();
    }
    else{
      seguirLinha();
    }
	}

    
	


