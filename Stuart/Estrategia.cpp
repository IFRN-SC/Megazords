#include "Estrategia.h"
#include "Calibracao.h"

Estrategia::Estrategia (){  
}



/***************** CURVAS ******************/
/* 
 *    verificar beco sem saida - 1
 *    verificar direito verde  - 2
 *    verificar esquerdo verde - 3
 * 
 */





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
        alinharCurva();
        if (!(fazerVerde(1) && fazerVerde(3))){
            robo.desligarTodosLeds();
            robo.ligarLed(1);
          
            movimento.seguir();
            delay(200);
            
            while(sensores.ehBrancoDireito()){
                movimento.girarParaEsquerda(); 
            } 
            while(!sensores.ehBrancoDireito()){
                movimento.girarParaDireita(); 
            }
        }
               
    }else if(sensores.branco_branco_preto_preto() || sensores.branco_preto_preto_preto()){ //BBPP//BPPP 
        alinharCurva();
        if (!(fazerVerde(1) && fazerVerde(2))){
            robo.desligarTodosLeds();
            robo.ligarLed(3);
                  
            
            movimento.seguir();
            delay(200); 
            
            while(sensores.ehBrancoEsquerdo()){
                movimento.girarParaDireita(); 
            }
            while(!sensores.ehBrancoEsquerdo()){
                movimento.girarParaEsquerda(); 
            }
        }  
    }
    else if(sensores.preto_preto_preto_preto()){    //PPPP
        alinharCurva();
        if (!(fazerVerde(1) && fazerVerde(2) && fazerVerde(3))){
            robo.desligarTodosLeds();
            robo.ligarLed(2);
            movimento.seguir();     
        }
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
      delay(10);
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
      delay(10);
    }

    movimento.parar();  
    delay(500);
    
    movimento.girarParaEsquerda();
    delay(450);

    movimento.parar();  
    delay(500);
  
    movimento.seguir();
    delay(300);
          
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
        //movimento.girarParaDireita(); 
        robo.acionarMotores(20, -20);   
    }
    while(!sensores.ehBrancoDireito()){
        //movimento.girarParaDireita();
        robo.acionarMotores(20, -20);    
    } 
    movimento.parar();
    delay(1000);
    movimento.voltar();
    delay(100);
}

void Estrategia::subirRampa(){
    if(sensores.branco_branco_branco_branco()){           //BBBB    
        robo.acionarMotores(55,55);  
    }
    else if(sensores.preto_branco_branco_branco() || sensores.branco_preto_branco_branco() || sensores.preto_preto_branco_branco()){       //PBBB//BPBB//PPBB             
        robo.acionarMotores(35,55);      
    }
    else if(sensores.branco_branco_preto_branco() || sensores.branco_branco_branco_preto() || sensores.branco_branco_preto_preto()){       //BBPB//BBBP//BBPP
        robo.acionarMotores(55,35);
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

void Estrategia::alinharCurva (){ 
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
    delay(200);
}

boolean Estrategia::fazerVerde(int curva){
    switch (curva) {
        case 1:
            if (sensores.verde_verde()) { 
                for(int i = 0; i < 5; i++){
                   robo.ligarLed(2);
                   delay(100);
                   robo.desligarLed(2);
                   delay(100); 
                }
                girarVerdeBeco();
                return true;
            }
            return false;
            break;
            
        case 2:
            if (sensores.outro_verde()) { 
                for(int i = 0; i < 5; i++){
                   robo.ligarLed(3);
                   delay(100);
                   robo.desligarLed(3);
                   delay(100); 
                }
                girarVerdeDir();
                return true;
            }
            return false;
            break;
            

        case 3:
            if (sensores.verde_outro()) { 
                for(int i = 0; i < 5; i++){
                   robo.ligarLed(1);
                   delay(100);
                   robo.desligarLed(1);
                   delay(100); 
                }
                girarVerdeEsq();
                return true;
            }
            return false;
            break;
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

    if(sensores.detectouObstaculo()){
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
