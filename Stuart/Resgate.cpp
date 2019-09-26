#include "Resgate.h"

Resgate::Resgate(){
    // USO DOS CARACTERES 
    // A: ZONA DIREITA
    // B: ZONA ESQUERDA
    // C: ZONA ESQUINA
    // Y: LADO DIREITO
    // Z: LADO ESQUERDO (OBR) 
}

void Resgate::iniciar (){
    char zona, area;
    area = this -> entrar ();                 // vamos entrar corretamente na sala 3

    zona = identificarZona (area);            // examina a sala a procura da area de resgate

    this -> restoDosCantos (zona, area);      // varre os cantos até chegar na posição 0
    this -> varrerSala (zona, area);          // varre a sala em vertical com a area de resgate 
    
}

// método responsável por soltar a bolinha na area de resgate
// e iremos balançar a mesma ate a bolinha cair 
void Resgate::soltarBolinha (){
    /*robo.acionarMotores (0,0);
    delay (100);
    robo.acionarServoGarra2 (50);
    robo.acionarMotores (0,0);
    delay (300);
    robo.acionarServoGarra1 (5);
    delay (300);  

    robo.acionarServoGarra2 (50,70,5);
    robo.acionarServoGarra2 (70,50,5);
    robo.acionarServoGarra2 (50,70,5);
    robo.acionarServoGarra2 (70,50,5);
    garra.fechar ();
    robo.acionarServoGarra2(50, 135, 5);
   */
    robo.acionarMotores (0,0);
    delay (200);
    robo.acionarServoGarra2 (50);
    robo.acionarServoGarra1 (25);
    delay (500);
    garra.fechar ();
    robo.acionarServoGarra2(20, 115, 5);
    robo.acionarMotores (0,0);
    delay (500);    
}

// método responsável por alinhar o robo com a 
// parede da area de resgate
void Resgate::alinhar (){
    robo.acionarMotores(-40,-40);
    delay (800);
    robo.acionarMotores(40,40);
    delay (200);
    robo.acionarMotores(-40,-40);
    delay (400);
    robo.acionarMotores(40,40);
    delay (200);
    robo.acionarMotores(-40,-40);
    delay (200);
    robo.acionarMotores(0,0);
    delay (100);
}

// método responsável por fazer o robô identificar a area de 
// resgate utilizando o sonar lateral
bool Resgate::verificaSonarArea (char area){
    robo.acionarMotores (0,0);
    delay (100);

    if (area == 'z'){
        return (robo.lerSensorSonarDir() <= DISTANCIA_AREA);      
    } else {
        return (robo.lerSensorSonarEsq() <= DISTANCIA_AREA);  
    }
}

// método responsável por verificiar se tem bolinha dentro da garra
// caso tenha iremos salvar a vitima
bool Resgate::verificaVitimaGarra (){
    //robo.acionarServoGarra1 (65, 83, 10);
    return robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2();
}

// método responsável por fazer o robô piscar os leds
// de quantas formas quisermos 
void Resgate::sinalizar (int vezes){
    for(int i = 0; i < vezes; i++){  
        robo.ligarTodosLeds();
        delay(200);
        robo.desligarTodosLeds();
        delay(100);
    }
}

// método responsável por fazer o robô entrar a sala de 
// resgate de forma adquada e identificar o tipo que esta a area
char Resgate::entrar (){
    // caso a area esteja como padrão da obr
    robo.acionarMotores (20,60);
    delay (550);
    robo.acionarMotores (-40,-40);
    delay (300);
    while (robo.lerSensorSonarDir() < 20){
        robo.acionarMotores (-40,38);
        delay (50);
    }

    robo.acionarMotores (-40,38);
    delay (250);
    
    this -> alinhar ();

    robo.acionarMotores (0,0);
    delay (3000);
    
    return 'z';

    /*
    // caso a area esteja diferente do padrão obr

    robo.acionarMotores (60,20);
    delay (550);
    robo.acionarMotores (-40,-40);
    delay (200);
    while (robo.lerSensorSonarEsq() < 20){
        robo.acionarMotores (40,-38);
        delay (50);
    }

    robo.acionarMotores (40,-38);
    delay (250);
    
    this -> alinhar ();
    return 'y';    */
}

