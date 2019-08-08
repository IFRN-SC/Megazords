#include "Resgate.h"

Resgate::Resgate(){}

void Resgate::iniciar (){
    this -> entrarNaSala ();
    char zona = this -> identificaZona ();
    
    this -> restoDosCantos (zona); 
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
    delay (1000);
}



// método responsável por fazer o robô entrar na sala 3
// alinhando com a sala após ter entrado
void Resgate::entrarNaSala (){
    robo.acionarMotores (60,20);
    delay (550);
    robo.acionarMotores (-40,-40);
    delay (200);
    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores (40,-38);
        delay (50);
    }
    robo.acionarMotores (40,-40);
    delay (250);
    this -> alinhar ();
}


// metodo responsável por soltar a bolinha com os servos
// na areá que esta há frente do robô
void Resgate::soltarBolinha (){
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarServoGarra2 (60);
    robo.acionarMotores (0,0);
    delay (1000);
    robo.acionarServoGarra1 (5);
    delay (2000);  

    robo.acionarServoGarra2 (60,80,5);
    robo.acionarServoGarra2 (80,60,5);
    robo.acionarServoGarra2 (60,80,5);
    robo.acionarServoGarra2 (80,60,5);
    robo.acionarServoGarra2 (60,80,5);
    robo.acionarServoGarra2 (80,60,5);
    robo.acionarServoGarra2 (60,80,5);
    robo.acionarServoGarra2 (80,60,5);
    garra.fechar ();
    robo.acionarServoGarra2(60, 135, 5);
   
    robo.acionarMotores (0,0);
    delay (100);
    
}



// método responsável por verificar se a area de resgate
// com o sonar ESQ 
bool Resgate::verificarArea (){
    robo.acionarMotores (0,0);
    delay (100);
    return (robo.lerSensorSonarEsq() <= 15);
}



