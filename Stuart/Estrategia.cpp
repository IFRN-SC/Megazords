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
       
     }else if(branco_preto_preto_branco()){                 //BPPB
       movimento.voltar();
       
     }else{
     	 movimento.parar();  	
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