// método responsável por fazer o robô identificar a 
// area de resgate com a distncia do sonar lateral
char Resgate::identificarZona(char area){    
    robo.desligarTodosLeds();
    robo.acionarMotores (40,38);
    delay (100);

    if (area == 'z'){
        robo.acionarMotores (40,-38); 
        delay (DELAY_DIR);  
    } else {
        robo.acionarMotores (-40,38); 
        delay (DELAY_ESQ);    
    }

    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);

    // vamos seguir até a possivel area A
    garra.fecharGarraMovimento(800, 500);

    robo.acionarMotores (0,0);
    delay (100);
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (100);

    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (DELAY_VERIFICA_ZONA);  
    } else {
        robo.acionarMotores (40,-38);
        delay (DELAY_VERIFICA_ZONA);
    }
    

    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (40,38);
    delay (700);
    robo.acionarMotores (0,0);
    delay (100);

    // verifica se a area é A
    if (verificaSonarArea(area)){
        this -> sinalizar (3);
        robo.ligarLed (1);  
        
        // ficar de frente a area
        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (520);
        } else {
            robo.acionarMotores(-40,38);
            delay (520);
        }

        // se tiver bolinha então solta
        if (verificaVitimaGarra()){
            robo.acionarMotores(40,38);
            delay (200);
            this -> soltarBolinha ();
            robo.acionarMotores(-40,-38);
            delay (100);
        } 
        return 'a';
    }

    // caso não encontre a zona na posição A
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (DELAY_VERIFICA_ZONA);    
    } else {
        robo.acionarMotores (40,-38);
        delay (DELAY_VERIFICA_ZONA);  
    }

    // vamos alinhar com o espaço vazio
    this -> alinhar ();
    robo.acionarMotores (40,38);
    delay (200);

    // vamos verificar o espaço deixado 
    if (area == 'z'){
        robo.acionarMotores (40,-38);
        delay (460); 
    }else {
        robo.acionarMotores (-40,38);
        delay (460); 
    }

    robo.acionarMotores (-40,-38);
    delay (200);
    robo.acionarMotores (0,0);
    delay (100);

    // vamos continuar varendo a sala 3 para enontrar a zona
    if (verificaVitimaGarra()){
        garra.baixar ();
        garra.abrir ();
    } else {
        garra.abrir ();
        garra.baixar ();
    }

    // tenta pegar uma bolinha no canto
    robo.acionarMotores (0,0);
    delay (100); 
    garra.fecharGarraMovimento(500, 250);
    robo.acionarMotores(0, 0); 
    delay(100);
    subir();
    robo.acionarMotores (40,38);
    delay (300);
    
    // vamos alinha e verificar a outra zona
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (500);
    } else {
        robo.acionarMotores (40,-38);
        delay (500);  
    }

    // alinha com a parede na posição A
    this -> alinhar (); 

    // vamos continuar varendo a sala 3 para enontrar a zona
    if (verificaVitimaGarra()){
        garra.baixar ();
        garra.abrir ();
    } else {
        garra.abrir ();
        garra.baixar ();
    }
    
    robo.acionarMotores (0,0);
    delay (100); 
    
    // seguir um pouco     
    garra.fecharGarraMovimento(1200, 800);
    robo.acionarMotores (0,0);
    delay (100);
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (100);

    // vamos seguir lateral com a possivel sala B
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (DELAY_VERIFICA_ZONA);
    } else {
        robo.acionarMotores (40,-38);
        delay (DELAY_VERIFICA_ZONA);
    }
    
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (40,38);
    delay (700);
    robo.acionarMotores (0,0);
    delay (100);
   
    // caso a zona esteja a frente da entrada da sala
    if (verificaSonarArea(area)){
        this -> sinalizar (3);
        robo.ligarLed (2);  

        // vamos ficar de frente com a area de resgate B
        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (520);
        } else {
            robo.acionarMotores(-40,38);
            delay (520);
        }
        
        // verifica se tem bolinha na garra
        if(verificaVitimaGarra()){
            robo.acionarMotores(40,38);
            delay (200);
            this -> soltarBolinha ();
            robo.acionarMotores(-40,-38);
            delay (100);
        }
        return 'b';
    }
    else {
        robo.ligarLed (3);
    }
    
    // caso não tenha encontrado a area de resgate na A ou B 
    // so podera esta presente na zona C
    // caso não esteja vamos verificar o canto que não foi preenchido
    
    if (area == 'z'){ 
        robo.acionarMotores (-40,38);
        delay (DELAY_VERIFICA_ZONA);
    } else { 
        robo.acionarMotores (40,-38);
        delay (DELAY_VERIFICA_ZONA);
    }

    robo.acionarMotores (0, 0);
    delay (100);    
    this -> alinhar ();
    robo.acionarMotores (40,38);
    delay (200);
    
    if (area == 'z'){
        robo.acionarMotores (40,-38);
        delay (480);
    } else {
        robo.acionarMotores (-40,38);
        delay (480);
    }
    
    // caso não encontre a zona na posição A
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (DELAY_VERIFICA_ZONA);    
    } else {
        robo.acionarMotores (40,-38);
        delay (DELAY_VERIFICA_ZONA);  
    }

    // vamos alinhar com o espaço vazio
    this -> alinhar ();
    robo.acionarMotores (40,38);
    delay (200);

    // vamos verificar o espaço deixado 
    if (area == 'z'){
        robo.acionarMotores (40,-38);
        delay (460); 
    }else {
        robo.acionarMotores (-40,38);
        delay (460); 
    }

    robo.acionarMotores (-40,-38);
    delay (200);
    robo.acionarMotores (0,0);
    delay (100);

    // vamos continuar varendo a sala 3 para enontrar a zona
    if (verificaVitimaGarra()){
        garra.baixar ();
        garra.abrir ();
    } else {
        garra.abrir ();
        garra.baixar ();
    }

    // tenta pegar uma bolinha no canto
    robo.acionarMotores (0,0);
    delay (100); 
    garra.fecharGarraMovimento(500, 250);
    robo.acionarMotores(0, 0); 
    delay(100);
    subir();
    robo.acionarMotores (40,38);
    delay (300);
    
    // vamos alinha e verificar a outra zona
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (500);
    } else {
        robo.acionarMotores (40,-38);
        delay (500);  
    }

    // alinha com a parede na posição B
    this -> alinhar (); 
    return 'c';
}

