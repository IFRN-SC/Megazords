#include "Resgate.h"

Resgate::Resgate(){}

void Resgate::iniciar (){
    this -> entrarNaSala ();
    char areaResgate = this -> identificaZona ();
    this -> pontoZero (areaResgate);

    // podemos varrer a sala 3 com a informação da area de resgate
    this -> seguirNaSala (areaResgate);
}


/********************************     Métodos para os movimentos do robô    ***********************************/

// método responsável por procurar bolinha nas laterais esquerdas
void Resgate::roboIrLateralEsq (){
    this -> roboFrente (120);
    this -> roboVirarEsq (480);

    this -> roboParar (100);
    garra.abrir ();
    garra.baixar ();
    this -> roboParar (100);

    fecharGarraMovimento(450, 250);

    this -> roboParar (100);
    garra.subir ();
    this -> roboParar (100);
   
    this -> roboVirarDir (480);
    this -> roboParar (100);
    this -> alinhar ();       
}

// método responsável por procurar bolinha nas laterais direitas
void Resgate::roboIrLateralDir (){
    this -> roboFrente (120);
    this -> roboVirarDir (480);

    this -> roboParar (100);
    garra.abrir ();
    garra.baixar ();
    this -> roboParar (100);

    fecharGarraMovimento(450, 250);

    this -> roboParar (100);
    garra.subir ();
    this -> roboParar (100);
   
    this -> roboVirarEsq (480);
    this -> roboParar (100);
    this -> alinhar ();       
}

// método reponsáve por fazer o robô virar para a direita
void Resgate::roboVirarDir (int tempo){
    robo.acionarMotores (37,-40);
    delay (tempo);    
} 

// método reponsáve por fazer o robô virar para a direita
void Resgate::roboVirarEsq (int tempo){
    robo.acionarMotores (-37,40);
    delay (tempo);    
} 

// método responsável por fazer o robô voltar 
void Resgate::roboVoltar (int tempo){
    robo.acionarMotores (-37,-40);
    delay (tempo);
}

// método responsável por fazer o robô ir pra frente
void Resgate::roboFrente (int tempo){
    robo.acionarMotores (37,40);
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
    this -> roboParar (100);
}

// método responsável por fazer o robô entrar corretamente na sala
void Resgate::entrarNaSala (){
    robo.acionarMotores (20,60);
    delay (550);
    roboVoltar (300);

    while (robo.lerSensorSonarEsq() < 20){
        this -> roboVirarEsq (50);
    }

    this -> roboVirarEsq (250);
    this -> alinhar ();
}

// método responsável por verificar se a area de resgate com o sonar ESQ 
bool Resgate::verificarArea (){
    this -> roboParar(200);
    return (robo.lerSensorSonarDir() <= 20);
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
    this -> roboVirarDir (480);

    this -> roboParar (100);
    garra.abrir ();
    garra.baixar ();
    this -> roboParar (100);
    
    garra.fecharGarraMovimento(900, 500);
    this -> roboParar (100);
    garra.subir (); 
    this -> roboParar (100);
    

    // o robô ira está lateralmente a area de resgate
    this -> roboVirarEsq (250);
    this -> roboFrente(800);
    this -> roboParar (100);
    
    if (this -> verificarArea()){
        this -> sinalizar (3);   
        robo.ligarLed (1);  

        this -> roboVirarDir (500);
        this -> roboFrente (100); 

        // caso o robo esteja com a bolinha dentro da garra
        // ele ira ate a area de resgate usando o sonar
        if(garra.pegouVitima()){
            this -> roboFrente (100); 
            this -> soltarBolinha ();
            this -> roboVoltar(200);
        }

        // vamos alinhar com a sala de resgate
        this -> roboVirarDir (800);
        this -> alinhar ();

        // retorna a posição A da area de resgate
        return 'a';
    }

    
    
    // caso não esteja vamos verificar o canto que não foi preenchido
    this -> roboVirarEsq (220);
    this -> roboParar (100);
    this -> alinhar ();   
    this -> roboParar (100);
    this -> roboFrente (200);
    this -> roboVirarDir (460);
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
    this -> roboVirarEsq (500);
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
    this -> roboVirarEsq (180);
    
    // ir lateral com a area B
    this -> roboParar(100); 
    this -> roboFrente (700);
    this -> roboParar(100);
   

    // vamos verificar se a area de resgate é B
    if (this -> verificarArea()){
        this -> sinalizar (3);
        robo.ligarLed (2);
        this -> roboVirarDir (500);
        this -> roboFrente (100);

        if (garra.pegouVitima()){
            this -> roboFrente (200); 
            this -> soltarBolinha ();
            this -> roboVoltar(100);
        }

        // vamos alinhar com a sala de resgate
        this -> roboVirarDir (800);
        this -> alinhar ();

        // retorna a posição B da area de resgate
        return 'b';

    }else {
        robo.ligarLed (3);
    }


    // caso não esteja vamos verificar o canto que não foi preenchido
    this -> roboVirarEsq (200);
    this -> roboParar (100);
    this -> alinhar ();   
    this -> roboParar (100);
    this -> roboFrente (200);
    this -> roboVirarDir (460);
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
    this -> roboVirarEsq (500);
    this -> alinhar ();
    this -> roboParar(100);
    garra.baixar ();
    garra.abrir ();
    this -> roboParar(100);

    // retorna a posição C da area de resgate
    return 'c';
}

