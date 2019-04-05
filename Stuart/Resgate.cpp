#include "Resgate.h"

Resgate::Resgate(){
}


void Resgate::iniciar (){
    this -> entrarNaSala(); 
    this -> zona = this -> indentificaZona();
    this -> seguirNaSala();                    
}


// construimos um método responsável por alinha o robô
// com a parede atrás dele, dessa forma reduzimos a força dos motores
// e aumentamos a práticidade com que ele alinha com a parede 

void Resgate::alinharRobo (){
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (200);
    robo.acionarMotores(-40,-40);
    delay (700);
    robo.acionarMotores(40,40);
    delay (150);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(0,0);
    delay (2000);
}


// faz com que o robô entre na sala de forma paralela
// assim facilitara o seu alinhamento com a parede

void Resgate::entrarNaSala (){
    robo.acionarMotores(60,20);
    delay (520);

    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores(40,-40);
        delay (50);
    }

    robo.acionarMotores(40,-40);
    delay (280);
    robo.acionarMotores(0,0);
    delay (1000);
    this -> alinharRobo ();
}


// estamos fazendo testes apenas com a sala de resgate 
// na posição direita e em seguida criaremos uma maneira 
// de indentificar onde a zona está

char Resgate::indentificaZona (){
    robo.desligarTodosLeds();
    robo.ligarLed(2);
    return 'c'; 
}


// nesse método iremos fazer com que o robô chece a sua lateral
// ja que pode haver uma possibilidade que a bolinha esteja em sua lateral
// ou ate mesmo o robô empura-la

void Resgate::seguirLateral() {
    robo.acionarMotores(-40,40);
    delay (550);

    garra.abrir ();    
    robo.acionarMotores(0,0);
    delay (1000);
    garra.baixar ();
   
    robo.acionarMotores(40,40);
    delay (500);
    robo.acionarMotores (0,0);
    delay (1000);
   
    garra.fechar ();
    robo.acionarMotores (0,0);
    delay (1000);
    
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (1000);
   
    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores(40,-40);
        delay (50);
    }

    robo.acionarMotores(40,-40);
    delay (280);
}


// esse método permite que o robô vá até o fim da sala com a garra aberta
// depois ele fecha a garra e trás tudo com sigo, permitindo que a bolinha támbem venha
// depois ele checa se a bolinha está em sua frente.

void Resgate::seguirNaSala (){

    for (int i = 0; i < 3; i++){
        garra.baixar();
        garra.abrir();
        
        robo.acionarMotores (0,0);
        delay (1000);
        robo.acionarMotores (40,38);
        delay (2200);
        garra.fechar();
        robo.acionarMotores (0,0);
        delay (1000);
        robo.acionarMotores (-40,-38);
        delay (2000);

        this -> alinharRobo ();

        // soltar a bolinha devagar 
        robo.acionarServoGarra1 (90,170, 40);
        garra.subir();
        robo.acionarMotores (0,0);
        delay(2000);


	    	// verificar com o sonar se a bolinha está em sua frente
        // caso esteja o robô ira alertar com os leds, e em segida vai deixar na area
        // caso não veja a bolinha, o robô irá checar as laterais

        if (robo.lerSensorSonarFrontal () <= 25){
            for(int i = 0; i < 10; i++){  
                robo.ligarTodosLeds();
                delay(400);
                robo.desligarTodosLeds();
                delay(200);
            }

            // deixar bolinha na area de resate 
            this -> areaResgate ();
             
            // começar novamente 
            seguirNaSala ();
          
        } else {
            this -> seguirLateral();      
            this -> alinharRobo ();
        }
    }
}


// método responsável por deixar a bolinha na determinada zona de resgate
// ao passarmos um char ('a'/'b'/'c') iremos ter noção de qual area vai se tratar 
// logo após a entrega da bolinha, o nosso robô deve voltar para o lugar de origem

void Resgate::areaResgate (){
    // primeiramente vamos pegar a bolinha que está a frente do robô
    // depois vamos alinha com a parede à esquerda da sala 
  
    robo.acionarServoGarra2 (0);
    delay (1000);       
    robo.acionarServoGarra1 (180);
    delay (1000);       
    robo.acionarServoGarra1 (90);
    delay (1000);       
    robo.acionarServoGarra2 (100);
    delay (1000);       

    robo.acionarMotores (40,38);
    delay (1200);
    robo.acionarMotores(-40,40);
    delay (550);
    this -> alinharRobo ();      
          
    // seguir ate ver a parede
    robo.acionarMotores (40,38);
    delay (1800);

        
    if (zona == 'a'){     
        robo.acionarMotores(-40,40);
        delay (225);
        robo.acionarMotores (-40,-38);
        delay (500);
        this -> alinharRobo ();      


        // giro para ficar de frente com a sala
        robo.acionarMotores(-40,40);
        delay (1100);
        robo.acionarMotores (40,38);
        delay (150);

        // soltar bolinha na area 
        robo.acionarServoGarra2 (30);
        delay (1000);
        robo.acionarServoGarra1 (180);
        delay (2000); 

        // regular servos
        garra.subir ();
        garra.fechar ();    

        robo.acionarMotores(0,0);
        delay (1000);
        robo.acionarMotores(40,-40);
        delay (225);
        robo.acionarMotores(-40,-38);
        delay (800);
        this -> alinharRobo ();
    }   
    

    else if (zona == 'b'){
        robo.acionarMotores(40,-40);
        delay (775);
        robo.acionarMotores (-40,-38);
        delay (500);
        this -> alinharRobo ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(-40,40);
        delay (1100);
        robo.acionarMotores (40,38);
        delay (150);

        // soltar bolinha na area 
        robo.acionarServoGarra2 (30);
        delay (1000);
        robo.acionarServoGarra1 (180);
        delay (2000);

        // regular servos
        garra.subir ();
        garra.fechar ();

        robo.acionarMotores(-40,-40);
        delay (800);

        robo.acionarMotores(40,-40);
        delay (200);
        robo.acionarMotores (-40,-38);
        delay (2000);

        this -> alinharRobo ();

        robo.acionarMotores(40,40);
        delay (150);
        robo.acionarMotores(40,-40);
        delay (550);
        robo.acionarMotores (-40,-38);
        delay (1000);
        this -> alinharRobo ();
    }
    
    else {
        robo.acionarMotores(-40,40);
        delay (775);
        robo.acionarMotores (-40,-38);
        delay (500);
        this -> alinharRobo ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(-40,40);
        delay (1100);
        robo.acionarMotores (40,38);
        delay (150);

        // soltar bolinha na area 
        robo.acionarServoGarra2 (30);
        delay (1000);
        robo.acionarServoGarra1 (180);
        delay (2000);

        // regular servos
        garra.subir ();
        garra.fechar ();

        robo.acionarMotores(-40,-40);
        delay (400);
    
        robo.acionarMotores(-40,40);
        delay (250);
        robo.acionarMotores (-40,-38);
        delay (2000);

        this -> alinharRobo ();
        robo.acionarMotores(40,40);
        delay (150);
        robo.acionarMotores(40,-40);
        delay (550);
        robo.acionarMotores (-40,-38);
        delay (800);
        this -> alinharRobo ();
    }
}
