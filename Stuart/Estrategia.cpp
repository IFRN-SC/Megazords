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
      delay(150);
    
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
          delay(600);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(400);
        movimento.parar();  
          delay(500);
          
        movimento.seguir();
          delay(900);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(300);
        movimento.parar();
          delay(500);
          
        while(sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito()){
          robo.acionarMotores(20,20);  
        }
       /* movimento.parar();  
          delay(300);*/

        
          movimento.parar();  
          delay(2000);
          robo.acionarMotores(20,20); 
          delay(350); 
          movimento.parar();  
          delay(500);

        while(sensores.ehBrancoEsquerdo()){
          movimento.girarParaDireita();    
        }
       
	}
	void Estrategia::identificarVerde(){
	}
	void Estrategia::subirRampa(){
     if(sensores.branco_branco_branco_branco()){            //BBBB    
        robo.acionarMotores(50,50);  
     }
     else if(sensores.preto_branco_branco_branco()){       //PBBB
       robo.acionarMotores(40,50);      
     }
     else if(sensores.branco_preto_branco_branco()){       //BPBB
       robo.acionarMotores(40,50); 
     }
     else if(sensores.branco_branco_preto_branco()){       //BBPB
       robo.acionarMotores(50,40);
     }
     else if(sensores.branco_branco_branco_preto()){       //BBBP
       robo.acionarMotores(50,40); 
     }
     else if(sensores.preto_preto_preto_preto()){         //PPPP
       robo.acionarMotores(50,50);
       delay(700);
       movimento.girarParaDireita();
       delay(360);    

       while(1){movimento.parar();}
     }
    
	}
	void Estrategia::calibracao(){
	}
	void Estrategia::executar(){

    if((robo.lerSensorSonarFrontal() < 5 && robo.lerSensorSonarFrontal() >= 1)){
      desviarObstaculo();
    }
    else if((robo.lerSensorSonarEsq() < 15 ) && (robo.lerSensorSonarDir() < 15)){
      subirRampa();  
    }
    else{
      seguirLinha();
    }


    
	}


