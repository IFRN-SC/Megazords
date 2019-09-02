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

        void voltarZero (char zona, char area);

        void voltar (char zona, char area);
        void restoDosCantos (char zona, char area);
        char identificarZona (char area);
        bool verificaSonarArea (char area);
        void sinalizar (int vezes);
        
        bool verificaVitimaGarra (); 
        void soltarBolinha ();

        // método responsável por varrer a sala 3
        void varrerSala (char zona, char area);

        void resgatarVitima (char zona, char area);

        void irLateralDir (char area);
        void irLateralEsq (char area);
};

#endif
