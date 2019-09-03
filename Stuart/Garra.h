#ifndef GARRA_H
#define GARRA_H

#include <robo_hardware2.h>

class Garra {
    private :
        #define DELAY 10
        #define ANG_MAO_FECHAR 83
        #define ANG_MAO_ABIR 5
        #define ANG_BRACO_SUBIR 110
        #define ANG_BRACO_BAIXAR 7 
        
    public :
        Garra ();
        void subir();
        void abrir();
        void fechar();
        void baixar();

        void fecharGarraMovimento (int valMaior, int valMenor);

        
};

#endif