// método responsável por fazer o robô a voltar ao ponto zero da area de resgate
void Resgate::pontoZero (char area){
  
    // caso a zona seja A ou B, a volta para o ponto zero são quase identicas
    if (area == 'a' or area == 'b'){
        // vamos voltar para o ponto zero
        this -> voltarAreaResgate (area);
    }

    // caso a area seja C, apenas faremos o robô voltar de ré
    // ate a posição vazia de A  
    else {
        this -> roboFrente (200);
        this -> roboParar (100);
        this -> roboVirarDir (480);   
        this -> roboVoltar (1000);
        this -> alinhar ();
    }
}


/********************************     Métodos para os resgatar a vitima ao varrer a area    ***********************************/

// metodo resposável por resgatar a vitima
void Resgate::resgatarVitima (char area){
    // vamos pra frente com o robô e a bolinha
    this -> roboFrente (1200);
    this -> roboParar (200);

    if (area == 'a' or area == 'c'){
        this -> roboVirarEsq (450);
    }else {
        this -> roboVirarDir (450);
    }

    this -> roboParar (100);
    this -> roboVoltar (800);
    this -> alinhar ();      
    this -> roboFrente (1800);
    this -> roboParar (300);
    
    // vamos salvar a vitima para o caso A e B
    if (area == 'a' or area == 'c'){
        this -> roboVirarEsq (630);
    }
    else {
        this -> roboVirarDir (630);
    }  

    this -> roboVoltar (700);
    this -> alinhar ();

    // giro para ficar de frente com a sala
    this -> roboFrente (200);
    this -> roboParar (100);
    this -> roboVirarDir (880);
    this -> roboFrente (200);      
    this -> soltarBolinha ();
    this -> roboParar (100);   
    this -> roboVoltar (200);  
    this -> roboVirarDir (1000); 
    this -> roboParar (100); 
    this -> alinhar();     
}

// método responsável por voltar apos resgatar vitima
void Resgate::voltarAreaResgate (char area){
    this -> roboFrente (100);
    this -> roboParar(200);
    garra.abrir ();
    garra.baixar ();
    fecharGarraMovimento(2000, 1500); 
    this -> roboParar (100);
    garra.subir ();
    this -> roboParar (100);
    this -> roboVirarDir(800);
    this -> roboParar (100);
    this -> alinhar();

    if (area != 'b'){
        this -> roboParar (1000);   
        this -> roboFrente(200);
        this -> roboVirarDir (480);  
        this -> alinhar();
    }
    
    
}

// método responsável por fazer o robô varrer os cantos e voltar para a posição zero
void Resgate::aposVarrerSala (char area){
    this -> sinalizar (10);
}


// método responsáevl por varrer a sala e resgatar a vitima
void Resgate::seguirNaSala (char area){
    
    bool resgatouVitima = false;

    // estrutura de repetição para varrer a sala
    while (true){
        
        for (int i = 0; i < 3; i++){
            
            // vamos voltar para sempre dentro do for
            if (resgatouVitima == true){
                resgatouVitima = false;
                i = 0;
            }

            // vamos verificar se tem bolinha na garra 
            if (garra.pegouVitima()){
                sinalizar (5);
                this -> resgatarVitima (area);
                this -> voltarAreaResgate(area); 
                resgatouVitima = true;
            }
 
            // vamos varrer a sala caso não encontre nenhuma bolinha
            else {
                garra.abrir ();
                garra.baixar ();
                this -> roboParar (100);
            }

            fecharGarraMovimento(1900, 1500);
            this -> roboParar (500);
            this -> roboVoltar (2000);
            this -> alinhar ();
            garra.subir();
            this -> roboParar (100);

            // vamos verificar se tem bolinha na garra 
            if (garra.pegouVitima()){
                sinalizar (5);
                this -> resgatarVitima (area);
                this -> voltarAreaResgate(area); 
                resgatouVitima = true;
            }
             

            // caso não conseguirmos pegar bolinha ao varrer
            // vamos seguir lateralmente
            if (area == 'a' or area == 'c'){
                this -> roboIrLateralEsq ();   
            }

            // caso a area de resgate seja B, vamos girar 
            // para a direita
            else {
                this -> roboIrLateralDir ();
            }

            // vamos verificar se tem bolinha na garra 
            if (garra.pegouVitima()){
                sinalizar (5);
                this -> resgatarVitima (area);
                this -> voltarAreaResgate(area); 
                resgatouVitima = true;
            }
        }   // for

        // vamos esta de frente a sala de resgate após varrer a sala 3 vezes
        // executaremos um metodo pra varrer os cantos e voltar ate o ponto zero
        
        this -> aposVarrerSala (area);
    }       // while
}
