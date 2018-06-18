class Movimento{
  #define PNEU_ANDA 35
  #define PNEU_VOLTA -35

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
  

  int girarSoEsquerda(){
    robo.acionarMotores(-30, 0); 
  }
  int girarSoDireita(){
    robo.acionarMotores(0, -30); 
  }
};
