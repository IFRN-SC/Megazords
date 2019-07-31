#include <robo_hardware2.h> 
#include "Calibracao.h"

Calibracao:: Calibracao(){
   
    robo.lerCalibracao(cd);
    mediaDireito = cd.refletanciaDir;
    mediaEsquerdo = cd.refletanciaEsq;
    mediaMaisDireito  = cd.refletanciaMaisDir;
    mediaMaisEsquerdo = cd.refletanciaMaisEsq;

    
    cor_direito = ((cd.verdeDir.s + cd.brancoDir.s)/2);
    cor_esquerdo = ((cd.verdeEsq.s + cd.brancoEsq.s)/2);

    // imprimir a calibração
    Serial.println ();
    Serial.println ();
    Serial.println ();
    Serial.print (F("-------------------------------"));
    Serial.print (F("   MAIS ESQUERDO:   "));
    Serial.print (mediaMaisEsquerdo);
    Serial.print (F("   ESQUERDO:   "));
    Serial.print (mediaEsquerdo);
    Serial.print (F("   DIREITO:   "));
    Serial.print (mediaDireito);
    Serial.print (F("   MAIS DIREITO:   "));
    Serial.print (mediaMaisDireito);
    Serial.println (F("-------------------------------"));
    Serial.println ();
    Serial.println ();
    Serial.print (F("-------------------------------"));
    Serial.print (F("   COR ESQUERDO:   "));
    Serial.print (((cd.verdeEsq.s + cd.brancoEsq.s)/2));
    Serial.print (F("   COR DIREITO:    "));
    Serial.print (((cd.verdeDir.s + cd.brancoDir.s)/2));
    Serial.print (F("-------------------------------"));
    Serial.println ();
    Serial.println ();
    Serial.println ();
}

void Calibracao::menuCor() {
    char controle = "t"; 
    Serial.println (F("CALIBRE COR"));
    Serial.println();
    while (1){
        Serial.print(F("BRANCO ESQUERDO : "));
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
        Serial.print(F("BRANCO DIREITO : "));
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
        Serial.print(F("VERDE ESQUERDO : "));
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
        Serial.print(F("VERDE DIREITO : "));
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

    // mostrar as médias de H 
    cor_direito = ((verdeDir + brancoDir)/2);
    cor_esquerdo = ((verdeEsq + brancoEsq)/2);

    Serial.println (); 
    Serial.println (); 
    Serial.println ();
    Serial.println (); 
    Serial.println ();
    Serial.print (F("COR DIREITO: "));
    Serial.println (cor_direito);
    Serial.print (F("COR ESQUERDO: "));
    Serial.println (cor_esquerdo);

    // Salvar dados da Calibracao na EEPROM
 
    cd.verdeDir.s = verdeDir;
    cd.verdeEsq.s = verdeEsq;
    cd.brancoDir.s = brancoDir;
    cd.brancoEsq.s = brancoEsq;
    salvaCalibracao(cd);
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
   
    cd.refletanciaDir = mediaDireito; 
    cd.refletanciaEsq = mediaEsquerdo;
    cd.refletanciaMaisDir = mediaMaisDireito;
    cd.refletanciaMaisEsq = mediaMaisEsquerdo;
    salvaCalibracao(cd);
    
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
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

    robo.lerCalibracao(cd);
    mediaDireito = cd.refletanciaDir;
    mediaEsquerdo = cd.refletanciaEsq;
    mediaMaisDireito  = cd.refletanciaMaisDir;
    mediaMaisEsquerdo = cd.refletanciaMaisEsq;
    
    
    Serial.println(mediaMaisEsquerdo);
    Serial.println(mediaEsquerdo);
    Serial.println(mediaDireito);
    Serial.println(mediaMaisDireito);

    // pegar os valores salvos de s
    cor_direito = ((cd.verdeDir.s + cd.brancoDir.s)/2);
    cor_esquerdo = ((cd.verdeEsq.s + cd.brancoEsq.s)/2);
} 

void Calibracao::salvaCalibracao(calibracao_dados dadosAtuais){
  
    robo.lerCalibracao(cd);
    
    if(dadosAtuais.refletanciaDir != cd.refletanciaDir){
        cd.refletanciaDir = dadosAtuais.refletanciaDir;
    }
    if(dadosAtuais.refletanciaMaisDir != cd.refletanciaMaisDir){
        cd.refletanciaMaisDir = dadosAtuais.refletanciaMaisDir;  
    }
    if(dadosAtuais.refletanciaEsq != cd.refletanciaEsq){
        cd.refletanciaEsq = dadosAtuais.refletanciaEsq; 
    }
    if(dadosAtuais.refletanciaMaisEsq != cd.refletanciaMaisEsq){
        cd.refletanciaMaisEsq = dadosAtuais.refletanciaMaisEsq;  
    }
    if(dadosAtuais.brancoDir.s != cd.brancoDir.s){
        cd.brancoDir.s = dadosAtuais.brancoDir.s;
    }
    if(dadosAtuais.brancoEsq.s != cd.brancoEsq.s){
        cd.brancoEsq.s = dadosAtuais.brancoEsq.s; 
    }
    if(dadosAtuais.verdeDir.s != cd.verdeDir.s){
        cd.verdeDir.s = dadosAtuais.verdeDir.s; 
    }
    if(dadosAtuais.verdeEsq.s != cd.verdeEsq.s){
        cd.verdeEsq.s = dadosAtuais.verdeEsq.s; 
    }

    robo.salvarCalibracao(cd);

    // imprimir a calibração
    Serial.println ();
    Serial.println ();
    Serial.println ();
    Serial.print (F("-------------------------------"));
    Serial.print (F("   MAIS ESQUERDO:   "));
    Serial.print (mediaMaisEsquerdo);
    Serial.print (F("   ESQUERDO:   "));
    Serial.print (mediaEsquerdo);
    Serial.print (F("   DIREITO:   "));
    Serial.print (mediaDireito);
    Serial.print (F("   MAIS DIREITO:   "));
    Serial.print (mediaMaisDireito);
    Serial.println (F("-------------------------------"));
    Serial.println ();
    Serial.println ();
    Serial.print (F("-------------------------------"));
    Serial.print (F("   COR ESQUERDO:   "));
    Serial.print (((cd.verdeEsq.s + cd.brancoEsq.s)/2));
    Serial.print (F("   COR DIREITO:    "));
    Serial.print (((cd.verdeDir.s + cd.brancoDir.s)/2));
    Serial.print (F("-------------------------------"));
    Serial.println ();
    Serial.println ();
    Serial.println ();
}
