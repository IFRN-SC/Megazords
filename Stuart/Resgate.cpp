#include "Resgate.h"

Resgate::Resgate(){}

void Resgate::iniciar (){        
      this -> entrarNaSala();
      char zona = this -> identificaZona();
      
      this -> restoDosCantos(zona); 
      this -> seguirNaSala(zona);
}

// método responsável por fazer o robô alinhar
void Resgate::alinhar (){
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (200);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (150);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(0,0);
    delay (1000);
}



// método responsável por fazer o robô entrar na sala 3
// alinhando com a sala após ter entrado
void Resgate::entrarNaSala(){
    robo.acionarMotores (20,60);
    delay (550);
    robo.acionarMotores (-40,-40);
    delay (200);
    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores (-40,38);
        delay (50);
    }
    robo.acionarMotores (-40,40);
    delay (250);
    this -> alinhar ();
}


// metodo responsável por soltar a bolinha com os servos
// na areá que esta há frente do robô
void Resgate::soltarBolinha (){
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarServoGarra2 (50);
    robo.acionarMotores (0,0);
    delay (500);
    robo.acionarServoGarra1 (5);
    delay (500);  

    robo.acionarServoGarra2 (50,70,5);
    robo.acionarServoGarra2 (70,50,5);
    robo.acionarServoGarra2 (50,70,5);
    robo.acionarServoGarra2 (70,50,5);
    robo.acionarServoGarra2 (50,70,5);
    robo.acionarServoGarra2 (70,50,5);
    robo.acionarServoGarra2 (50,70,5);
    robo.acionarServoGarra2 (70,50,5);
    garra.fechar ();
    robo.acionarServoGarra2(50, 115, 5);
   
    robo.acionarMotores (0,0);
    delay (100);
    
}



// método responsável por verificar se a area de resgate
// com o sonar ESQ 
bool Resgate::verificarArea (){
    robo.acionarMotores (0,0);
    delay (100);
    return (robo.lerSensorSonarDir() <= 15);
}



