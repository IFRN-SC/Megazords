#include "Resgate.h"
#include "Sensores.h"
#include "Movimento.h"
#include "Calibracao.h"

class Estrategia{
	  private:
        Resgate resgate;
        Sensores sensores;
        Movimento movimento;
        Calibracao cali;
       
    protected:    
        void fazerVerde();
        void subirRampa(); 
      	void seguirLinha();
      	void desviarObstaculo();
     
   	public:
        Estrategia();
        void calibracao();
      	void executar();
};
