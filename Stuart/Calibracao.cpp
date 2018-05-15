#include <robo_hardware2.h> 
#include "Calibracao.h"

  /*
  float valor_sensor_dir;
  float valor_sensor_mais_dir;
  float valor_sensor_esq;
  float valor_sensor_mais_esq;
  */
  int mediaEsquerdo = 47;
  int mediaDireito = 47;
  int mediaMaisDireito = 47;
  int mediaMaisEsquerdo = 47;

  int caliPretoEsquerdo, caliPretoMaisEsquerdo, caliPretoDireito, caliPretoMaisDireito;
  int caliBrancoEsquerdo, caliBrancoMaisEsquerdo, caliBrancoDireito, caliBrancoMaisDireito; 

void calibracao(){
  char controle = 't';
  Serial.println("CALIBRE BRANCO");
  while(1){
    Serial.print("MAIS ESQUERDO : ");
    Serial.print(robo.lerSensorLinhaMaisEsq());
    Serial.print("  ||  ESQUERDO : ");
    Serial.print(robo.lerSensorLinhaEsq());
    Serial.print("  ||  DIREITO : ");
    Serial.print(robo.lerSensorLinhaDir());
    Serial.print("  ||  MAIS DIREITO : ");
    Serial.println(robo.lerSensorLinhaMaisDir());
    
 // Verifica se o testador  quer terminar ou não a calibração para esse sensor
     
    if(Serial.available()){
       controle = Serial.read();
       if(controle == 's'){
         controle = 't';
         caliBrancoEsquerdo = robo.lerSensorLinhaEsq();
         caliBrancoMaisEsquerdo = robo.lerSensorLinhaMaisEsq();
         caliBrancoDireito = robo.lerSensorLinhaDir();
         caliBrancoMaisDireito = robo.lerSensorLinhaMaisDir(); 
         break;
       }
     }
    delay(500);  
  }
// Mostra os valores do preto do sensor de refletancia mais esquerdo

  Serial.println("CALIBRE PRETO MAIS ESQUERDO");
  while(1){
     Serial.print("MAIS ESQUERDO : ");
     Serial.println(robo.lerSensorLinhaMaisEsq());
     if(Serial.available()){
      controle = Serial.read();
      if(controle == 's'){
       controle = 't';
       caliPretoMaisEsquerdo = robo.lerSensorLinhaMaisEsq();
       break;
      } 
     } 
     delay(500);
   }
  Serial.println("CALIBRE PRETO ESQUERDO");
  while(1){
    Serial.print("ESQUERDO : ");
    Serial.println(robo.lerSensorLinhaEsq());
    if(Serial.available()){
       controle = Serial.read();
      if(controle == 's'){
       controle = 't';
       caliPretoEsquerdo = robo.lerSensorLinhaEsq();
       break; 
      }
    }
    delay(500);
  }
   
    Serial.println("CALIBRE PRETO DIREITO");
  while(1){
    Serial.print("DIREITO : ");
    Serial.println(robo.lerSensorLinhaDir());
    if(Serial.available()){
       controle = Serial.read();
      if(controle == 's'){
       controle = 't';
       caliPretoDireito = robo.lerSensorLinhaDir();
       break;
      } 
    }
    delay(500);
  }
   Serial.println("CALIBRE PRETO MAIS DIREITO");
  while(1){
    Serial.print("MAIS DIREITO : ");
    Serial.println(robo.lerSensorLinhaMaisDir());
    
    if(Serial.available()){
       controle = Serial.read();
      if(controle == 's'){
         controle = 't';
         caliPretoMaisDireito = robo.lerSensorLinhaMaisDir();
         break; 
      }
    }
    delay(500);  
  }

  // Faz a média de acordo com os valores "capturados"
  
  mediaEsquerdo = (caliBrancoEsquerdo + caliPretoEsquerdo) / 2;
  mediaMaisEsquerdo = (caliBrancoMaisEsquerdo + caliPretoMaisEsquerdo) / 2;
  mediaDireito = (caliBrancoDireito + caliPretoDireito) / 2;
  mediaMaisDireito = 45;

  Serial.println(" ");
  // Imprime os valores das médias
  Serial.println("Valores finais: ");
  Serial.print("MAIS ESQUERDO : ");
    Serial.print(mediaMaisEsquerdo);
    Serial.print("  ||  ESQUERDO : ");
    Serial.print(mediaEsquerdo);
    Serial.print("  ||  DIREITO : ");
    Serial.print(mediaDireito);
    Serial.print("  ||  MAIS DIREITO : ");
    Serial.println(mediaMaisDireito);
}
