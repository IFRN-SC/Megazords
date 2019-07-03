#include "Estrategia.h"
#include "Calibracao.h"

Estrategia::Estrategia (){  
}

void Estrategia::seguirLinha() {
	  if(sensores.branco_branco_branco_branco()){            //BBBB  
        robo.desligarTodosLeds();
        robo.ligarLed(2);  
     	  movimento.seguir(); 
         
   	}else if(sensores.preto_branco_branco_branco() || sensores.branco_preto_branco_branco()){ //PBBB//BPBB
       // robo.acionarMotores(-33,30);
        movimento.girarParaEsquerda();    
        
   	}else if(sensores.branco_branco_branco_preto() || sensores.branco_branco_preto_branco()){ //BBBP//BBPB
     	 // robo.acionarMotores(33,-30);
        movimento.girarParaDireita(); 
         
    }else if(sensores.preto_preto_branco_branco() || sensores.preto_preto_preto_branco()){ //PPBB//PPPB
        
        robo.desligarTodosLeds();
        robo.ligarLed(1);
      
        while(!sensores.ehBrancoMaisEsquerdo()){
            movimento.seguir(); 
        }
        while(sensores.ehBrancoDireito()){
            movimento.girarParaEsquerda(); 
        } 
        while(!sensores.ehBrancoDireito()){
            movimento.girarParaDireita(); 
        }
        
    }else if(sensores.branco_branco_preto_preto() || sensores.branco_preto_preto_preto()){ //BBPP//BPPP 

        robo.desligarTodosLeds();
        robo.ligarLed(3);
              
        while(!sensores.ehBrancoMaisDireito()){
            movimento.seguir(); 
        }
        while(sensores.ehBrancoEsquerdo()){
            movimento.girarParaDireita(); 
        }
        while(!sensores.ehBrancoEsquerdo()){
            movimento.girarParaEsquerda(); 
        }
          
    }else if(sensores.preto_preto_preto_preto()){    //PPPP
        robo.desligarTodosLeds();
        robo.ligarLed(2);
     	  movimento.seguir();  	
    }
}


void Estrategia::desviarObstaculo(){
    movimento.parar();
    delay(1000);
    
    robo.desligarTodosLeds();
       
    for(int i = 0; i < 3; i++){  
      robo.ligarTodosLeds();
      delay(250);
      robo.desligarTodosLeds();
      delay(250);
    }
    
    movimento.voltar();
    delay(50);
    
    while(sensores.ehBrancoMaisEsquerdo()){
        movimento.girarParaDireita(); 
    }
          
    while(sensores.ehBrancoMaisDireito()){
        movimento.girarSoDireita();
    }
    
    while(robo.lerSensorSonarEsq() > 15){
      movimento.seguir();  
    }

    movimento.parar();  
    delay(1000);

    while(robo.lerSensorSonarEsq() < 15){
      movimento.seguir();
      //delay(5);
    }

    movimento.parar();  
    delay(500);
  
    movimento.girarParaEsquerda();
    delay(470);

    movimento.parar();  
    delay(500);

    while(robo.lerSensorSonarEsq() > 15){
      movimento.seguir();  
    }

    movimento.parar();  
    delay(500);

    while(robo.lerSensorSonarEsq() < 15){
      movimento.seguir();
      //delay(5);
    }

    movimento.parar();  
    delay(500);
    
    movimento.girarParaEsquerda();
    delay(470);

    movimento.parar();  
    delay(500);
  
    movimento.seguir();
    delay(300);

    /*movimento.parar(); 
    delay(500);
    movimento.seguir(); 
    delay(400);
    movimento.parar(); 
    delay(500);

    for(int i = 0; i < 3; i++){
    robo.acionarMotores(30, 70);
    delay(450);
    robo.acionarMotores(0, 0);
    delay(500);
    }
    robo.acionarMotores(-30, 30);
    delay(400);*/
          
    while(sensores.ehBrancoEsquerdo() && sensores.ehBrancoDireito()){
        movimento.seguir(); 
    }        
 
    movimento.parar();  
    delay(500);
    
    while(!sensores.ehBrancoEsquerdo() && !sensores.ehBrancoDireito()){
        movimento.seguir(); 
    }

    while(sensores.ehBrancoMaisDireito()){
        movimento.girarParaDireita();    
    }
    movimento.seguir();
    delay(150);
    while(sensores.ehBrancoDireito()){
        movimento.girarParaDireita();    
    }
    movimento.seguir();
    delay(150);
    
    while(sensores.ehBrancoDireito()){
        movimento.girarParaDireita();    
    }
    while(!sensores.ehBrancoDireito()){
        movimento.girarParaDireita();    
    } 
    movimento.parar();
    delay(500);
    movimento.voltar();
    delay(200);
          
}

