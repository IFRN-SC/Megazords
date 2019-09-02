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
     
    area = this -> entrar ();         // vamos entrar corretamente na sala 3
    zona = identificarZona (area);
    
     
    
} 


void Resgate::sinalizar (int vezes){
    for(int i = 0; i < vezes; i++){  
        robo.ligarTodosLeds();
        delay(400);
        robo.desligarTodosLeds();
        delay(200);
    }
}


bool Resgate::verificaVitimaGarra (){
    return robo.fimDeCursoPressionado1() or robo.fimDeCursoPressionado2();
}


void Resgate::soltarBolinha (){
    robo.acionarMotores (0,0);
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
   
    robo.acionarMotores (0,0);
    delay (100);    
}




char Resgate::entrar (){
    char valorRetorno;
    
    while ((robo.lerSensorSonarEsq()+20) > robo.lerSensorSonarDir() or 
        (robo.lerSensorSonarDir()+20) > robo.lerSensorSonarEsq()){
    
        robo.acionarMotores (40,40);
    }

    // caso seja verdade, identificaremos que a area e Y
    if ((robo.lerSensorSonarEsq()+20) < robo.lerSensorSonarDir()){
        robo.acionarMotores (60,20);
        delay (550);
        robo.acionarMotores (-40,-40);
        delay (200);
        
        while (robo.lerSensorSonarEsq() < 20){
            robo.acionarMotores (40,-38);
            delay (50);
        }

        valorRetorno = 'y';    
    }
    // caso seja verdade, identificaremos que a area e Z
    else {
        robo.acionarMotores (20,60);
        delay (550);
        robo.acionarMotores (-40,-40);
        delay (200);

        while (robo.lerSensorSonarDir() < 20){
            robo.acionarMotores (-40,38);
            delay (50);
        }
        valorRetorno = 'z';
    }
    
    robo.acionarMotores (-40,40);
    delay (250);
    this -> alinhar ();

    return valorRetorno;
}

void Resgate::alinhar (){
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (400);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(40,40);
    delay (200);
    robo.acionarMotores(-40,-40);
    delay (1000);
    robo.acionarMotores(0,0);
    delay (1000);
}


bool Resgate::verificaSonarArea (char area){
    robo.acionarMotores (0,0);
    delay (100);

    if (area == 'z'){
        return (robo.lerSensorSonarDir() <= 15);      
    }
    else {
        return (robo.lerSensorSonarEsq() <= 15);  
    }
}


