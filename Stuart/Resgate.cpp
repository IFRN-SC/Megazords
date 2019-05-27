#include "Resgate.h"

Resgate::Resgate(){}

void Resgate::iniciar (){
    this -> entrarNaSala ();
    char zona = this -> identificaZona ();
    if (zona != 'c'){
        this -> voltar (zona);
    }
    this -> seguirNaSala (zona);
}

// método responsável por fazer o robô alinhar
void Resgate::alinhar (){
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



// método responsável por fazer o robô entrar na sala 3
// alinhando com a sala após ter entrado
void Resgate::entrarNaSala (){
    robo.acionarMotores (60,20);
    delay (520);
    robo.acionarMotores (-40,-40);
    delay (200);
    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores (40,-38);
        delay (50);
    }
    robo.acionarMotores (40,-38);
    delay (280);
    this -> alinhar ();
}



// metodo responsável por soltar a bolinha com os servos
// na areá que esta há frente do robô
void Resgate::soltarBolinha (){
    robo.acionarMotores (0,0);
    delay (3000);
    robo.acionarServoGarra2 (60);
    delay (1000);
    robo.acionarServoGarra1 (5);
    delay (2000);  
    garra.subir ();
    garra.fechar ();
    robo.acionarMotores (0,0);
    delay (500);
    robo.acionarMotores(-40,-38);
    delay (800);
}



// método responsável por verificar se a area de resgate
// com o sonar ESQ 
bool Resgate::verificarArea (){
    robo.acionarMotores (0,0);
    delay (500);
    return (robo.lerSensorSonarEsq() <= 20);
}



// nesse método iremos fazer com que o robô encontre a sala 
// onde deve ser deixado a bolinha
char Resgate::identificaZona (){
    robo.desligarTodosLeds();
    robo.acionarMotores (-40,38);
    delay (550);
    robo.acionarMotores (0,0);
    delay (100);
    garra.baixar ();
    garra.abrir ();
    robo.acionarMotores (0,0);
    delay (100);
    
     // seguir um pouco 
    robo.acionarMotores (40,38);
    delay (1100);
    robo.acionarMotores (0,0);
    delay (500);
    
    garra.fechar ();
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (2000);
    
    // o robô ira está lateralmente a area de resgate
    robo.acionarMotores (40,-38);
    delay (230);
    robo.acionarMotores (40,38);
    delay (1000);
    robo.acionarMotores (0,0);
    delay (3000);

    // caso a zona esteja a frente da entrada da sala
    if (verificarArea()){
        for(int i = 0; i < 10; i++){  
            robo.ligarTodosLeds();
            delay(400);
            robo.desligarTodosLeds();
            delay(200);
        }
        robo.ligarLed (1);
        robo.acionarMotores(-40,38);
        delay (550);
        robo.acionarMotores(40,38);
        delay (200);  
        this -> soltarBolinha ();
        return 'a';
    }

    
    // caso não esteja vamos verificar o canto que não foi preenchido
    robo.acionarMotores (-40,-38);
    delay (900);    
    robo.acionarMotores (-40,38);
    delay (230);
    robo.acionarMotores (0,0);
    delay (1000);    
    garra.baixar ();
    garra.abrir ();
    robo.acionarMotores (0,0);
    delay (1000);    
    robo.acionarMotores (40,38);
    delay (800);
    robo.acionarMotores (0,0);
    delay (500);
    garra.fechar ();
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (2000);
    robo.acionarMotores (40,38);
    delay (300);




    // vamos alinha e verificar a outra zona
    robo.acionarMotores (40,-38);
    delay (550);
    this -> alinhar ();
   
    // procurar zona e pegar as bolinhas
    garra.baixar ();
    garra.abrir ();
    robo.acionarMotores (0,0);
    delay (1000);
    
    // seguir um pouco 
    robo.acionarMotores (40,38);
    delay (1200);
    robo.acionarMotores (0,0);
    delay (1000);
    garra.fechar ();
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (2000);
    robo.acionarMotores (40,-38);
    delay (230);
    robo.acionarMotores (40,38);
    delay (900);
    robo.acionarMotores (0,0);
    delay (1000);

    for(int i = 0; i < 10; i++){  
        robo.ligarTodosLeds();
        delay(400);
        robo.desligarTodosLeds();
        delay(200);
    }

    // caso a zona esteja a frente da entrada da sala
    if (verificarArea()){
        robo.ligarLed (2);
        robo.acionarMotores(-40,38);
        delay (550);
        robo.acionarMotores(40,38);
        delay (200);
        
        this -> soltarBolinha ();
        return 'b';
    }else {
        robo.ligarLed (3);
    }

     // caso não esteja vamos verificar o canto que não foi preenchido
    robo.acionarMotores (-40,-38);
    delay (900);    
    robo.acionarMotores (-40,38);
    delay (230);
    robo.acionarMotores (0,0);
    delay (1000);    

    // vamos alinha e fazer a sala
    robo.acionarMotores (40,38);
    delay (1000);
    this -> alinhar ();
    return 'c';
}


