class Movimento{
  #define PNEU_ANDA_ESQ 44
  #define PNEU_ANDA_DIR 40
  #define PNEU_VOLTA -40

	public:
	
	void seguir(){robo.acionarMotores(PNEU_ANDA_ESQ, PNEU_ANDA_DIR);}
 
	void girarParaEsquerda(){robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA_DIR);}
 
  void girarParaDireita(){robo.acionarMotores(PNEU_ANDA_ESQ, PNEU_VOLTA);}
  
  void parar(){robo.acionarMotores(0,0);}
  
  void voltar(){robo.acionarMotores(PNEU_VOLTA, PNEU_VOLTA);}
  
  void girarSoEsquerda(){robo.acionarMotores(-25, 0);}
  
  void girarSoDireita(){robo.acionarMotores(0, -25);}
};
