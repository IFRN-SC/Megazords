#include "Sensores.h"
#include "Movimento.h"
#include "Calibracao.h"

class Estrategia{

	private:
  Sensores sensores;
  Movimento movimento;
  Calibracao cali;
  
	void seguirLinha();
	void desviarObstaculo();
	void identificarVerde();
	void subirRampa(); 
	void calibracao();

	public:
	void executar();
};