// método responsável por fazer o robô voltar para o ponto zero 
// em relação a area de resgate
void Resgate::restoDosCantos (char zona, char area){
    // se as area de resgates forem A ou B 
    // o robô ira esta de frente para a are de resgate
    // ja no caso C o robô estara alinhado no espaco vazio
    // da area B

    if (zona != 'c'){        
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (200);
    
        // giro de 180 
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(40,-38);
        delay (800);
        robo.acionarMotores(0,0);
        delay (100);

        // vamos alinhar com a area de resgate caso A ou B
        this -> alinhar ();

        // vamos seguir ate o cento da sala 3
        robo.acionarMotores(0,0);
        delay (100); 
        robo.acionarMotores(40,38);
        delay (750);               
        robo.acionarMotores(0,0);
        delay (100);
        
        // vamos alinha ao lado da area de resgate
        if (zona == 'z'){
            robo.acionarMotores(-40,38);
            delay (DELAY_VERIFICA_ZONA);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (DELAY_VERIFICA_ZONA);
        }

        robo.acionarMotores(0,0);
        delay (100);
        this -> alinhar ();
        robo.acionarMotores(40,38);
        delay (200); 
        robo.acionarMotores(0,0);
        delay (100);

        // verificar os cantos
        if (zona == 'z'){
            robo.acionarMotores(40,-38);
            delay (DELAY_DIR);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (DELAY_ESQ);
        }  
        robo.acionarMotores(0,0);
        delay (100);         

        // vamos começar a voltar pro ponto zero
        if (verificaVitimaGarra()){
            garra.baixar ();
            garra.abrir ();
        }
        else {
            garra.abrir ();
            garra.baixar ();
        }
      
        robo.acionarMotores (0,0);
        delay (100);  
        garra.fecharGarraMovimento(800, 500);
        
        robo.acionarMotores (0,0);
        delay (100);
        garra.subir();
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (250);               
        robo.acionarMotores (0,0);
        delay (100);
        
        if (zona == 'z'){
            robo.acionarMotores(-40,38);
            delay (DELAY_ESQ);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (DELAY_DIR);
        }  

        robo.acionarMotores(0,0);
        delay (100); 

        // robô vai alinhar com o espaço vazio da zona B
        this -> alinhar ();
        robo.acionarMotores(0,0);
        delay (100); 

        // vamos tentar pegar a bolinha na segunda parte
        if (verificaVitimaGarra()){
            garra.baixar ();
            garra.abrir ();
        }
        else {
            garra.abrir ();
            garra.baixar ();
        }
        robo.acionarMotores (0,0);
        delay (100); 

        // seguir na sala até o ponto C
        garra.fecharGarraMovimento(1800, 1400);
        robo.acionarMotores (0,0);
        delay (100);
        garra.subir();
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (200);               
        robo.acionarMotores (0,0);
        delay (100);

        if (zona == 'z'){
            robo.acionarMotores(-40,38);
            delay (DELAY_ESQ);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (DELAY_DIR);
        }  
        robo.acionarMotores(0,0);
        delay (100); 
 
        // vamos alinhar com a posição zero 
        this -> alinhar ();
    }    

    // vamos voltar ao ponto zero da area C
    else {
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (200);               
        robo.acionarMotores (0,0);
        delay (100);

        if (zona == 'z'){
            robo.acionarMotores(40,-38);
            delay (DELAY_ESQ);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (DELAY_DIR);
        }  
 
        robo.acionarMotores(40,38);
        delay (1000);               
        this -> alinhar();
    }
}

