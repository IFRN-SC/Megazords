#include "Sensores.h"
#include "Movimento.h"

class Estrategia{

	private:
  Sensores sensores;
  Movimento movimento;
  
	void seguirLinha();
	void desviarObstaculo();
	void identificarVerde();
	void subirRampa(); 
	void calibracao();

	public:
	void executar();
};