void Estrategia::subirRampa(){
    if(sensores.branco_branco_branco_branco()){           //BBBB    
        robo.acionarMotores(55,55);  
    }
    else if(sensores.preto_branco_branco_branco() || sensores.branco_preto_branco_branco()){       //PBBB//BPBB
        robo.acionarMotores(40,55);      
    }
    else if(sensores.branco_branco_preto_branco() || sensores.branco_branco_branco_preto()){       //BBPB//BBBP
        robo.acionarMotores(55,40);
    }
    else if(sensores.preto_preto_preto_preto()){          //PPPP 
        while (sensores.identificouRampa()){
            robo.acionarMotores(55,55);
        }

        //  ********************   COMEÇAMOS A SALA TRÊS AQUI!   ******************** 
        resgate.iniciar (); 
    }
}

  
void Estrategia::calibracao(){
    Serial.println(F("Pressione o Botão para Calibrar!"));
    Serial.println();
    for (int i = 1; i <= 10; i++){
        robo.ligarLed(3);

        // para calibrar a refletância
        if(robo.botao1Pressionado()){
            robo.desligarLed(3);
            robo.ligarLed(2);
            cali.menuCalibrar();
            robo.desligarTodosLeds(); 
        }
      
        // para calibrar a cor
        if(robo.botao3Pressionado()){
            robo.desligarLed(3);
            robo.ligarLed(1);
            cali.menuCor();
            robo.desligarTodosLeds(); 
        }
        Serial.println(F("Tentativa:"));
        Serial.println(i);
        delay(500); 
    }
    robo.ligarTodosLeds();
    sensores.dadosCalibracao();
    Serial.println(F("Robô Calibrado!"));
}

void Estrategia::fazerVerde(){
    
    movimento.parar();
    delay(200);
    movimento.seguir();
    delay(100);
    movimento.parar();
    delay(200);
    
    while(sensores.ehBrancoMaisDireito() && sensores.ehBrancoMaisEsquerdo()){
       robo.acionarMotores(-30,-30);
    }
    
    movimento.parar();
    delay(100);
    
    if (sensores.outro_verde()) { girarVerdeDir();}
    
    else if (sensores.verde_outro()) { girarVerdeEsq();}
    
    else if (sensores.verde_verde()) { girarVerdeBeco();}
    
    else{
            if(!sensores.ehBrancoMaisEsquerdo()){
          
              if(!sensores.ehBrancoMaisEsquerdo()){
                movimento.seguir();
                delay(100);   
              }
              while(sensores.ehBrancoMaisDireito()){
                movimento.girarParaEsquerda(); 
              }
              while(!sensores.ehBrancoMaisDireito()){
                movimento.girarParaDireita();   
              }   
            }
            else if(!sensores.ehBrancoMaisDireito()){
              
              if(!sensores.ehBrancoMaisEsquerdo()){
                movimento.seguir();
                delay(100);   
              }
              while(sensores.ehBrancoMaisEsquerdo()){
                movimento.girarParaDireita();
              }
              while(!sensores.ehBrancoMaisEsquerdo()){
                movimento.girarParaEsquerda();
              }
            }
            else{

              while(!sensores.ehBrancoMaisDireito() && !sensores.ehBrancoMaisDireito()){
                movimento.seguir();   
              }
            }
    }
}

void Estrategia::girarVerdeEsq(){

  robo.desligarTodosLeds();
  
    for(int i = 0; i < 5; i++){
       robo.ligarLed(1);
       delay(100);
       robo.desligarLed(1);
       delay(100); 
    }
    
    robo.acionarMotores(35, 35);
    delay(200);
    
    while(sensores.ehBrancoMaisEsquerdo()){
       movimento.girarParaEsquerda(); 
    } 
    while(!sensores.ehBrancoMaisEsquerdo()){
       movimento.girarParaEsquerda(); 
    }     
  }
  
  void Estrategia::girarVerdeDir(){

    robo.desligarTodosLeds();
    
    for(int i = 0; i < 5; i++){
       robo.ligarLed(1);
       delay(100);
       robo.desligarLed(1);
       delay(100); 
    }
    
    robo.acionarMotores(35, 35);
    delay(200);
     
    while(sensores.ehBrancoMaisDireito()){
       movimento.girarParaDireita(); 
    }
    while(!sensores.ehBrancoMaisDireito()){
       movimento.girarParaDireita(); 
    } 
  }
  
  void Estrategia::girarVerdeBeco(){
    
    robo.desligarTodosLeds();
    
    for(int i = 0; i < 5; i++){
       robo.ligarLed(3);
       delay(100);
       robo.desligarLed(3);
       delay(100); 
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

void Estrategia::executar(){

    /*if(sensores.testarVerde()){
        fazerVerde();
    }
    else */if(sensores.detectouObstaculo()){
        desviarObstaculo();
    }
    else if (sensores.identificouRampa()){ 
        robo.desligarTodosLeds();
        robo.ligarTodosLeds();
        subirRampa();  
    }
    else{
        seguirLinha();
    }

    
}
