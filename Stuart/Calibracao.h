#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware2.h>

class Calibracao{    
    protected:       
        int mediaEsquerdo;
        int mediaDireito;
        int mediaMaisDireito;
        int mediaMaisEsquerdo;
        float cor_direito, cor_esquerdo;
  
    public:
        Calibracao(); 
        void menuCor();
        void menuCalibrar();
        int dadosCalibracao();
    private:
        int caliPretoEsquerdo, caliPretoMaisEsquerdo, caliPretoDireito, caliPretoMaisDireito;
        int caliBrancoEsquerdo, caliBrancoMaisEsquerdo, caliBrancoDireito, caliBrancoMaisDireito; 
        calibracao_dados cd;
        float verdeDir, verdeEsq, brancoDir,brancoEsq;
        void salvaCalibracao(calibracao_dados);
};

#endif