// nesse método iremos fazer com que o robô encontre a sala 
// onde deve ser deixado a bolinha
char Resgate::identificaZona (){
    robo.desligarTodosLeds();
    robo.acionarMotores (40,38);
    delay (100);
    robo.acionarMotores (-40,38);
    delay (500);
    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);
    
     // seguir um pouco 

    long ant2 = millis();
    int angInicial2 = 2;
    long t2 = (millis() -  ant2);
    int x2 = 800;
    while(t2 < x2){
      robo.acionarMotores(40, 38);     
      if(t2 > (x2-500)){
        robo.acionarServoGarra1(map(t2, 500, 800, 0, 70));  
      }
      t2 = (millis() -  ant2);
    }

    robo.acionarMotores (0,0);
    delay (100);
    
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (100);
    
    // o robô ira está lateralmente a area de resgate
    robo.acionarMotores (40,-38);
    delay (230);
    robo.acionarMotores (40,38);
    delay (900);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarServoGarra1 (55, 70, 10);

    // caso a zona esteja a frente da entrada da sala
    if (verificarArea()){
        for(int i = 0; i < 10; i++){  
            robo.ligarTodosLeds();
            delay(400);
            robo.desligarTodosLeds();
            delay(200);
        }

        robo.acionarMotores(-40,38);
        delay (520);
        robo.acionarMotores(40,38);
        delay (100);                

        // caso o robo esteja com a bolinha dentro da garra
        // ele ira ate a area de resgate usando o sonar
        if(robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
            robo.ligarLed (1);  

            robo.acionarMotores(40,38);
            delay (200);

            this -> soltarBolinha ();

            robo.acionarMotores(-40,-38);
            delay (100);
        }
        return 'a';
    }

    
    // caso não esteja vamos verificar o canto que não foi preenchido
    robo.acionarMotores (40,-38);
    delay (200);  
    robo.acionarMotores(0, 0); 
    delay(100); 
    this -> alinhar ();
   
    robo.acionarMotores(0, 0); 
    delay(100);
    robo.acionarMotores (40,38);
    delay (200);
    robo.acionarMotores (-40,38);
    delay (500); 
    robo.acionarMotores (0,0);
    delay (100);

    if (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2()){
        garra.baixar ();
        garra.abrir ();
        robo.acionarMotores (0,0);
        delay (100); 
    }
    else {
        garra.abrir ();
        garra.baixar ();
        robo.acionarMotores (0,0);
        delay (100);  
    }
    
    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 300;
    while(t < x){
        robo.acionarMotores(40, 38);     
        if(t > (x-150)){
            robo.acionarServoGarra1(map(t, 150, 300, 0, 70));  
         }
         t = (millis() -  ant);
    };

    robo.acionarMotores(0, 0); 
    delay(100);
    
    subir();
    
    robo.acionarMotores (40,38);
    delay (350);
    // vamos alinha e verificar a outra zona
    robo.acionarMotores (40,-38);
    delay (500);
    this -> alinhar ();
   
    // procurar zona e pegar as bolinhas
    garra.baixar ();
    garra.abrir ();
    robo.acionarMotores (0,0);
    delay (100);
    
    // seguir um pouco 
    
    long ant4 = millis();
    int angInicial4 = 2;
    long t4 = (millis() -  ant4);
    int x4 = 1200;
    while(t4 < x4){
      robo.acionarMotores(40, 38);     
      if(t4 > (x4-400)){
        robo.acionarServoGarra1(map(t4, 800, 1200, 0, 70));  
      }
      t4 = (millis() -  ant4);
    }
    
    robo.acionarMotores (0,0);
    delay (100);
    
    garra.subir (); 
    
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (40,-38);
    delay (200);
    robo.acionarMotores (40,38);
    delay (800);
    robo.acionarMotores (0,0);
    delay (100);

    robo.acionarServoGarra1 (50, 70, 30);

    // caso a zona esteja a frente da entrada da sala
    if (verificarArea()){
      
        for(int i = 0; i < 10; i++){  
        robo.ligarTodosLeds();
        delay(400);
        robo.desligarTodosLeds();
        delay(200);
        }

        robo.acionarMotores(-40,38);
        delay (550);
        robo.acionarMotores(40,38);
        delay (200);

        if(robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
            robo.ligarLed (2);

            robo.acionarMotores(40,38);
            delay (200);
            
            this -> soltarBolinha ();
        }
        return 'b';
    }else {
        robo.ligarLed (3);
    }

     // caso não esteja vamos verificar o canto que não foi preenchido
    robo.acionarMotores (40,-38);
    delay (250);
    robo.acionarMotores (0, 0);
    delay (100);    
    robo.acionarMotores (-40,-38);
    delay (400);
    robo.acionarMotores (0,0);
    delay (100);    
    this -> alinhar ();
    
    // vamos alinha e fazer a sala
    robo.acionarMotores (40,38);
    delay (200);
    robo.acionarMotores (-40,38);
    delay (510);
    robo.acionarMotores (-40,-38);
    delay (1000);
    this -> alinhar ();
    
    return 'c';
}


// construimos um método voltar para cada vez que 
// o robô estiver na area de resgate ele irá volta ao ponto 0 
void Resgate::voltar (char zona){
    if (zona == 'a' or zona == 'c'){
        robo.acionarMotores(-40,-38);
        delay (1100);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (150);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (500);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(-40,38);
        delay (550);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
    }
    else if (zona == 'b'){
        robo.acionarMotores(-40,-38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,38);
        delay (1000);
        robo.acionarMotores(0,0);
        delay (100);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (800);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (800);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (500);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (400);
        this -> alinhar();
    }
}

