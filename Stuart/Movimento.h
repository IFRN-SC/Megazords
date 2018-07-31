class Movimento{
  #define PNEU_ANDA 40
  #define PNEU_VOLTA -40
  #define PNEU_ANDA_OBSTACULO 40
  #define PNEU_VOLTA_OBSTACULO -40

	public:
	
	void seguir(){
		robo.acionarMotores(PNEU_ANDA, PNEU_ANDA);
	}
	void girarParaEsquerda(){
		robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
	}
  void girarParaDireita(){
    robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA);
  }
  void parar(){
    robo.acionarMotores(0,0);
  }
  void voltar(){
    robo.acionarMotores(PNEU_VOLTA, PNEU_VOLTA);
  }
  

  void girarSoEsquerda(){
    robo.acionarMotores(-25, 0); 
  }
  void girarSoDireita(){
    robo.acionarMotores(0, -25); 
  }
  void seguirOb(){
    robo.acionarMotores(PNEU_ANDA_OBSTACULO, PNEU_ANDA_OBSTACULO);
  }
  void girarParaEsquerdaOb(){
    robo.acionarMotores(PNEU_VOLTA_OBSTACULO, PNEU_ANDA_OBSTACULO);
  }
  void girarParaDireitaOb(){
    robo.acionarMotores(PNEU_ANDA_OBSTACULO, PNEU_VOLTA_OBSTACULO);
  }
};
