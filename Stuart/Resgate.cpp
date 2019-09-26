#include "Resgate.h"

Resgate::Resgate(){}

void Resgate::iniciar (){
    this -> entrarNaSala ();
    char areaResgate = this -> identificaZona ();
    pontoZero (areaResgate);

    // podemos varrer a sala 3 com a informação da area de resgate
}




/********************************     Métodos para os movimentos do robô    ***********************************/

// método responsável por fazer o robô voltar 
void Resgate::roboVoltar (int tempo){
    robo.acionarMotores (-40,-40);
    delay (tempo);
}

// método responsável por fazer o robô ir pra frente
void Resgate::roboFrente (int tempo){
    robo.acionarMotores (40,40);
    delay (tempo);    
}

// método responsável por fazer o robô ficar parado
void Resgate::roboParar (int tempo){
    robo.acionarMotores (0,0);
    delay (tempo);    
}

// método responsável por fazer o robô alinhar com a sala 3
void Resgate::alinhar (){
    this -> roboVoltar(1000);
    this -> roboFrente (200);
    this -> roboVoltar (1000);
    this -> roboFrente (150);
    this -> roboVoltar (1000);
    this -> roboParar (1000);
}



// método responsável por fazer o robô entrar corretamente na sala
void Resgate::entrarNaSala (){
    robo.acionarMotores (20,60);
    delay (550);
    roboVoltar (300);

    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores (-40,38);
        delay (50);
    }

    robo.acionarMotores (-40,40);
    delay (250);
    this -> alinhar ();
}

// método responsável por verificar se a area de resgate com o sonar ESQ 
bool Resgate::verificarArea (){
    this -> roboParar(100);
    return (robo.lerSensorSonarDir() <= 15);
}

// método responsável por fazer o robõ piscar os leds
void Resgate::sinalizar (int vezes){
    for (int i = 0; i < vezes; i++){  
        robo.ligarTodosLeds();
        delay(400);
        robo.desligarTodosLeds();
        delay(200);
    }
}
        
// método responsável por verificar onde esta a area de resgate
char Resgate::identificaZona(){
    robo.desligarTodosLeds();
    this -> roboFrente(200);
   
    robo.acionarMotores (40,-38); 
    delay (480);
   
    this -> roboParar (100);
    garra.abrir ();
    garra.baixar ();
    this -> roboParar (100);
    
    garra.fecharGarraMovimento(800, 500);
    this -> roboParar (100);
    garra.subir (); 
    this -> roboParar (100);
    

    // o robô ira está lateralmente a area de resgate
    robo.acionarMotores (-40,38);
    delay (220);
    this -> roboFrente(700);
    this -> roboParar (100);
    
    if (this -> verificarArea()){
        this -> sinalizar (3);   
        robo.ligarLed (1);  

        robo.acionarMotores(40,-38);
        delay (520);
        this -> roboFrente (100); 

        // caso o robo esteja com a bolinha dentro da garra
        // ele ira ate a area de resgate usando o sonar
        if(garra.pegouVitima()){
            this -> roboFrente (200); 
            this -> soltarBolinha ();
            this -> roboVoltar(100);
        }

        // vamos alinhar com a sala de resgate
        robo.acionarMotores(40,-38);
        delay (1000);
        this -> alinhar ();

        // retorna a posição A da area de resgate
        return 'a';
    }

    
    
    // caso não esteja vamos verificar o canto que não foi preenchido
    robo.acionarMotores (-40,38);
    delay (200);  
    this -> roboParar (100);
    this -> alinhar ();   
    this -> roboParar (100);
    this -> roboFrente (200);

    robo.acionarMotores (40,-38);
    delay (460); 

    this -> roboVoltar (200);
    this -> roboParar (100);

    // verificamos se tem boliha pra descer a garra
    garra.descerGarra (garra.pegouVitima ());
    garra.fecharGarraMovimento(500, 250);
 
    this -> roboParar(100);
    garra.subir ();
    
    this -> roboFrente (300);
    this -> roboParar(100);
    
    // vamos alinha e verificar a outra zona
    robo.acionarMotores (-40,38);
    delay (500);
    this -> alinhar ();
    
    this -> roboParar(100);
    garra.baixar ();
    garra.abrir ();
    this -> roboParar(100);
    
 
    // seguir um pouco até a possivel area B
    garra.fecharGarraMovimento(1200, 800);
    this -> roboParar(100);
    garra.subir ();
    this -> roboParar(100);
    
    robo.acionarMotores (-40,38);
    delay (180);
    
    // ir lateral com a area B
    this -> roboParar(100); 
    this -> roboFrente (700);
    this -> roboParar(100);
   

    // vamos verificar se a area de resgate é B
    if (this -> verificarArea()){
        this -> sinalizar (3);
        robo.ligarLed (2);

        robo.acionarMotores(40,-38);
        delay (500);

        this -> roboFrente (100);

        if (garra.pegouVitima()){
            this -> roboFrente (200); 
            this -> soltarBolinha ();
            this -> roboVoltar(100);
        }

        // vamos alinhar com a sala de resgate
        robo.acionarMotores(40,-38);
        delay (1000);
        this -> alinhar ();


        
        // retorna a posição B da area de resgate
        return 'b';

    }else {
        robo.ligarLed (3);
    }


    // caso não esteja vamos verificar o canto que não foi preenchido
    robo.acionarMotores (-40,38);
    delay (200);  
    this -> roboParar (100);
    this -> alinhar ();   
    this -> roboParar (100);
    this -> roboFrente (200);

    robo.acionarMotores (40,-38);
    delay (460); 

    this -> roboVoltar (200);
    this -> roboParar (100);

    // verificamos se tem boliha pra descer a garra
    garra.descerGarra (garra.pegouVitima ());
    garra.fecharGarraMovimento(500, 250);
 
    this -> roboParar(100);
    garra.subir ();
    
    this -> roboFrente (300);
    this -> roboParar(100);
    
    // vamos alinha e verificar a outra zona
    robo.acionarMotores (-40,38);
    delay (500);
    this -> alinhar ();
    
    this -> roboParar(100);
    garra.baixar ();
    garra.abrir ();
    this -> roboParar(100);

  
    // retorna a posição C da area de resgate
    return 'c';
}

