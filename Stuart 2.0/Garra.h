#ifndef GARRA_H
#define GARRA_H

#include <robo_hardware2.h>

class Garra {

    private :
        #define DELAY 20
        #define ANG_MAO_FECHAR 90
        #define ANG_MAO_ABIR 0
        #define ANG_BRACO_SUBIR 180
        #define ANG_BRACO_BAIXAR 90
   
   
    public :
        Garra ();
        void subir();
        void abrir();
        void fechar();
        void baixar();     
};

#endif