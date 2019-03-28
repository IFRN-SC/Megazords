#include "Resgate.h"

Resgate::Resgate(){
}

char Resgate::indentificaZona (){
    // zona direita 'A' || zona esquerda 'B' || zona bunda 'C'
    float valorEsq = robo.lerSensorSonarEsq ();
    float valorFrontal = robo.lerSensorSonarFrontal ();
    robo.desligarTodosLeds();
     
    if (valorFrontal < 50){      
        robo.ligarLed(1);
        return 'a';
    }else if (valorEsq < 50){
        robo.ligarLed(3);
        return 'b';
    }else{
        robo.ligarLed(2);
        return 'c'; 
    }
}

void Resgate::noventaEsquerda() {
    robo.acionarMotores(-40,40);
    delay (550);
    robo.acionarMotores(40,40);
    delay (300);
    robo.acionarMotores (0,0);
    delay (1000);
    robo.acionarMotores(40,-40);
    delay (650);
}

void Resgate::entrarNaSala (){
    robo.acionarMotores(60,20);
    delay (500);

    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores(40,-40);
        delay (50);
        robo.acionarMotores(0,0);
        delay (1000);
    }

    robo.acionarMotores(40,-40);
    delay (280);
    robo.acionarMotores(0,0);
    delay (2000);
}

void Resgate::alinhar (){
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (250);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (250);
    robo.acionarMotores(-40,-40);
    delay (500);
}

void Resgate::areaResgate (){
    if (zona == 'a'){
        // ir para a zona direita
    }else if (zona == 'b'){
        // ir para a zona esquerda
    }else {
        // ir para a zona bunda
        robo.acionarMotores (40,38);
        delay (1100);
        robo.acionarMotores(-40,40);
        delay (550);
        
        this -> alinhar ();

        robo.acionarMotores(0,0);
        delay (1000);

        while (robo.lerSensorSonarFrontal () > 30){
            robo.acionarMotores (40,38);
        }

        robo.acionarMotores(-40,40);
        delay (550);
        robo.acionarMotores (-40,-38);
        delay (700);

        robo.acionarMotores(-40,40);
        delay (270);
        robo.acionarMotores (-40,-38);
        delay (300);
        this-> alinhar ();


        robo.acionarMotores(-40,40);
        delay (1100);
    
        robo.acionarMotores (40,38);
        delay (150);
    }
}


void Resgate::seguirNaSala (){
    for (int i = 0; i < 3; i++){
        garra.baixar();
        garra.abrir ();
        
        robo.acionarMotores (40,38);
        delay (2000);
        robo.acionarMotores (0,0);
        delay (2000);

        garra.fechar ();
        garra.subir ();
    
        robo.acionarMotores (-40,-38);
        delay (2000);

        this -> alinhar ();        

        //verifica se encontrou a bolinha 
        float sonar = robo.lerSensorSonarFrontal ();
        if (sonar <= 10){
             for(int i = 0; i < 5; i++){  
                 robo.ligarTodosLeds();
                 delay(350);
                 robo.desligarTodosLeds();
                 delay(200);
             }
             this -> areaResgate ();
             break;
        }else {
             this -> noventaEsquerda ();      
             this -> alinhar ();
        }
        
    }
    robo.acionarMotores(0,0);
    delay(10000);    
}
