#include "Resgate.h"

Resgate::Resgate(){}

void Resgate::iniciar (){
    entrarNaSala ();
    char areaResgate = identificaZona ();
    pontoZero (areaResgate);

    // podemos varrer a sala 3 com a informação da area de resgate
    seguirNaSala (areaResgate);
}


/********************************     Métodos para os movimentos do robô    ***********************************/

// método responsável por procurar bolinha nas laterais esquerdas
void Resgate::roboIrLateralEsq (){
    movimento.roboFrente (200);
    movimento.roboVirarEsq (480);

    movimento.roboParar (100);
    garra.abrir ();
    garra.baixar ();
    movimento.roboParar (100);

    fecharGarraMovimento(450, 250);

    movimento.roboParar (100);
    garra.subir ();
    movimento.roboParar (100);

    movimento.roboVirarDir (480);
    movimento.roboParar (100);
    alinhar ();
}

// método responsável por procurar bolinha nas laterais direitas
void Resgate::roboIrLateralDir (){
    movimento.roboFrente (200);
    movimento.roboVirarDir (480);

    movimento.roboParar (100);
    garra.abrir ();
    garra.baixar ();
    movimento.roboParar (100);

    fecharGarraMovimento(450, 250);

    movimento.roboParar (100);
    garra.subir ();
    movimento.roboParar (100);

    movimento.roboVirarEsq (480);
    movimento.roboParar (100);
    alinhar ();
}

// método responsável por fazer o robô alinhar com a sala 3
void Resgate::alinhar (){
    movimento.roboVoltar(1000);
    movimento.roboFrente (200);
    movimento.roboVoltar (1000);
    movimento.roboFrente (150);
    movimento.roboVoltar (1000);
    movimento.roboParar (100);
}

// método responsável por fazer o robô entrar corretamente na sala
void Resgate::entrarNaSala (){
    robo.acionarMotores (20,60);
    delay (550);
    movimento.roboVoltar (300);

    while (robo.lerSensorSonarEsq() < 20){
        movimento.roboVirarEsq (50);
    }

    movimento.roboVirarEsq (250);
    alinhar ();
}