void Resgate::voltar (char zona, char area){
    if (zona == 'a' or zona == 'c'){
        robo.acionarMotores(-40,-38);
        delay (1300);
        robo.acionarMotores(0,0);
        delay (1000);

        if (area == 'z'){
            robo.acionarMotores(-40,38);
            delay (250);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (250);
        }
        
        robo.acionarMotores(0,0);
        delay (1000);
        robo.acionarMotores(-40,-38);
        delay (500);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (200);


        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (480);
        }else {
            robo.acionarMotores(-40,38);
            delay (480);
        }

        
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
    }
    else if (zona == 'b'){
        robo.acionarMotores(-40,-38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);

        if (area == 'z'){
            robo.acionarMotores(-40,38);
            delay (1000);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (1000);
        }


        robo.acionarMotores(0,0);
        delay (100);
        this -> alinhar();
        robo.acionarMotores(40,38);
        delay (800);
        robo.acionarMotores(0,0);
        delay (500);


        if (area == 'z'){
            robo.acionarMotores(-40,38);
            delay (650);
        }
        else {    
            robo.acionarMotores(40,-38);
            delay (650);
        }

        robo.acionarMotores(0,0);
        delay (500);
        robo.acionarMotores(-40,-38);
        delay (1000);
        this -> alinhar ();
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);

        if (area == 'z'){
            robo.acionarMotores(-40,38);
            delay (450);
        }
        else {    
            robo.acionarMotores(40,-38);
            delay (450);
        }
        
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (400);
        this -> alinhar();
    }
}




// métodos responsavel por resgatar a vitima
void Resgate::resgatarVitima (char zona, char area){ 
    
    robo.acionarMotores (40,38);
    delay (1200);

    if (zona == 'a' or zona == 'c'){
        if (area == 'z'){
            robo.acionarMotores(-40,38);
            delay (450);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (450);
        }
    }

    else {
        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (450);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (450);
        }
    }


    robo.acionarMotores (0,0);
    delay (100);   
    robo.acionarMotores(-40,-38);
    delay (800);    
    this -> alinhar ();       
    robo.acionarMotores(40,38);
    delay (1300);
    robo.acionarMotores (0,0);
    delay (100);


    if (zona == 'a' or zona == 'c'){     
        if (area == 'z'){
            robo.acionarMotores(-40,38);
            delay (630);
        }
        else {
            robo.acionarMotores(40,-38);
            delay (630);
        }

        robo.acionarMotores(-40,-38);
        delay (700);
        this -> alinhar ();

        // giro para ficar de frente com a sala
        robo.acionarMotores(40,38);
        delay (200);
        robo.acionarMotores(0,0);
        delay (100);

        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (880);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (880);
        }
        
        robo.acionarMotores(40,38);
        delay (200);
        this -> soltarBolinha ();
    }
    
    
    else {
        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (630);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (630);
        }

        robo.acionarMotores(-40,-38);
        delay (500);
        this -> alinhar ();

        // giro para ficar de frente com a sala
        
        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (1000);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (1000);
        }

        robo.acionarMotores(40,38);
        delay (200);
        this -> soltarBolinha ();
    }
}







void Resgate::voltarZero(char zona, char area){   
    this -> sinalizar (3);

    robo.acionarMotores (44,40);
    delay (200);


    if (zona == 'a' or zona == 'c'){
        if (area == 'z'){
            robo.acionarMotores (44,-40);
            delay (DELAY_DIR);
        }   
        else {
            robo.acionarMotores (-44,40);
            delay (DELAY_ESQ);
        }
    }
    else {
        if (area == 'z'){
            robo.acionarMotores (-44,40);
            delay (DELAY_ESQ);
        }   
        else {
            robo.acionarMotores (44,-40);
            delay (DELAY_DIR);
        }
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


   garra.fecharGarraMovimento(1900, 1500);
  
  
    if (zona == 'a' or zona == 'c'){
        if (area == 'z'){
            robo.acionarMotores (-44,40);
            delay (480);  
        }
        else {
            robo.acionarMotores (44,-40);
            delay (480);  
        }
    }
    
    else {
        // caso zona a (viro para a esquerda)
        robo.acionarMotores (44,-40);
        delay (480);
            
    } 

    // ele vai alinhar em todos os caso
    this -> alinhar ();  
}



void Resgate::irLateralEsq (char area){
    robo.acionarMotores (40,38);
    delay (200);
   
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (DELAY_ESQ);
    }
    else {
        robo.acionarMotores (40,-38);
        delay (DELAY_DIR);
    }

    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);

    garra.fecharGarraMovimento(450, 250);

    robo.acionarMotores (0,0);
    delay (100);   
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (100);   

    if (area == 'z'){
        robo.acionarMotores (40,-38);
        delay (DELAY_ESQ);
    }
    else {
        robo.acionarMotores (-40,38);
        delay (DELAY_DIR);
    }

    robo.acionarMotores (0,0);
    delay (1000);
    this -> alinhar ();       
}



