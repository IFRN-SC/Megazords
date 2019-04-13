#ifndef RESGATE_H
#define RESGATE_H

#include <robo_hardware2.h>
#include "Garra.h"

class Resgate: public Garra {
    private :
        Garra garra;
    
    protected: 
        void alinhar ();
        void entrarNaSala ();
        void soltarBolinha ();
        void identificaZona ();
 
        bool verificaArea ();
        void irLateralDir ();
        void irLateralEsq ();

        void voltar (char zona);
        void seguirNaSala (char zona);      
        void resgatarVitima (char zona);
        
    public :
        Resgate ();
        void iniciar ();
};

#endif
