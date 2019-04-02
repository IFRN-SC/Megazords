#include "Resgate.h"

Resgate::Resgate(){
}

char Resgate::indentificaZona (){
    float valorEsq = robo.lerSensorSonarEsq ();
    float valorFrontal = robo.lerSensorSonarFrontal ();
    robo.desligarTodosLeds();
     
    if (valorFrontal < 50){      
        robo.ligarLed(3);
        return 'a';
    }    
    else if (valorEsq < 50){
        robo.ligarLed(1);
        return 'b';
    }else{
        robo.ligarLed(2);
        return 'c'; 
    }
}

void Resgate::noventaEsquerda() {
    robo.acionarMotores(-40,40);
    delay (550);
    robo.acionarMotores(0,0);
    delay (1000);
    
    garra.baixar ();
    garra.abrir ();
    
   
    robo.acionarMotores(40,40);
    delay (600);
    
    garra.fechar ();
    robo.acionarMotores (0,0);
    delay (1000);
   
    garra.subir ();
    robo.acionarMotores(40,-40);
    delay (550);
}

void Resgate::entrarNaSala (){
    robo.acionarMotores(60,20);
    delay (520);

    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores(40,-40);
        delay (50);
        robo.acionarMotores(0,0);
        delay (1000);
    }

    robo.acionarMotores(40,-40);
    delay (280);
    robo.acionarMotores(0,0);
    delay (3000);
}

void Resgate::alinhar (){
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (300);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(0,0);
    delay (2000);
}

void Resgate::seguirNaSala (){
    for (int i = 0; i < 3; i++){
        garra.baixar();
        garra.abrir();

        robo.acionarMotores (0,0);
        delay (2000);

        
        robo.acionarMotores (40,38);
        delay (2100);
        robo.acionarMotores (0,0);
        delay (2000);

        garra.fechar();
        robo.acionarMotores (0,0);
        delay (500);

        robo.acionarMotores (-40,-38);
        delay (2000);

        this -> alinhar ();

        garra.abrir();
        garra.subir();

        robo.acionarMotores (0,0);
        delay(2000);

        if (robo.lerSensorSonarFrontal () <= 20){
             for(int i = 0; i < 7; i++){  
                 robo.ligarTodosLeds();
                 delay(400);
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



void Resgate::areaResgate (){
    robo.acionarServoGarra2 (0);
    robo.acionarMotores (0,0);
    delay (1000);       
   
    robo.acionarServoGarra1 (180);
    robo.acionarMotores (0,0);
    delay (1000);       
   
    robo.acionarServoGarra1 (130);
    robo.acionarMotores (0,0);
    delay (1000);       
    robo.acionarServoGarra2 (100);
    robo.acionarMotores (0,0);
    delay (1000);       
    

    
    if (zona == 'a'){ 
        robo.acionarMotores (40,38);
        delay (2100);
        robo.acionarMotores(-40,40);
        delay (1100);

        robo.acionarMotores (40,38);
        delay (150);
        
        robo.acionarServoGarra2 (30);
        robo.acionarMotores (0,0);
        delay (1000);
        
        robo.acionarServoGarra1 (180);
        robo.acionarMotores (0,0);
        delay (1000);
    }   
    else if (zona == 'b'){
        robo.acionarMotores (40,38);
        delay (1100);
        robo.acionarMotores(-40,40);
        delay (550);
        this -> alinhar ();      
          
        while (robo.lerSensorSonarFrontal () > 30){
            robo.acionarMotores (40,38);
        }

        robo.acionarMotores(40,-40);
        delay (550);
        robo.acionarMotores (-40,-38);
        delay (800);

        robo.acionarMotores(40,-40);
        delay (270);
        robo.acionarMotores (-40,-38);
        delay (500);

        robo.acionarMotores(-40,40);
        delay (1100);
    
        robo.acionarMotores (40,38);
        delay (150);
        
        robo.acionarServoGarra2 (30);
        robo.acionarMotores (0,0);
        delay (1000);
        
        robo.acionarServoGarra1 (180);
        robo.acionarMotores (0,0);
        delay (1000);
    }
    
    else {
        robo.acionarMotores (40,38);
        delay (1100);
        robo.acionarMotores(-40,40);
        delay (550);
        this -> alinhar ();      
          
        while (robo.lerSensorSonarFrontal () > 30){
            robo.acionarMotores (40,38);
        }
     
        robo.acionarMotores(-40,40);
        delay (550);
        robo.acionarMotores (-40,-38);
        delay (800);

        robo.acionarMotores(-40,40);
        delay (270);
        robo.acionarMotores (-40,-38);
        delay (500);

        robo.acionarMotores(-40,40);
        delay (1100);
    
        robo.acionarMotores (40,38);
        delay (150);
        
        robo.acionarServoGarra2 (30);
        robo.acionarMotores (0,0);
        delay (1000);
        
        robo.acionarServoGarra1 (180);
        robo.acionarMotores (0,0);
        delay (1000);
    }
}
