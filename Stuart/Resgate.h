#ifndef RESGATE_H
#define RESGATE_H

#include <robo_hardware2.h>
#include "Garra.h"

class Resgate: public Garra {
    private:
        Garra garra;
      
    public:
		    Resgate();
        char zona = 'd';  
	    	char indentificaZona ();
	    	void areaResgate ();     
	      void alinharRobo ();
        void entrarNaSala ();
        void seguirNaSala ();   
        void seguirLateral();
};

#endif