// método responsável por verificar a lateral
// se a bolinha estiver      
void Resgate::irLateralEsq (){
    robo.acionarMotores (43,38);
    delay (50);
    robo.acionarMotores (-40,38);
    delay (550);
    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);

    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 500;
    while(t < x){
        robo.acionarMotores(40, 38);     
        if(t > (x-200)){
            robo.acionarServoGarra1(map(t, 300, 500, 0, 70));  
         }
         t = (millis() -  ant);
    }

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
    delay (100);

    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 500;
    while(t < x){
        robo.acionarMotores(40, 38);     
        if(t > (x-200)){
            robo.acionarServoGarra1(map(t, 300, 500, 0, 70));  
         }
         t = (millis() -  ant);
    }

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
    robo.acionarMotores (40,38);
    delay (1200);

    if (zona == 'a' or zona == 'c'){
        robo.acionarMotores(40,-38);
        delay (450);    
        robo.acionarMotores (0,0);
        delay (100);   
    }
    else {
        robo.acionarMotores(-40,38);
        delay (450);    
        robo.acionarMotores (0,0);
        delay (100);   
    }

    this -> alinhar ();       
    robo.acionarMotores(40,38);
    delay (1300);
 

    if (zona == 'a' or zona == 'c'){     
        robo.acionarMotores(40,-38);
        delay (650);
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
        robo.acionarMotores(-40,38);
        delay (650);
        robo.acionarMotores(-40,-38);
        delay (500);

        this -> alinhar ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(40,-38);
        delay (1000);
       
        robo.acionarMotores(40,38);
        delay (200);
       
        this -> soltarBolinha ();
    }
}

// código para o resto da sala que sobrar durante a execução do robô
// na sala 3, onde preencherar os cantos 
void Resgate::restoDosCantos (char zona){
    if (zona != 'c'){
        
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (200);
        robo.acionarMotores(40,-38);
        delay (1000);
        robo.acionarMotores(0,0);
        delay (100);               
        this -> alinhar ();
        robo.acionarMotores(0,0);
        delay (100); 
        robo.acionarMotores(40,38);
        delay (750);               
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100); 
      
        this -> alinhar ();
        
        robo.acionarMotores(0,0);
        delay (100); 
        robo.acionarMotores(40,38);
        delay (200); 
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,38);
        delay (500);               
        robo.acionarMotores(0,0);
        delay (100);         
    }

    
    if (zona == 'a'){
        if (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2()){
            garra.baixar ();
            garra.abrir ();
            robo.acionarMotores (0,0);
            delay (100); 
        }
        else {
            garra.abrir ();
            garra.baixar ();
            robo.acionarMotores (0,0);
            delay (100);  
        }
      
        
        long ant = millis();
        int angInicial = 2;
        long t = (millis() -  ant);
        int x = 800;
        while(t < x){
            robo.acionarMotores(40, 38);     
            if(t > (x-500)){
                robo.acionarServoGarra1(map(t, 500, 800, 0, 70));  
             }
             t = (millis() -  ant);
        }
        
        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (400);               
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (480);               
        robo.acionarMotores(0,0);
        delay (100); 

        this -> alinhar ();
        
        robo.acionarMotores(0,0);
        delay (100); 


        // vamos tentar pegar a bolinha na segunda parte
        
        if (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2()){
            garra.baixar ();
            garra.abrir ();
            robo.acionarMotores (0,0);
            delay (100); 
        }
        else {
            garra.abrir ();
            garra.baixar ();
            robo.acionarMotores (0,0);
            delay (100);  
        }
        
        robo.acionarMotores (0,0);
        delay (100);
        
        ant = millis();
        angInicial = 2;
        t = (millis() -  ant);
        x = 1800;
        while(t < x){
          robo.acionarMotores(40, 38);     
          if(t > (x-400)){
            robo.acionarServoGarra1(map(t, 1400, 1800, 0, 70));  
          }
          t = (millis() -  ant);
        }

        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (200);               
        robo.acionarMotores (0,0);
        delay (100);

        robo.acionarMotores(40,-38);
        delay (470);               
        robo.acionarMotores(0,0);
        delay (100); 
        this -> alinhar ();
        robo.acionarMotores(0,0);
        delay (100); 
    }
    
    
    else if (zona == 'b'){
       
        if (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2()){
            garra.baixar ();
            garra.abrir ();
            robo.acionarMotores (0,0);
            delay (100); 
        }
        else {
            garra.abrir ();
            garra.baixar ();
            robo.acionarMotores (0,0);
            delay (100);  
        }
        
        long ant = millis();
        int angInicial = 2;
        long t = (millis() -  ant);
        int x = 700;
        while(t < x){
            robo.acionarMotores(40, 38);     
            if(t > (x-300)){
                robo.acionarServoGarra1(map(t, 400, 700, 0, 70));  
             }
             t = (millis() -  ant);
        }
        
        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (300);               
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (480);               
        robo.acionarMotores(0,0);
        delay (100); 

        this -> alinhar ();
        
        robo.acionarMotores(0,0);
        delay (100);
        
        if (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2()){
            garra.baixar ();
            garra.abrir ();
            robo.acionarMotores (0,0);
            delay (100); 
        }
        else {
            garra.abrir ();
            garra.baixar ();
            robo.acionarMotores (0,0);
            delay (100);  
        }
        
        ant = millis();
        angInicial = 2;
        t = (millis() -  ant);
        x = 1000;
        while(t < x){
          robo.acionarMotores(40, 38);     
          if(t > (x-300)){
            robo.acionarServoGarra1(map(t, 700, 1000, 0, 70));  
          }
          t = (millis() -  ant);
        }
        
        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (480);               
        robo.acionarMotores(0,0);
        delay (100); 

        this -> alinhar ();
        
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (200); 
        robo.acionarMotores(40,-38);
        delay (500);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (500);
        
        this -> alinhar ();
        
    }
}





