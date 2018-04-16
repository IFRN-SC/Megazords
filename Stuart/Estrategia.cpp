#include "Estrategia.h"

#define PNEU_ANDA 45
#define PNEU_VOLTA -45

	void Estrategia::seguirLinha(){
    if(branco_branco_branco_branco()){            //BBBB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA); 
    }else if(preto_branco_branco_branco()){       //PBBB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
    }else if(branco_preto_branco_branco()){       //BPBB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA); 
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