// método responsável por verificar se a area de resgate com o sonar ESQ
bool Resgate::verificarArea (){
    movimento.roboParar(200);
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
    movimento.roboFrente(300);
    movimento.roboVirarDir (480);

    movimento.roboParar (100);
    garra.abrir ();
    garra.baixar ();
    movimento.roboParar (100);

    garra.fecharGarraMovimento(900, 700);
    movimento.roboParar (100);
    garra.subir ();
    movimento.roboParar (100);


    // o robô ira está lateralmente a area de resgate
    movimento.roboVirarEsq (270);
    movimento.roboFrente(800);
    movimento.roboParar (100);

    if (verificarArea()){
        sinalizar (3);
        robo.ligarLed (1);

        movimento.roboVirarDir (500);
        movimento.roboFrente (100);

        // caso o robo esteja com a bolinha dentro da garra
        // ele ira ate a area de resgate usando o sonar
        if(garra.pegouVitima()){
            movimento.roboFrente (100);
            soltarBolinha ();
            movimento.roboVoltar(200);
        }

        // vamos alinhar com a sala de resgate
        movimento.roboVoltar (100);
        movimento.roboVirarDir (900);
        alinhar ();

        // retorna a posição A da area de resgate
        return 'a';
    }



    // caso não esteja vamos verificar o canto que não foi preenchido
    movimento.roboVirarEsq (220);
    movimento.roboParar (100);
    alinhar ();
    movimento.roboParar (100);
    movimento.roboFrente (300);
    movimento.roboVirarDir (460);
    movimento.roboVoltar (200);
    movimento.roboParar (100);

    // verificamos se tem boliha pra descer a garra
    garra.descerGarra (garra.pegouVitima ());
    garra.fecharGarraMovimento(500, 250);

    movimento.roboParar(100);
    garra.subir ();

    movimento.roboFrente (350);
    movimento.roboParar(100);

    // vamos alinha e verificar a outra zona
    movimento.roboVirarEsq (500);
    alinhar ();

    movimento.roboParar(100);
    garra.descerGarra (garra.pegouVitima ());
    movimento.roboParar(100);


    // seguir um pouco até a possivel area B
    garra.fecharGarraMovimento(1200, 1000);
    movimento.roboParar(100);
    garra.subir ();
    movimento.roboParar(100);
    movimento.roboVirarEsq (180);

    // ir lateral com a area B
    movimento.roboParar(100);
    movimento.roboFrente (700);
    movimento.roboParar(100);


    // vamos verificar se a area de resgate é B
    if (verificarArea()){
        sinalizar (3);
        robo.ligarLed (2);
        movimento.roboVirarDir (500);
        movimento.roboFrente (100);

        if (garra.pegouVitima()){
            movimento.roboFrente (200);
            soltarBolinha ();
            movimento.roboVoltar(100);
        }

        // vamos alinhar com a sala de resgate
        movimento.roboVirarDir (800);
        alinhar ();

        // retorna a posição B da area de resgate
        return 'b';

    }else {
        robo.ligarLed (3);
    }


    // caso não esteja vamos verificar o canto que não foi preenchido
    movimento.roboVirarEsq (200);
    movimento.roboParar (100);
    alinhar ();
    movimento.roboParar (100);
    movimento.roboFrente (300);
    movimento.roboVirarEsq (460);
    movimento.roboParar (100);

    // verificamos se tem boliha pra descer a garra
    garra.descerGarra (garra.pegouVitima ());
    garra.fecharGarraMovimento(1000, 800);

    movimento.roboParar(100);
    garra.subir ();
    movimento.roboParar(100);

    movimento.roboVirarEsq (1000);
    movimento.roboParar(100);
    alinhar ();

    // retorna a posição C da area de resgate
    return 'c';
}

// método responsável por fazer o robô a voltar ao ponto zero da area de resgate
void Resgate::pontoZero (char area){

    // caso a zona seja A ou B, a volta para o ponto zero são quase identicas
    if (area == 'a' or area == 'b'){
        // vamos voltar para o ponto zero
        voltarAreaResgate (area);
    }
}


/********************************     Métodos para os resgatar a vitima ao varrer a area    ***********************************/

// metodo resposável por resgatar a vitima
void Resgate::resgatarVitima (char area){
    // vamos pra frente com o robô e a bolinha
    movimento.roboFrente (1200);
    movimento.roboParar (200);

    if (area == 'a' or area == 'c'){
        movimento.roboVirarEsq (450);
    }else {
        movimento.roboVirarDir (450);
    }

    movimento.roboParar (100);
    movimento.roboVoltar (800);
    alinhar ();
    movimento.roboFrente (1800);
    movimento.roboParar (300);

    // vamos salvar a vitima para o caso A e B
    if (area == 'a' or area == 'c'){
        movimento.roboVirarEsq (630);
    }
    else {
        movimento.roboVirarDir (630);
    }

    movimento.roboVoltar (700);
    alinhar ();

    // giro para ficar de frente com a sala
    movimento.roboFrente (200);
    movimento.roboParar (100);
    movimento.roboVirarDir (880);
    movimento.roboFrente (200);
    soltarBolinha ();
    movimento.roboParar (100);
    movimento.roboVoltar (200);
    movimento.roboVirarDir (1000);
    movimento.roboParar (100);
    alinhar();
}

