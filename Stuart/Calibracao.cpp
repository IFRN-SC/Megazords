#include <robo_hardware2.h> 
#include "Calibracao.h"

Calibracao:: Calibracao(){
    calibracao_dados cd;
    robo.lerCalibracao(cd);
    mediaDireito = cd.refletanciaDir;
    mediaEsquerdo = cd.refletanciaEsq;
    mediaMaisDireito  = cd.refletanciaMaisDir;
    mediaMaisEsquerdo = cd.refletanciaMaisEsq;
    cor_direito = ((cd.verdeDir.h + cd.brancoDir.h)/2);
    cor_esquerdo = ((cd.verdeEsq.h + cd.brancoEsq.h)/2);
}

void Calibracao::menuCor() {
    char controle = "t"; 
    Serial.println (F("CALIBRE COR"));
    Serial.println();
    while (1){
        Serial.print(F("BRANCO ESQUERDO : "));
        Serial.println (robo.getHSVEsquerdo().h);
        if (Serial.available()){
            controle = Serial.read();
            if(controle == 's'){
              brancoEsq = robo.getHSVEsquerdo().h;
              break;
            }
        }
        delay(500);
    } 
    while (1){
        Serial.print(F("BRANCO DIREITO : "));
        Serial.println (robo.getHSVDireito().h);
        if (Serial.available()){
            controle = Serial.read();
            if(controle == 's'){
                brancoDir = robo.getHSVDireito().h;
                break;
            }
        }
        delay(500);
    }
    while (1){
        Serial.print(F("VERDE ESQUERDO : "));
        Serial.println (robo.getHSVEsquerdo().h);
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                verdeEsq = robo.getHSVEsquerdo().h;
                break;
            }
        }
        delay(500);
    }     
    while (1){
        Serial.print(F("VERDE DIREITO : "));
        Serial.println (robo.getHSVDireito().h);
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                verdeDir = robo.getHSVDireito().h;
                break;
            }
        }
        delay(500);
    }

    // mostrar as médias de H 
    cor_direito = ((verdeDir + brancoDir)/2);
    cor_esquerdo = ((verdeEsq + brancoEsq)/2);

    Serial.println ();
    Serial.print (F("COR DIREITO: "));
    Serial.println (cor_direito);
    Serial.print (F("COR ESQUERDO: "));
    Serial.println (cor_esquerdo);

    // Salvar dados da Calibracao na EEPROM
    calibracao_dados cd;
    cd.verdeDir.h = verdeDir;
    cd.verdeEsq.h = verdeEsq;
    cd.brancoDir.h = brancoDir;
    cd.brancoEsq.h = brancoEsq;
    robo.salvarCalibracao(cd);
}

