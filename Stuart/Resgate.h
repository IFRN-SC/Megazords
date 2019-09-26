#ifndef RESGATE_H
#define RESGATE_H

#include <robo_hardware2.h>
#include "Garra.h"

class Resgate: public Garra {
    private :
        Garra garra;

    public:
        Resgate ();
        void iniciar ();

    private:
        void entrarNaSala ();
        bool verificarArea ();
        char identificaZona ();
        void pontoZero (char area);


        void sinalizar (int vezes);
        



 
        // parte do código referente a movimento
        void alinhar ();
        void roboVoltar (int tempo);
        void roboFrente (int tempo);
        void roboParar (int tempo);

        /*
    
    protected: 
        void alinhar ();
        void entrarNaSala ();
        char identificaZona ();
        void voltarZero(char zona);
 
        void irLateralDir ();
        void irLateralEsq ();
        bool verificarArea ();
 
        void voltar (char zona);
        void seguirNaSala (char zona);      
        void resgatarVitima (char zona);
        void restoDosCantos (char zona);
        
    public :
        Resgate ();
        void iniciar ();*/
};

#endif
