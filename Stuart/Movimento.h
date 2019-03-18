class Movimento{
  #define PNEU_ANDA 40
  #define PNEU_VOLTA -40

	public:
	
	int seguir(){
		robo.acionarMotores(PNEU_ANDA, PNEU_ANDA);
	}
	int girarParaEsquerda(){
		robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
	}
  int girarParaDireita(){
    robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA);
  }
  int parar(){
    robo.acionarMotores(0,0);
  }
  int voltar(){
    robo.acionarMotores(PNEU_VOLTA, PNEU_VOLTA);
  }
  

  int girarSoEsquerda(){
    robo.acionarMotores(-20, 0); 
  }
  int girarSoDireita(){
    robo.acionarMotores(0, -20); 
  }
};