// construimos um método voltar para cada vez que 
// o robô estiver na area de resgate ele irá volta ao ponto 0 
void Resgate::voltar (char zona){
    if (zona == 'a'){
        robo.acionarMotores(40,-38);
        delay (225);
        robo.acionarMotores(-40,-38);
        delay (2000);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (550);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
    }
    else if (zona == 'b'){
        robo.acionarMotores(-40,38);
        delay (225);
        robo.acionarMotores(-40,-38);
        delay (2000);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (550);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
    }
    else if (zona == 'c'){
        robo.acionarMotores(40,-38);
        delay (225);
        robo.acionarMotores(-40,-38);
        delay (2000);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (100);
        robo.acionarMotores(-40,38);
        delay (550);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
    }
}

// método responsável por verificar a lateral
// se a bolinha estiver      
void Resgate::irLateralEsq (){
    robo.acionarMotores (40,38);
    delay (50);
    robo.acionarMotores (-40,38);
    delay (550);
    robo.acionarMotores (0,0);
    delay (1000);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (1000);
    robo.acionarMotores (40,38);
    delay (600);
    robo.acionarMotores (0,0);
    delay (1000);   
    garra.fechar ();
    robo.acionarMotores (0,0);
    delay (100);
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (100);   
    robo.acionarMotores (40,-38);
    delay (550);
    robo.acionarMotores (0,0);
    delay (1000);
    this -> alinhar ();       
}

// método responsável por verificar a lateral
// se a bolinha estiver
void Resgate::irLateralDir (){
    robo.acionarMotores (40,38);
    delay (50);
    robo.acionarMotores (40,-38);
    delay (550);
    robo.acionarMotores (0,0);
    delay (1000);
   
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (1000);

    robo.acionarMotores (40,38);
    delay (600);
    robo.acionarMotores (0,0);
    delay (1000);   
    garra.fechar ();
    robo.acionarMotores (0,0);
    delay (100);
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (100);  
    robo.acionarMotores (-40,38);
    delay (550);
    robo.acionarMotores (0,0);
    delay (1000);
    this -> alinhar ();       
}


// método responsável por pegar a bolinha e deixa-la
// na determinada zona
void Resgate::resgatarVitima (char zona){ 
    //iremos aperfeiçoar isso ainda pois temos outra garra agr

    robo.acionarServoGarra2 (12);
    delay (1000);
    robo.acionarServoGarra1 (5);
    delay (1000);
    garra.fechar ();
    delay (1000);
    robo.acionarServoGarra2 (100);
    delay (1000);

    robo.acionarMotores (40,38);
    delay (1200);

    if (zona == 'c'){
        robo.acionarMotores(40,-38);
        delay (550);    
        robo.acionarMotores (0,0);
        delay (4000);   
    }else {
        robo.acionarMotores(-40,38);
        delay (550);    
        robo.acionarMotores (0,0);
        delay (4000);   
    }

    this -> alinhar ();       
    robo.acionarMotores(40,38);
    delay (1600);
 


    if (zona == 'a'){     
        robo.acionarMotores(40,-38);
        delay (775);
        robo.acionarMotores(-40,-38);
        delay (700);
        this -> alinhar ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(40,-38);
        delay (1100);
        robo.acionarMotores(40,38);
        delay (200);
        this -> soltarBolinha ();

    }   
    
    else if (zona == 'b'){
        robo.acionarMotores(-40,38);
        delay (775);
        robo.acionarMotores(-40,-38);
        delay (700);
        this -> alinhar ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(40,-38);
        delay (1100);
        robo.acionarMotores(40,38);
        delay (200);
        this -> soltarBolinha ();
    }
    
    else {
        robo.acionarMotores(40,-38);
        delay (775);
        robo.acionarMotores(-40,-38);
        delay (700);
        this -> alinhar ();      

        // giro para ficar de frente com a sala
        robo.acionarMotores(40,-38);
        delay (1100);
        robo.acionarMotores(40,38);
        delay (200);
        this -> soltarBolinha ();
    }
}




// método responsável por preencher as paralelas sendo que um avez que encontre a bolinha, o mesmo irá 
// deixa-la e voltara ao ponto 0, caso não encontre ele irá para após ter feito a paralela 4 vezes
void Resgate::seguirNaSala (char zona){
    for (int i = 0; i < 4; i++){
      
        garra.baixar();
        garra.abrir();
        
        long ant = millis();
        int angInicial = 2;
        long t = (millis() -  ant);
        int x = 2100;
        while(t < x){
          robo.acionarMotores(40, 38);     
          if(t > (x-800)){
            robo.acionarServoGarra1(map(t, 1300, 2100, 0, 55));  
          }
          t = (millis() -  ant);
        }
        robo.acionarMotores(0,0);
        delay (500);
        
        robo.acionarMotores(-40,-38);
        delay (2000);       
        this -> alinhar ();

        // iremos modificar isso  
        robo.acionarServoGarra1 (5, 55, 40);
        garra.subir();
        delay(2000);


        if (robo.lerSensorSonarFrontal() <= 20){
            for(int i = 0; i < 10; i++){  
                robo.ligarTodosLeds();
                delay(400);
                robo.desligarTodosLeds();
                delay(200);
            }    
            
            this -> resgatarVitima (zona);
            this -> voltar(zona);
            i = 0;
        }
        else if (zona == 'a' or zona == 'b'){
            this-> irLateralEsq ();   
        }else {
            this-> irLateralDir ();
        }
    }
    robo.acionarMotores (0,0);
    delay (60000);
}      
