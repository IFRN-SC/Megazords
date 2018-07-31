#include <robo_hardware2.h> 
#include "Calibracao.h"

int caliPretoEsquerdo, caliPretoMaisEsquerdo, caliPretoDireito, caliPretoMaisDireito;
int caliBrancoEsquerdo, caliBrancoMaisEsquerdo, caliBrancoDireito, caliBrancoMaisDireito; 

  Calibracao:: Calibracao(){
    
    calibracao_dados cd;

    robo.lerCalibracao(cd);
    
    mediaDireito = cd.refletancia_dir;
    mediaEsquerdo = cd.refletancia_esq;
    mediaMaisDireito  = cd.refletancia_mais_dir;
    mediaMaisEsquerdo = cd.refletancia_mais_esq;
  }

Calibracao::calibreBrancos(){
     char controle = 't';
  
  Serial.println("CALIBRE BRANCO");
  while(1){
    Serial.print("MAIS ESQUERDO : ");
    Serial.print(robo.lerSensorLinhaMaisEsq());
    Serial.print("  |  ESQUERDO : ");
    Serial.print(robo.lerSensorLinhaEsq());
    Serial.print("  |  DIREITO : ");
    Serial.print(robo.lerSensorLinhaDir());
    Serial.print("  |  MAIS DIREITO : ");
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
  }
void Calibracao::menuCalibrar(){
  
  calibreBrancos();
}
