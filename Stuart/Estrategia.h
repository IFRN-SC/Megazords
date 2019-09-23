#include "Resgate.h"
#include "Sensores.h"
#include "Movimento.h"
#include "Calibracao.h"
#include "Garra.h"

class Estrategia{
    private:
        Garra garra;
        Resgate resgate;
        Sensores sensores;
        Movimento movimento;
        Calibracao cali;
       
    protected:    
        void alinharCurva();
        boolean fazerVerde();
        void girarVerdeEsq();
        void girarVerdeDir();
        void girarVerdeBeco();
        void subirRampa(); 
      	void seguirLinha();
      	void desviarObstaculo();
     
    public:
        Estrategia();
      	void executar();
        void calibracao();
};