// método responsável por verificar a lateral
// se a bolinha estiver
void Resgate::irLateralDir (char area){
    robo.acionarMotores (40,38);
    delay (200);

    if (area == 'z'){
        robo.acionarMotores (40,-38);
        delay (DELAY_DIR);
    } 
    else {
        robo.acionarMotores (-40,38);
        delay (DELAY_ESQ);
    }

    robo.acionarMotores (0,0);
    delay (100);
    garra.abrir ();
    garra.baixar ();
    robo.acionarMotores (0,0);
    delay (100);


    garra.fecharGarraMovimento(450, 250);

    robo.acionarMotores (0,0);
    delay (100);
    garra.subir ();
    robo.acionarMotores (0,0);
    delay (100);  

    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (DELAY_ESQ);
    }
    else {
        robo.acionarMotores (40,-38);
        delay (DELAY_DIR);
    }

    robo.acionarMotores (0,0);
    delay (1000);
    this -> alinhar ();       
}


/**************************** MÉTODOS RESPONSÁVEIS POR RESGATAR AS VITIMAS ***********************/

void Resgate::varrerSala (char zona, char area){
    
    while (true){

        // saberemos se o robô já salvou a vitima
        bool salvouVitima = false;                 

        // ele ira varrer a sala 3 vezes por isso o for até 3
        for (int i = 0; i <= 3; i++){             
    
            // voltares o contador para 0
            if (salvouVitima == true){
                salvouVitima = false;
                i = 0;
            }
 
            // vamos verificar se tem bolinha na garra
           
            if (verificaVitimaGarra()){
                sinalizar (3);

                // vamos resgatar a vitima e voltar 
                this -> resgatarVitima (zona, area);
                this -> voltar(zona, area); 
                salvouVitima = true;
            }


            // caso a vitima não seja identificada
            else {        
                garra.abrir ();
                garra.baixar ();
                robo.acionarMotores (0,0);
                delay (100);  
            }  
           
            // vamos seguir (POUCO) na sala tentando pegar a bolinha 
            if (i != 3){
               garra.fecharGarraMovimento(1900, 1500);                
            }
            
            // vamos seguir (MUITO) na sala tentando pegar a bolinha
            else if (i == 3){
                garra.fecharGarraMovimento(1400, 1000);
            }   
            
            // vamos voltar e alinhar com a parede
            robo.acionarMotores(0,0);
            delay (100);
            robo.acionarMotores(-40,-38);
            delay (2000);       
            this -> alinhar ();
        
            // vamos verifificar novamente se ele possui uma bolinha na garra
            garra.subir();
            
            if (verificaVitimaGarra()){
                sinalizar (3);

                // vamos resgatar a vitima e voltar 
                this -> resgatarVitima (zona, area);
                this -> voltar(zona, area); 
                salvouVitima = true;
            }


            // caso o robô não encontre a bolinha seguindo na sala 
            // o mesmo vai virar para os lado procurando 

            else if ((zona == 'a' or zona == 'c') and (i != 3)){
                this-> irLateralEsq (zona);   
                
                if (verificaVitimaGarra()){
                    sinalizar (3);
                 
                    // vamos resgatar a vitima e voltar 
                    this -> resgatarVitima (zona, area);
                    this -> voltar(zona, area); 
                    salvouVitima = true;
                }
            }
              
            else if ((i + 1) == 4){
                this-> irLateralDir (zona);             
                                   
                if (verificaVitimaGarra()){
                    sinalizar (3);
                        
                    // vamos resgatar a vitima e voltar 
                    this -> resgatarVitima (zona, area);
                    this -> voltar(zona, area); 
                    salvouVitima = true;
                }
            }    
        }

        // vamos voltar ao ponto zero
        this -> voltarZero(zona, area);
    }
}
