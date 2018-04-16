#include "Sensores.h"

class Estrategia{

	private:
  Sensores sensores;
  
	void seguirLinha();
	void desviarObstaculo();
	void identificarVerde();
	void subirRampa(); 
	void calibracao();

	public:
	void executar();
};
