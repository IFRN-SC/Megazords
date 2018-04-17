#include "Estrategia.h"

#define PNEU_ANDA 45
#define PNEU_VOLTA -45

  void Estrategia::seguirLinha(){

	   if(sensores.branco_branco_branco_branco()){            //BBBB    
     	 robo.acionarMotores(PNEU_ANDA, PNEU_ANDA); 
      
   	 }else if(sensores.preto_branco_branco_branco()){       //PBBB
       robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
      
   	 }else if(sensores.branco_preto_branco_branco()){       //BPBB
     	 robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA); 
      
   	 }else if(sensores.branco_branco_preto_branco()){       //BBPB
       robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA); 
      
     }else if(sensores.branco_branco_branco_preto()){       //BBBP
     	 robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA); 
      
     }else{
     	 robo.acionarMotores(0,0);  	
     }
	}
	void Estrategia::desviarObstaculo(){
	}
	void Estrategia::identificarVerde(){
	}
	void Estrategia::subirRampa(){
	}
	void Estrategia::calibracao(){
	}
	void Estrategia::executar(){

    if(/*vendo obstaculo*/false){
    }
    else{
      seguirLinha();
    }


    
	}


