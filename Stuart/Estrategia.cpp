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

     }else if(sensores.branco_preto_preto_branco()){       //BPPB
       movimento.seguir(); 
        
     }/*else if(sensores.preto_preto_branco_branco()){       //PPBB
       while(!sensores.ehBrancoMaisEsquerdo()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoMaisEsquerdo()){
         movimento.girarParaEsquerda(); 
       } 
        while(!sensores.ehBrancoMaisEsquerdo()){
         movimento.girarParaEsquerda(); 
       }
     
     }else if(sensores.branco_branco_preto_preto()){       //BBPP
       while(!sensores.ehBrancoMaisDireito()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoMaisDireito()){
         movimento.girarParaDireita(); 
       }
       while(!sensores.ehBrancoMaisDireito()){
         movimento.girarParaDireita(); 
       }
      
     }else if(sensores.branco_preto_preto_preto()){        //BPPP
       while(!sensores.ehBrancoMaisDireito()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoMaisDireito()){
         movimento.girarParaDireita(); 
       }
       while(!sensores.ehBrancoMaisDireito()){
         movimento.girarParaDireita(); 
       }
      
     }else if(sensores.preto_preto_preto_branco()){        //PPPB
       while(!sensores.ehBrancoMaisEsquerdo()){
         movimento.seguir();   
       }
       while(sensores.ehBrancoMaisEsquerdo()){
         movimento.girarParaEsquerda(); 
       }
       while(!sensores.ehBrancoMaisEsquerdo()){
       movimento.girarParaEsquerda();
       }
     }*/else if(sensores.preto_preto_preto_preto()){         //PPPP
     	 movimento.seguir();  	
     }
	}
	void Estrategia::desviarObstaculo(){
    movimento.parar();
      delay(500);
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
          delay(620);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(350);
        movimento.parar();  
          delay(500);
          
        movimento.seguir();
          delay(700);
        movimento.parar();
          delay(500);
          
        movimento.girarParaEsquerda();
          delay(350);
        movimento.parar();
          delay(500);
          
        while(sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito()){
          robo.acionarMotores(30,30);  
        }
       /* movimento.parar();  
          delay(300);*/

        
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
    robo.desligarLed(3);
    movimento.parar();
    delay(200);
    movimento.seguir();
    delay(50);
    movimento.parar();
    delay(100);
    while(sensores.ehBrancoMaisDireito() && sensores.ehBrancoMaisEsquerdo()){
      robo.acionarMotores(-20, -20);
    }
    movimento.parar();
    delay(100);
    /*if (sensores.verde_beco()) {
      girarVerdeBeco();   
    }else */if (sensores.verde_esquedo()){
      girarVerdeEsquerdo();
    }else if (sensores.verde_direito()){
      girarVerdeDireito();
    }
        if(!sensores.ehBrancoMaisEsquerdo()){
          while(!sensores.ehBrancoMaisEsquerdo()){
            movimento.seguir();   
          }
          while(sensores.ehBrancoDireito()){
            robo.acionarMotores(-25, 25); 
          }   
        }
        else if(!sensores.ehBrancoMaisDireito()){
          while(!sensores.ehBrancoMaisDireito()){
            movimento.seguir();   
          }
          while(sensores.ehBrancoEsquerdo()){
            robo.acionarMotores(25, -25); 
          }
        }
    }
  void Estrategia::girarVerdeEsquerdo(){
    for(int i = 0; i < 3; i++){
           robo.ligarLed(1);
           delay(200);
           robo.desligarLed(1);
           delay(200); 
         }
      robo.acionarMotores(20, 20);
      delay(300);
      while(sensores.ehBrancoMaisEsquerdo()){
         movimento.girarParaEsquerda(); 
      } 
      while(!sensores.ehBrancoMaisEsquerdo()){
         movimento.girarParaEsquerda(); 
      }       
  }
  void Estrategia::girarVerdeDireito(){
    for(int i = 0; i < 3; i++){
           robo.ligarLed(2);
           delay(200);
           robo.desligarLed(2);
           delay(200); 
         }
      robo.acionarMotores(20, 20);
      delay(300); 
      while(sensores.ehBrancoMaisDireito()){
         movimento.girarParaDireita(); 
      }
      while(!sensores.ehBrancoMaisDireito()){
         movimento.girarParaDireita(); 
      }  
  }
  void Estrategia::girarVerdeBeco(){
    for(int i = 0; i < 3; i++){
           robo.ligarLed(3);
           delay(200);
           robo.desligarLed(3);
           delay(200); 
         }
    movimento.girarParaDireita();
    delay(400);
    while(sensores.ehBrancoMaisDireito()){
       movimento.girarParaDireita(); 
    }
    while(!sensores.ehBrancoMaisDireito()){
       movimento.girarParaDireita(); 
    }  
  }
	void Estrategia::subirRampa(){
    while(1){
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
       robo.acionarMotores(70,70);  
       //break;
       }
    }
    /*robo.acionarMotores(50, 50);
    delay(1000);
    robo.acionarMotores(0,0);
    robo.ligarLed(2);
    
    while(1);*/
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
    if(sensores.testarVerde()){
      robo.ligarLed(3);
      identificarVerde();
    }
    else if(sensores.detectouObstaculo()){
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

    
	


