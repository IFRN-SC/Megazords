#ifndef GARRA_H
#define GARRA_H

#include <robo_hardware2.h>

class Garra {
    private :
        #define DELAY 10
        #define SUPER_DELAY 20
        #define ANG_MAO_FECHAR 120
        #define ANG_MAO_ABIR 25
        #define ANG_BRACO_SUBIR 115
        #define ANG_BRACO_BAIXAR 3

    public :
        Garra ();
        void subir();
        void abrir();
        void fechar();
        void baixar();
        void comecar ();


        boolean pegouVitima(){ return (robo.fimDeCursoPressionado1() || robo.fimDeCursoPressionado2());}

        void fecharGarraMovimento (int valMaior, int valMenor);
        void soltarBolinha ();
        void descerGarra (boolean abrir);
};

#endif
