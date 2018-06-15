  #include "Estrategia.h"
  #include "Calibracao.h"

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
       movimento.seguir(); 
        
     }else if(sensores.preto_preto_branco_branco()){        //PPBB
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
        robo.acionarMotores(60,60);  
     }
     else if(sensores.preto_branco_branco_branco()){        //PBBB
       robo.acionarMotores(50,60);      
     }
     else if(sensores.branco_preto_branco_branco()){        //BPBB
       robo.acionarMotores(50,60); 
     }
     else if(sensores.branco_branco_preto_branco()){        //BBPB
       robo.acionarMotores(60,50);
     }
     else if(sensores.branco_branco_branco_preto()){        //BBBP
       robo.acionarMotores(60,50); 
     }
     else if(sensores.preto_preto_preto_preto()){           //PPPP
       robo.acionarMotores(60,60);
       delay(700);
       movimento.seguir();
       delay(300);    

       while(1){
       movimento.parar();
       robo.desligarLed(1);
       robo.ligarLed(3);
       }
     }
    
	}
	void Estrategia::calibracao(){
    Serial.println(F("Pressione o Botão para Calibrar!"));
    Serial.println();
    robo.ligarLed(3);
    
    for(int i = 1; i <= 10; i++){
      if(robo.botao1Pressionado()){
        
        cali.calibrar();
      }
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
      robo.ligarLed(2);
      desviarObstaculo();
    }
    else if(sensores.identificouRampa()){
      robo.ligarLed(1);
      subirRampa();  
    }
    else{
      robo.desligarLed(2);
      seguirLinha();
    }
   
	}

    
	


