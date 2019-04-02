#include <robo_hardware2.h> 
#include "Calibracao.h"

int caliPretoEsquerdo, caliPretoMaisEsquerdo, caliPretoDireito, caliPretoMaisDireito;
int caliBrancoEsquerdo, caliBrancoMaisEsquerdo, caliBrancoDireito, caliBrancoMaisDireito; 
float verdeDir, verdeEsq, brancoDir,brancoEsq;

Calibracao:: Calibracao(){
    calibracao_dados cd;
    robo.lerCalibracao(cd);
    mediaDireito = cd.refletanciaDir;
    mediaEsquerdo = cd.refletanciaEsq;
    mediaMaisDireito  = cd.refletanciaMaisDir;
    mediaMaisEsquerdo = cd.refletanciaMaisEsq;
    cor_direito = ((cd.verdeDir.s + cd.brancoDir.s)/2);
    cor_esquerdo = ((cd.verdeEsq.s + cd.brancoEsq.s)/2);
}

void Calibracao::testeRobo (){  
    robo.acionarMotores (40,40);
    delay (1000);
    robo.acionarMotores (40,-40);
    delay (1000);
    robo.acionarMotores (-40,40);
    delay (1000);
    robo.acionarMotores (-40,-40);
    delay (1000);
}

void Calibracao::menuCor() {
    char controle = "t"; 
    Serial.println ("CALIBRE COR");
    Serial.println();
    while (1){
        Serial.print("BRANCO ESQUERDO : ");
        Serial.println (robo.getHSVEsquerdo().s);
        if (Serial.available()){
            controle = Serial.read();
            if(controle == 's'){
              brancoEsq = robo.getHSVEsquerdo().s;
              break;
            }
        }
        delay(500);
    } 
    while (1){
        Serial.print("BRANCO DIREITO : ");
        Serial.println (robo.getHSVDireito().s);
        if (Serial.available()){
            controle = Serial.read();
            if(controle == 's'){
                brancoDir = robo.getHSVDireito().s;
                break;
            }
        }
        delay(500);
    }
    while (1){
        Serial.print("VERDE ESQUERDO : ");
        Serial.println (robo.getHSVEsquerdo().s);
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                verdeEsq = robo.getHSVEsquerdo().s;
                break;
            }
        }
        delay(500);
    }     
    while (1){
        Serial.print("VERDE DIREITO : ");
        Serial.println (robo.getHSVDireito().s);
        if (Serial.available()){
            controle = Serial.read();
            if (controle == 's'){
                verdeDir = robo.getHSVDireito().s;
                break;
            }
        }
        delay(500);
    }

    // mostrar as médias de S 
    cor_direito = ((verdeDir + brancoDir)/2);
    cor_esquerdo = ((verdeEsq + brancoEsq)/2);

    Serial.println ();
    Serial.print ("COR DIREITO: ");
    Serial.println (cor_direito);
    Serial.print ("COR ESQUERDO: ");
    Serial.println (cor_esquerdo);

    // Salvar dados da Calibracao na EEPROM
    calibracao_dados cd;
    cd.verdeDir.s = verdeDir;
    cd.verdeEsq.s = verdeEsq;
    cd.brancoDir.s = brancoDir;
    cd.brancoEsq.s = brancoEsq;
    robo.salvarCalibracao(cd);
}

void Calibracao::menuCalibrar(){
    char controle = 't'; 
    Serial.println("CALIBRE BRANCO");
    while(1){
        Serial.print("MAIS ESQUERDO : ");
        Serial.print(robo.lerSensorLinhaMaisEsqSemRuido());
        Serial.print("  |  ESQUERDO : ");
        Serial.print(robo.lerSensorLinhaEsqSemRuido());
        Serial.print("  |  DIREITO : ");
        Serial.print(robo.lerSensorLinhaDirSemRuido());
        Serial.print("  |  MAIS DIREITO : ");
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
    
    Serial.println("CALIBRE PRETO MAIS ESQUERDO");
    while(1){
        Serial.print("MAIS ESQUERDO : ");
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
    
    Serial.println("CALIBRE PRETO ESQUERDO");
    while(1){
        Serial.print("ESQUERDO : ");
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
   
    Serial.println("CALIBRE PRETO DIREITO");
    while(1){
        Serial.print("DIREITO : ");
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
    Serial.println("CALIBRE PRETO MAIS DIREITO");
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

    // pegar os valores salvos de S
    cor_direito = ((cd.verdeDir.s + cd.brancoDir.s)/2);
    cor_esquerdo = ((cd.verdeEsq.s + cd.brancoEsq.s)/2);
}    