// nesse método iremos fazer com que o robô encontre a sala 
// onde deve ser deixado a bolinha
char Resgate::identificaZona(){
    robo.desligarTodosLeds();
    robo.acionarMotores (40,38);
    delay (200);
    robo.acionarMotores (40,-38); 
    delay (480);
    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);
    
     // seguir um pouco 

    fecharGarraMovimento(800, 500);

    robo.acionarMotores (0,0);
    delay (100);
    
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (100);
    
    // o robô ira está lateralmente a area de resgate
    robo.acionarMotores (-40,38);
    delay (220);
    robo.acionarMotores (40,38);
    delay (700);
    robo.acionarMotores (0,0);
    delay (100);

    // caso a zona esteja a frente da entrada da sala
    if (verificarArea()){
        for(int i = 0; i < 5; i++){  
            robo.ligarTodosLeds();
            delay(400);
            robo.desligarTodosLeds();
            delay(200);
        }

        robo.acionarMotores(40,-38);
        delay (520);
        robo.acionarMotores(40,38);
        delay (100);                

        // caso o robo esteja com a bolinha dentro da garra
        // ele ira ate a area de resgate usando o sonar
        if(garra.pegouVitima()){
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
    robo.acionarMotores (-40,38);
    delay (200);  
    robo.acionarMotores(0, 0); 
    delay(100); 
    this -> alinhar ();
   
    robo.acionarMotores(0, 0); 
    delay(100);
    robo.acionarMotores (40,38);
    delay (200);
    robo.acionarMotores (40,-38);
    delay (460); 
    robo.acionarMotores (-40,-38);
    delay (200);
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
    
    fecharGarraMovimento(500, 250);

    robo.acionarMotores(0, 0); 
    delay(100);
    
    subir();
    
    robo.acionarMotores (40,38);
    delay (300);
    robo.acionarMotores(0, 0); 
    delay(100);
    // vamos alinha e verificar a outra zona
    robo.acionarMotores (-40,38);
    delay (500);
    this -> alinhar ();
   
    // procurar zona e pegar as bolinhas
    garra.baixar ();
    garra.abrir ();
    robo.acionarMotores (0,0);
    delay (100);
    
    // seguir um pouco 
    
    fecharGarraMovimento(1200, 800);
    
    robo.acionarMotores (0,0);
    delay (100);
    
    garra.subir (); 
    
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (-40,38);
    delay (180);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (40,38);
    delay (700);
    robo.acionarMotores (0,0);
    delay (100);

    robo.acionarServoGarra1 (65, 83, 10);

    // caso a zona esteja a frente da entrada da sala
    if (verificarArea()){
      
        for(int i = 0; i < 10; i++){  
        robo.ligarTodosLeds();
        delay(400);
        robo.desligarTodosLeds();
        delay(200);
        }

        robo.acionarMotores(40,-38);
        delay (500);
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
    robo.acionarMotores (-40,38);
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
    robo.acionarMotores (40,-38);
    delay (450);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (-40,-38);
    delay (400);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (-40,38);
    delay (400);
    this -> alinhar ();
    robo.acionarMotores (40,38);
    delay (200);
    robo.acionarMotores (40,-38);
    delay (450);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (-40,-38);
    delay (400);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (-40,38);
    delay (400);
    this -> alinhar ();
    
    return 'c';
}

// construimos um método voltar para cada vez que 
// o robô estiver na area de resgate ele irá volta ao ponto 0 
void Resgate::voltar (char zona){
    if (zona == 'a' or zona == 'c'){
        robo.acionarMotores(-40,-38);
        delay (1300);
        robo.acionarMotores(0,0);
        delay (1000);
        robo.acionarMotores(-40,38);
        delay (250);
        robo.acionarMotores(0,0);
        delay (1000);
        robo.acionarMotores(-40,-38);
        delay (500);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(40,-38);
        delay (480);
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
        delay (500);
        robo.acionarMotores(-40,38);
        delay (650);
        robo.acionarMotores(0,0);
        delay (500);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,38);
        delay (450);
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
    robo.acionarMotores (40,38);
    delay (120);
    robo.acionarMotores (-40,38);
    delay (480);
    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);

    fecharGarraMovimento(450, 250);

    robo.acionarMotores (0,0);
    delay (100);   
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (100);   
    robo.acionarMotores (40,-38);
    delay (480);
    robo.acionarMotores (0,0);
    delay (1000);
    this -> alinhar ();       
}

// método responsável por verificar a lateral
// se a bolinha estiver
void Resgate::irLateralDir (){
    robo.acionarMotores (40,38);
    delay (120);
    robo.acionarMotores (40,-38);
    delay (480);
    robo.acionarMotores (0,0);
    delay (100);
   
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);

    fecharGarraMovimento(450, 250);

    robo.acionarMotores (0,0);
    delay (100);
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (100);  
    robo.acionarMotores (-40,38);
    delay (480);
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
        robo.acionarMotores(-40,38);
        delay (450);    
        robo.acionarMotores (0,0);
        delay (100);   
    }
    else {
        robo.acionarMotores(40,-38);
        delay (450);    
        robo.acionarMotores (0,0);
        delay (100);   
    }
    robo.acionarMotores(-40,-38);
    delay (800);    
    this -> alinhar ();       
    robo.acionarMotores(40,38);
    delay (1300);
    robo.acionarMotores (0,0);
    delay (100);

    if (zona == 'a' or zona == 'c'){     
        robo.acionarMotores(-40,38);
        delay (630);
        robo.acionarMotores(-40,-38);
        delay (700);
        this -> alinhar ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (880);
        
        robo.acionarMotores(40,38);
        delay (200);
        
       
        this -> soltarBolinha ();
    }
    
    
    else {
        robo.acionarMotores(40,-38);
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
        delay (800);
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
        delay (250);
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
        delay (480);               
        robo.acionarMotores(0,0);
        delay (100);         
    }

    
    if (zona == 'a'){
        
        robo.acionarMotores(40,38);
        delay (1000);               
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (480);               
        robo.acionarMotores(0,0);
        delay (100); 

        this -> alinhar ();
        
        robo.acionarMotores(0,0);
        delay (100); 

        garra.descerGarra(garra.pegouVitima());
        
        fecharGarraMovimento(1900, 1500);
        
        robo.acionarMotores(0,0);
        delay (100);

        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        
        robo.acionarMotores(40,-30);
        delay(900);

        robo.acionarMotores (0,0);
        delay (100);
        
        this -> alinhar ();
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
        
        fecharGarraMovimento(700, 400);
        
        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (270);               
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(-40,38);
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
        
        fecharGarraMovimento(1000, 700);
        
        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(-40,38);
        delay (480);               
        robo.acionarMotores(0,0);
        delay (100); 

        this -> alinhar ();
        
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (200); 
        robo.acionarMotores(-40,38);
        delay (480);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (500);
        
        this -> alinhar ();
        
    }
}

