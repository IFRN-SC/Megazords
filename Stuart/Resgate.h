#ifndef RESGATE_H
#define RESGATE_H

#include <robo_hardware2.h>
#include "Garra.h"
#include "Movimento.h"

class Resgate: public Garra {
    private :
        Garra garra;
        Movimento movimento;

    public:
        Resgate ();
        void iniciar ();

    protected:
        void entrarNaSala ();
        bool verificarArea ();
        char identificaZona ();
        void pontoZero (char area);
        void seguirNaSala (char area);
        void sinalizar (int vezes);
        void resgatarVitima (char area); 
        void voltarAreaResgate (char area);
       
        // falta implementar
        void aposVarrerSala (char area);


        // parte do código referente a movimento
        void alinhar ();
        void roboVoltar (int tempo);
        void roboFrente (int tempo);
        void roboParar (int tempo);
        void roboVirarDir (int tempo);
        void roboVirarEsq (int tempo);

        void roboIrLateralEsq ();
        void roboIrLateralDir ();
};

#endif
