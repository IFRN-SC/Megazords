  #include "Estrategia.h"
  #include "Calibracao.h"

  void Estrategia::seguirLinha(){

	   if(sensores.branco_branco_branco_branco()){            //BBBB    
     	 movimento.seguir(); 
      
   	 }else if(sensores.preto_branco_branco_branco()){       //PBBB
       movimento.girarParaEsquerda();
        
   	 }else if(sensores.branco_preto_branco_branco()){       //BPBB
     	 robo.acionarMotores(20, 40);
     	 //movimento.girarParaEsquerda();
      
   	 }else if(sensores.branco_branco_preto_branco()){       //BBPB
       robo.acionarMotores(40, 20);
       //movimento.girarParaDireita();
      
     }else if(sensores.branco_branco_branco_preto()){       //BBBP
     	 movimento.girarParaDireita(); 

     }else if(sensores.branco_preto_preto_branco()){       //BPPB
       movimento.seguir(); 
        
     }else if(sensores.preto_preto_branco_branco()){       //PPBB
       while(!sensores.ehBrancoMaisEsquerdo()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoDireito()){
         movimento.girarParaEsquerda(); 
       } 
        while(!sensores.ehBrancoDireito()){
         movimento.girarParaDireita(); 
       }
     
     }else if(sensores.branco_branco_preto_preto()){       //BBPP
       while(!sensores.ehBrancoMaisDireito()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoEsquerdo()){
         movimento.girarParaDireita(); 
       }
       while(!sensores.ehBrancoEsquerdo()){
         movimento.girarParaEsquerda(); 
       }
      
     }else if(sensores.branco_preto_preto_preto()){        //BPPP
       while(!sensores.ehBrancoMaisDireito()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoEsquerdo()){
         movimento.girarParaDireita(); 
       }
       while(!sensores.ehBrancoEsquerdo()){
         movimento.girarParaEsquerda(); 
       }
      
     }else if(sensores.preto_preto_preto_branco()){        //PPPB
       while(!sensores.ehBrancoMaisEsquerdo()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoDireito()){
         movimento.girarParaEsquerda(); 
       } 
        while(!sensores.ehBrancoDireito()){
         movimento.girarParaDireita(); 
       }
     }else if(sensores.preto_preto_preto_preto()){         //PPPP
     	 movimento.seguir();  	
     }
	}
	void Estrategia::desviarObstaculo(){
    movimento.parar();
      delay(500);
    for(int i = 0; i < 3; i++){  
      robo.ligarTodosLeds();
      delay(350);
      robo.desligarTodosLeds();
      delay(200);
    }
    movimento.voltar();
      delay(50);
    
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
          delay(350);
        movimento.parar();  
          delay(500);
          
        movimento.seguir();
          delay(730);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(300);
        movimento.parar();
          delay(500);
          
        while(sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito()){
          robo.acionarMotores(30,30);  
        }        
          movimento.parar();  
          delay(500);
          robo.acionarMotores(30,30); 
          delay(100); 
          movimento.parar();  
          delay(500);

        while(sensores.ehBrancoDireito()){
          movimento.girarParaDireita();    
        }
        while(!sensores.ehBrancoDireito()){
          movimento.girarParaDireita();    
        }
       
	}
	void Estrategia::identificarVerde(){
	}
	void Estrategia::subirRampa(){
     if(sensores.branco_branco_branco_branco()){            //BBBB    
        robo.acionarMotores(60,60);  
     }
     else if(sensores.preto_branco_branco_branco()){       //PBBB
       robo.acionarMotores(50,60);      
     }
     else if(sensores.branco_preto_branco_branco()){       //BPBB
       robo.acionarMotores(50,60); 
     }
     else if(sensores.branco_branco_preto_branco()){       //BBPB
       robo.acionarMotores(60,50);
     }
     else if(sensores.branco_branco_branco_preto()){       //BBBP
       robo.acionarMotores(60,50); 
     }
     else if(sensores.preto_preto_preto_preto()){         //PPPP
       robo.acionarMotores(60,60);
       delay(700);
       movimento.girarParaDireita();
       delay(360);    
       
       while(1){movimento.parar();}
       robo.desligarLed(1);
       robo.ligarLed(3);
     }
    
	}
	void Estrategia::calibracao(){
    Serial.println(F("Pressione o Botão para Calibrar!"));
    Serial.println();
    for(int i = 1; i <= 10; i++){
      robo.ligarLed(3);
      if(robo.botao1Pressionado()){
        robo.desligarLed(3);
        robo.ligarLed(2);
        cali.menuCalibrar();
      }
      robo.desligarLed(2);
      Serial.println(F("Tentativa:"));
      Serial.println(i);
      delay(500); 
	  }
    robo.desligarLed(3);
    sensores.dadosCalibracao();
    Serial.println(F("Robô Calibrado!"));
	}
	void Estrategia::executar(){
    if(sensores.detectouObstaculo()){
      desviarObstaculo();
    }
    else if(sensores.identificouRampa()){ 
      robo.ligarLed(1);
      subirRampa();  
    }
    else{
      seguirLinha();
    }
   
	}

    
	