// método responsável por preencher as paralelas sendo que um avez que encontre a bolinha, o mesmo irá 
// deixa-la e voltara ao ponto 0, caso não encontre ele irá para após ter feito a paralela 4 vezes
void Resgate::seguirNaSala (char zona){
    for (int i = 0; i <= 4; i++){

        robo.acionarServoGarra1 (55, 70, 10);
        
        if (i == 0 and (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2())){
                  this -> resgatarVitima (zona);
                  this -> voltar(zona);
                  i = 0;  
        }
        else {
            if (robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2()){
                garra.baixar ();
                garra.abrir ();
                robo.acionarMotores (0,0);
                delay (100); 
            }
            else {
                garra.abrir ();
                garra.baixar ();
                robo.acionarMotores (0,0);
                delay (100);  
            }
            if(i != 4){
                long ant = millis();
                int angInicial = 2;
                long t = (millis() -  ant);
                int x = 2000;
                while(t < x){
                  robo.acionarMotores(40, 38);     
                  if(t > (x-400)){
                    robo.acionarServoGarra1(map(t, 1600, 2000, 0, 70));  
                  }
                  t = (millis() -  ant);
                }
            }
            else{
                long ant = millis();
                int angInicial = 2;
                long t = (millis() -  ant);
                int x = 1500;
                while(t < x){
                  robo.acionarMotores(40, 38);     
                  if(t > (x-400)){
                    robo.acionarServoGarra1(map(t, 1100, 1500, 0, 70));  
                  }
                  t = (millis() -  ant);
                }  
            }
            robo.acionarMotores(0,0);
            delay (500);
            
            robo.acionarMotores(-40,-38);
            delay (2000);       
            this -> alinhar ();
    
            // iremos modificar isso  
            garra.subir();
            
            robo.acionarServoGarra1 (50, 70, 30);
    
            if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
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



          // lados que ele deve virar caso não encontre a bolinha
          
          else if (zona == 'a' or zona == 'c'){
              this-> irLateralDir ();   
                
              if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
                  for (int i = 0; i < 10; i++){  
                      robo.ligarTodosLeds();
                      delay(400);
                      robo.desligarTodosLeds();
                      delay(200);
                  }    
                   
                  this -> resgatarVitima (zona);
                  this -> voltar(zona);
                  i = 0;
              }
          }
          else {
              this-> irLateralEsq ();             
              if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
                  for (int i = 0; i < 10; i++){  
                      robo.ligarTodosLeds();
                      delay(400);
                      robo.desligarTodosLeds();
                      delay(200);
                  }    
                    
                  this -> resgatarVitima (zona);
                  this -> voltar(zona);
                  i = 0;
              }
          }
       }      // parentese do if
    }         // parentese do for
}      