// método responsável por voltar apos resgatar vitima
void Resgate::voltarAreaResgate (char area){
   if(area != 'b'){
      descerGarra(garra.pegouVitima());
      fecharGarraMovimento(750, 500);
      movimento.roboParar(100);
      garra.subir ();
      movimento.roboParar(100);
      movimento.roboVirarEsq(300);
      movimento.roboParar (100);
      alinhar();
      movimento.roboParar (100);
      descerGarra(garra.pegouVitima());
      fecharGarraMovimento(1900, 1700);
      movimento.roboParar (100);
      garra.subir ();
      movimento.roboParar (100);
      movimento.roboVirarDir(1000);
      movimento.roboParar (100);
      alinhar();
      movimento.roboParar (100);
      movimento.roboFrente(300);
      movimento.roboVirarDir (480);
      alinhar();
   }
   else{
      descerGarra(garra.pegouVitima());
      fecharGarraMovimento(750, 500);
      movimento.roboParar(100);
      garra.subir ();
      movimento.roboParar(100);
      movimento.roboVirarDir(300);
      movimento.roboParar (100);
      alinhar();
      movimento.roboParar (100);
      descerGarra(garra.pegouVitima());
      fecharGarraMovimento(1900, 1700);
      movimento.roboParar (100);
      garra.subir ();
      movimento.roboParar (100);
      movimento.roboVirarDir(1000);
      movimento.roboParar (100);
      alinhar();
      movimento.roboParar (100);
      movimento.roboFrente(300);
      movimento.roboVirarEsq (480);
      alinhar();
   }


}

// método responsável por fazer o robô varrer os cantos e voltar para a posição zero
void Resgate::aposVarrerSala (char area){
    movimento.roboParar(300);
    sinalizar (10);
    movimento.roboFrente(300);

    if (area != 'b'){
        movimento.roboVirarDir (450);
    } else {
        movimento.roboVirarEsq (450);
    }

    this -> alinhar ();
    movimento.roboFrente(300);
    if (area != 'b'){
        movimento.roboVirarEsq (450);
    } else {
        movimento.roboVirarDir (450);
    }

    descerGarra(garra.pegouVitima());
    garra.fecharGarraMovimento(900, 700);
    movimento.roboParar (100);
    garra.subir ();
    movimento.roboParar (100);

    if (area != 'b'){
        movimento.roboVirarDir (270);
    } else {
        movimento.roboVirarEsq (270);
    }

    movimento.roboFrente(800);
    movimento.roboParar (200);
    movimento.roboVirarDir (500);
    movimento.roboParar (200);
    movimento.roboFrente (100);

    if(garra.pegouVitima()){
        movimento.roboFrente (100);
        soltarBolinha ();
        movimento.roboVoltar(200);
    }

    movimento.roboVoltar (100);
    movimento.roboVirarDir (900);
    alinhar ();
    this -> voltarAreaResgate (area);
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
                resgatarVitima (area);
                voltarAreaResgate(area);
                resgatouVitima = true;
            }

            // vamos varrer a sala caso não encontre nenhuma bolinha
            else {
                descerGarra(garra.pegouVitima());
            }

            fecharGarraMovimento(1900, 1500);
            movimento.roboParar (500);
            movimento.roboVoltar (2000);
            alinhar ();
            garra.subir();
            movimento.roboParar (100);

            // vamos verificar se tem bolinha na garra
            if (garra.pegouVitima()){
                sinalizar (5);
                resgatarVitima (area);
                voltarAreaResgate(area);
                resgatouVitima = true;
            }


            // caso não conseguirmos pegar bolinha ao varrer
            // vamos seguir lateralmente
            if (area == 'a' or area == 'c'){
                roboIrLateralEsq ();
            }

            // caso a area de resgate seja B, vamos girar
            // para a direita
            else {
                roboIrLateralDir ();
            }

            // vamos verificar se tem bolinha na garra
            if (garra.pegouVitima()){
                sinalizar (5);
                resgatarVitima (area);
                voltarAreaResgate(area);
                resgatouVitima = true;
            }
        }   // for

        // vamos esta de frente a sala de resgate após varrer a sala 3 vezes
        // executaremos um metodo pra varrer os cantos e voltar ate o ponto zero

        aposVarrerSala (area);
    }       // while
}