void Resgate::voltarZero(char zona){ 
  for (int j = 0; j < 5; j++){  
         robo.ligarTodosLeds();
         delay(400);
         robo.desligarTodosLeds();
         delay(200);
     }    
    
    
    robo.acionarMotores (44,40);
    delay (200);


    if (zona == 'a' or zona == 'c'){
        robo.acionarMotores (44,-40);
        delay (480);  
    }
    else {
        // caso zona a (viro para a esquerda)
        robo.acionarMotores (-44,40);
        delay (480);
            
    } 

    // ele não vai alinhar com a saida da sala
    if (zona != 'c'){
        this -> alinhar ();
    }
    
    // vamos baixar a garra e seguir pegando a bola
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);  


    fecharGarraMovimento(1900, 1500);
  
  
    if (zona == 'a' or zona == 'c'){
        robo.acionarMotores (-44,40);
        delay (480);  
    }
    else {
        // caso zona a (viro para a esquerda)
        robo.acionarMotores (44,-40);
        delay (480);
            
    } 

    // ele vai alinhar em todos os caso
    this -> alinhar ();    
  
}
// método responsável por preencher as paralelas sendo que um avez que encontre a bolinha, o mesmo irá 
// deixa-la e voltara ao ponto 0, caso não encontre ele irá para após ter feito a paralela 4 vezes
void Resgate::seguirNaSala (char zona){
    while(1){
        bool salvouVitima=false;
        
        for (int i = 0; i <= 3; i++){
          if(salvouVitima){
            i=0;
            salvouVitima=false;
          }
    
            robo.acionarServoGarra1 (65, 83, 10);
            
            if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
                    for(int j = 0; j < 10; j++){  
                      robo.ligarTodosLeds();
                      delay(400);
                      robo.desligarTodosLeds();
                      delay(200);
                    }  
                    this -> resgatarVitima (zona);
                    this -> voltar(zona); 
                    salvouVitima=true;
            }  
            else{        
             garra.abrir ();
             garra.baixar ();
             robo.acionarMotores (0,0);
             delay (100);  
            }  
                      
            if(i != 3){
               fecharGarraMovimento(1900, 1500);
            }
            else if(i == 3){
                fecharGarraMovimento(1400, 1000);
            }   
            robo.acionarMotores(0,0);
            delay (500);
                
            robo.acionarMotores(-40,-38);
            delay (2000);       
            this -> alinhar ();
        
            // iremos modificar isso  
            garra.subir();
                
            robo.acionarServoGarra1 (65, 83, 10);
        
            if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
                for(int j = 0; j < 10; j++){  
                    robo.ligarTodosLeds();
                    delay(400);
                    robo.desligarTodosLeds();
                    delay(200);
                }    
                    
                this -> resgatarVitima (zona);
                this -> voltar(zona);
                salvouVitima=true;
            }
              // lados que ele deve virar caso não encontre a bolinha
              
           else if (zona == 'a' or zona == 'c'){
               this-> irLateralEsq ();   
               robo.acionarServoGarra1 (65, 83, 10);  
               if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
                 for (int j = 0; j < 10; j++){  
                      robo.ligarTodosLeds();
                      delay(400);
                      robo.desligarTodosLeds();
                      delay(200);
                 }    
                       
                 this -> resgatarVitima (zona);
                 this -> voltar(zona);
                 salvouVitima=true;
               }
           }
           else {
               this-> irLateralDir();             
               if (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2()){
               robo.acionarServoGarra1 (65, 83, 10);
                 for (int j = 0; j < 10; j++){  
                     robo.ligarTodosLeds();
                     delay(400);
                     robo.desligarTodosLeds();
                     delay(200);
                 }    
                        
                 this -> resgatarVitima (zona);
                 this -> voltar(zona);
                 salvouVitima=true;
               }
           }
        }

        voltarZero(zona);
          
    }              
}      