char Resgate::identificarZona(char area){
    boolean pegouVitima = false;
    
    
    robo.desligarTodosLeds();
    robo.acionarMotores (40,38);
    delay (100);


    if (area = 'z'){
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


    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 800;
    while(t < x){
      robo.acionarMotores(40, 38);     
      if(t > (x-500)){
        robo.acionarServoGarra1(map(t, 500, 800, 0, 83 ));  
      }
      t = (millis() -  ant);
    }

    robo.acionarMotores (0,0);
    delay (100);
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (100);


    // o robô ira está lateralmente a area de resgate
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (220);  
    }
    else {
        robo.acionarMotores (40,-38);
        delay (220);
    }
    
    robo.acionarMotores (40,38);
    delay (700);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarServoGarra1 (65, 83, 10);

    // caso a zona esteja a frente da entrada da sala
    if (verificaSonarArea(area)){
        this -> sinalizar (5);

        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (520);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (520);
        }
        
        robo.acionarMotores(40,38);
        delay (100);                

        if(verificaVitimaGarra()){
            robo.ligarLed (1);  
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
        delay (200);    
    }  
    else {
        robo.acionarMotores (40,-38);
        delay (200);  
    }

    robo.acionarMotores(0, 0); 
    delay(100); 
    this -> alinhar ();
   
 
    robo.acionarMotores (40,38);
    delay (200);

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
    x = 500;
    while(t < x){
        robo.acionarMotores(40, 38);     
        if(t > (x-250)){
            robo.acionarServoGarra1(map(t, 250, 500, 0, 83));  
         }
         t = (millis() -  ant);
    };
    
    robo.acionarMotores(0, 0); 
    delay(100);
    
    subir();
    
    robo.acionarMotores (40,38);
    delay (300);
    
    // vamos alinha e verificar a outra zona
    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (500);
    }
    else {
        robo.acionarMotores (40,-38);
        delay (500);  
    }
    
    this -> alinhar (); 

    // vamos continuar varendo a sala 3 para enontrar a zona
    if (verificaVitimaGarra()){
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

    
    // seguir um pouco     
    ant = millis();
    angInicial = 2;
    t = (millis() -  ant4);
    x = 1200;
    while(t < x){
      robo.acionarMotores(40, 38);     
      if(t > (x-400)){
        robo.acionarServoGarra1(map(t, 800, 1200, 0, 83));  
      }
      t = (millis() -  ant4);
    }
    
    robo.acionarMotores (0,0);
    delay (100);
    garra.subir (); 
    robo.acionarMotores (0,0);
    delay (100);

    if (area == 'z'){
        robo.acionarMotores (-40,38);
        delay (180);
    }
    else {
        robo.acionarMotores (40,-38);
        delay (180);
    }
    
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarMotores (40,38);
    delay (700);
    robo.acionarMotores (0,0);
    delay (100);
    robo.acionarServoGarra1 (65, 83, 10);



    // caso a zona esteja a frente da entrada da sala
    if (verificaSonarArea(area)){
        this -> sinalizar (5);

        if (area == 'z'){
            robo.acionarMotores(40,-38);
            delay (520);
        }
        else {
            robo.acionarMotores(-40,38);
            delay (520);
        }
        
        robo.acionarMotores(40,38);
        delay (100);                

        if(verificaVitimaGarra()){
            robo.ligarLed (2);  
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
    
    // caso não tenha encontrado a area de resgate na A or B 
    // so podera esta presente na zona C

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
    delay (480);
    robo.acionarMotores (-40,-38);
    delay (1000);
    this -> alinhar ();
    
    return 'c';

    
    



}




/************************************************************************* CÓDIGO ANTIGO ****************************************************

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

    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 500;
    while(t < x){
        robo.acionarMotores(40, 38);     
        if(t > (x-200)){
            robo.acionarServoGarra1(map(t, 300, 500, 0, 83));  
         }
         t = (millis() -  ant);
    }

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

    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 500;
    while(t < x){
        robo.acionarMotores(40, 38);     
        if(t > (x-200)){
            robo.acionarServoGarra1(map(t, 300, 500, 0, 83));  
         }
         t = (millis() -  ant);
    }

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
        robo.acionarMotores(-40,38);
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
        robo.acionarMotores(40,-38);
        delay (480);               
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
                robo.acionarServoGarra1(map(t, 500, 800, 0, 83));  
             }
             t = (millis() -  ant);
        }
        
        robo.acionarMotores (0,0);
        delay (100);
        
        garra.subir();
        
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(40,38);
        delay (250);               
        robo.acionarMotores (0,0);
        delay (100);
        robo.acionarMotores(-40,38);
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
            robo.acionarServoGarra1(map(t, 1400, 1800, 0, 83));  
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

        robo.acionarMotores(-40,38);
        delay (480);               
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
                robo.acionarServoGarra1(map(t, 400, 700, 0, 83));  
             }
             t = (millis() -  ant);
        }
        
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
        
        ant = millis();
        angInicial = 2;
        t = (millis() -  ant);
        x = 1000;
        while(t < x){
          robo.acionarMotores(40, 38);     
          if(t > (x-300)){
            robo.acionarServoGarra1(map(t, 700, 1000, 0, 83));  
          }
          t = (millis() -  ant);
        }
        
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
        delay (500);
        robo.acionarMotores(0,0);
        delay (100);
        robo.acionarMotores(-40,-38);
        delay (500);
        
        this -> alinhar ();
        
    }
}

void Resgate::voltarZero(char zona){   
    for (int j = 0; j < 20; j++){  
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


    long ant = millis();
    int angInicial = 2;
    long t = (millis() -  ant);
    int x = 1900;

    while(t < x){
        robo.acionarMotores(40, 38);     
        if (t > (x-400)){
            robo.acionarServoGarra1(map(t, 1500, 1900, 0, 70));  
        }
    t = (millis() -  ant);
    }
  
  
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
                long ant = millis();
                int angInicial = 2;
                long t = (millis() -  ant);
                int x = 1900;
                while(t < x){
                  robo.acionarMotores(40, 38);     
                  if(t > (x-400)){
                    robo.acionarServoGarra1(map(t, 1500, 1900, 0, 83));  
                  }
                  t = (millis() -  ant);
                }
            }
            else if(i == 3){
                long ant = millis();
                int angInicial = 2;
                long t = (millis() -  ant);
                int x = 1400;
                while(t < x){
                  robo.acionarMotores(40, 38);     
                  if(t > (x-400)){
                    robo.acionarServoGarra1(map(t, 1000, 1400, 0, 83));  
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
              
           else if ((zona == 'a' or zona == 'c') and (i != 3)){
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
           else if((i + 1) == 4){
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
}      */ 