void Calibracao::menuCalibrar(){
    char controle = 't'; 
    Serial.println(F("CALIBRE BRANCO"));
    while(1){
        Serial.print(F("MAIS ESQUERDO : "));
        Serial.print(robo.lerSensorLinhaMaisEsqSemRuido());
        Serial.print(F("  |  ESQUERDO : "));
        Serial.print(robo.lerSensorLinhaEsqSemRuido());
        Serial.print(F("  |  DIREITO : "));
        Serial.print(robo.lerSensorLinhaDirSemRuido());
        Serial.print(F("  |  MAIS DIREITO : "));
        Serial.println(robo.lerSensorLinhaMaisDirSemRuido());
      
        // Verifica se o testador  quer terminar ou não a calibração para esse sensor
     
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                controle = 't';
                caliBrancoEsquerdo = robo.lerSensorLinhaEsqSemRuido();
                caliBrancoMaisEsquerdo = robo.lerSensorLinhaMaisEsqSemRuido();
                caliBrancoDireito = robo.lerSensorLinhaDirSemRuido();
                caliBrancoMaisDireito = robo.lerSensorLinhaMaisDirSemRuido(); 
                break;
            }
        }
        delay(500);  
    }
    
    // Mostra os valores do preto do sensor de refletancia mais esquerdo
    
    Serial.println(F("CALIBRE PRETO MAIS ESQUERDO"));
    while(1){
        Serial.print(F("MAIS ESQUERDO : "));
        Serial.println(robo.lerSensorLinhaMaisEsqSemRuido());
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                controle = 't';
                caliPretoMaisEsquerdo = robo.lerSensorLinhaMaisEsqSemRuido();
                break;
            } 
        }  
        delay(500);
    }    
    
    Serial.println(F("CALIBRE PRETO ESQUERDO"));
    while(1){
        Serial.print(F("ESQUERDO : "));
        Serial.println(robo.lerSensorLinhaEsqSemRuido());
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                controle = 't';
                caliPretoEsquerdo = robo.lerSensorLinhaEsqSemRuido();
                break; 
            }
        }
        delay(500);
    }
   
    Serial.println(F("CALIBRE PRETO DIREITO"));
    while(1){
        Serial.print(F("DIREITO : "));
        Serial.println(robo.lerSensorLinhaDirSemRuido());
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                controle = 't';
                caliPretoDireito = robo.lerSensorLinhaDirSemRuido();
                break;
            } 
        }
        delay(500);
    }
    Serial.println(F("CALIBRE PRETO MAIS DIREITO"));
    while(1){
        Serial.print(F("MAIS DIREITO : "));
        Serial.println(robo.lerSensorLinhaMaisDirSemRuido());
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                controle = 't';
                caliPretoMaisDireito = robo.lerSensorLinhaMaisDirSemRuido();
                break; 
            }
        }
        delay(500);  
    }

    // Faz a média de acordo com os valores "capturados"  
    mediaMaisEsquerdo = (caliBrancoMaisEsquerdo + caliPretoMaisEsquerdo) / 2;
    mediaEsquerdo = (caliBrancoEsquerdo + caliPretoEsquerdo) / 2;
    mediaDireito = (caliBrancoDireito + caliPretoDireito) / 2;
    mediaMaisDireito = (caliBrancoMaisDireito + caliPretoMaisDireito) / 2;
  
    // Salvar dados da Calibracao na EEPROM
    calibracao_dados cd;
    cd.refletanciaDir = mediaDireito; 
    cd.refletanciaEsq = mediaEsquerdo;
    cd.refletanciaMaisDir = mediaMaisDireito;
    cd.refletanciaMaisEsq = mediaMaisEsquerdo;
    robo.salvarCalibracao(cd);
    
    Serial.println();
    Serial.println();
  
    // Imprime os valores das médias 
    Serial.print(F("Valores finais: "));
    Serial.print(F("MAIS ESQUERDO : "));
    Serial.print(mediaMaisEsquerdo);
    Serial.print(F("  |  ESQUERDO : "));
    Serial.print(mediaEsquerdo);
    Serial.print(F("  |  DIREITO : "));
    Serial.print(mediaDireito);
    Serial.print(F("  |  MAIS DIREITO : "));
    Serial.println(mediaMaisDireito);
}

Calibracao::dadosCalibracao(){
    calibracao_dados cd;
    robo.lerCalibracao(cd);
    mediaDireito = cd.refletanciaDir;
    mediaEsquerdo = cd.refletanciaEsq;
    mediaMaisDireito  = cd.refletanciaMaisDir;
    mediaMaisEsquerdo = cd.refletanciaMaisEsq;
    
    
    Serial.println(mediaMaisEsquerdo);
    Serial.println(mediaEsquerdo);
    Serial.println(mediaDireito);
    Serial.println(mediaMaisDireito);

    // pegar os valores salvos de H
    cor_direito = ((cd.verdeDir.h + cd.brancoDir.h)/2);
    cor_esquerdo = ((cd.verdeEsq.h + cd.brancoEsq.h)/2);
}    
