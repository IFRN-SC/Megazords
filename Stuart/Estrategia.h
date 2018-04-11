#include "Sensores.h"

class Estrategia{

	private:
	void seguirLinha();
	void desviarObstaculo();
	void identificarVerde();
	void subirRampa(); 
	void calibracao();

	public:
	void executar();
};
