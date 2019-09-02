#ifndef RESGATE_H
#define RESGATE_H

#include <robo_hardware2.h>
#include "Garra.h"

class Resgate: public Garra {

    #define DELAY_DIR 480  // constante para o giro 90º para a direita
    #define DELAY_ESQ 480  // constante para o giro 90º para a esquerda    

    private :
        Garra garra;

    public:
        Resgate ();
        void iniciar ();
        
    protected :
        char entrar ();
        void alinhar ();

        char identificarZona (char area);
        bool verificaSonarArea (char area);
        void sinalizar (int vezes);
        
        bool verificaVitimaGarra (); 
        void soltarBolinha ();
    
    
    /*
    private :
        Garra garra;
    
    protected: 
        void alinhar ();
        void entrarNaSala ();
        void soltarBolinha ();
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