// método responsável por fazer o robô a voltar ao ponto zero da area de resgate
void Resgate::pontoZero (char zona){
  
    // caso a zona seja A ou B, a volta para o ponto zero são quase identicas
    if (zona == 'a' or zona == 'b'){

        this -> roboFrente (1300);
        this -> roboParar (1000);

        // caso seja A vamos girar para a direita
        // caso seja B vamos girar para a esquerda
        if (zona == 'a'){
            robo.acionarMotores(40,-38);
            delay (250);
        }
        else {  
            robo.acionarMotores(-40,38);
            delay (250);
        }

        this -> roboParar (1000);
        this -> alinhar();
        this -> roboFrente (200);

        robo.acionarMotores(-40,38);
        delay (480);

        this -> roboParar (1000);
        this -> roboFrente (800);

        robo.acionarMotores(40,-38);
        delay (480);
        this -> alinhar();

        // verificamos se tem boliha pra descer a garra
        garra.descerGarra (garra.pegouVitima ());
        garra.fecharGarraMovimento(500, 250);

        this -> roboParar(100);
        garra.subir ();

        this -> roboFrente (300);
        this -> roboParar(100);

        // vamos da um giro de 180 pós o rogô esta de frente a area C
        if (zona == 'a'){
            robo.acionarMotores(40,-38);
            delay (1000);
        }
        // vamos da apenas um giro de 90 para o robô alinhar com a entrada 
        else {
            robo.acionarMotores(40,-38);
            delay (480);
        }

        this -> alinhar ();
    }   

    // caso a are seja C, apenas faremos o robô voltar de ré
    // ate a posição vazia de A  
    else {
        this -> roboFrente (200);
        this -> roboParar (100);

        robo.acionarMotores(40,-38);
        delay (480);
   
        this -> roboVoltar (1000);
        this -> alinhar ();
    }
}

/*
void Resgate::iniciar (){        
      this -> entrarNaSala();
      char zona = this -> identificaZona();
      
      this -> restoDosCantos(zona); 
      this -> seguirNaSala(zona);
}



/*


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
*/
