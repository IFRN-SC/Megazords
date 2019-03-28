class Movimento{
        #define PNEU_ANDA_ESQ 40
        #define PNEU_ANDA_DIR 43
        #define PNEU_VOLTA_DIR -43
        #define PNEU_VOLTA_ESQ -40

	  public:
        void parar (){
            robo.acionarMotores(0,0);
        }
        
        void girarSoEsquerda(){
            robo.acionarMotores(PNEU_ANDA_ESQ * (-1), 0);
        }
        
        void girarSoDireita (){
            robo.acionarMotores(0, PNEU_ANDA_DIR * (-1));
        }
      
        void seguir (){
            robo.acionarMotores(PNEU_ANDA_ESQ, PNEU_ANDA_DIR);
        }
        
        void voltar (){
            robo.acionarMotores(PNEU_VOLTA_ESQ, PNEU_VOLTA_DIR);
        }
        
        void girarParaEsquerda (){
            robo.acionarMotores(PNEU_VOLTA_ESQ, PNEU_ANDA_DIR);
        }
            
        void girarParaDireita (){
            robo.acionarMotores(PNEU_ANDA_ESQ, PNEU_VOLTA_DIR);
        }
};
