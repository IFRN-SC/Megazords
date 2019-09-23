class Movimento{
     
     #define PNEU_ANDA_ESQ 44
     #define PNEU_ANDA_DIR 40
     #define PNEU_VOLTA_DIR -40
     #define PNEU_VOLTA_ESQ -44

     public:
	 void seguir (){
	     robo.acionarMotores(PNEU_ANDA_ESQ, PNEU_ANDA_DIR);
	 }

	 void voltar (){
	     robo.acionarMotores(PNEU_VOLTA_ESQ, PNEU_VOLTA_DIR);
	 }

	 void parar (){
	     robo.acionarMotores(0,0);
	 }

	 void girarSoEsquerda(){
	     robo.acionarMotores(-30, 0);
	 }

	 void girarSoDireita (){
	     robo.acionarMotores(0, -30);
	 }

	 void girarParaEsquerda (){
	     robo.acionarMotores(PNEU_VOLTA_ESQ, PNEU_ANDA_DIR);
	 }

	 void girarParaDireita (){
	     robo.acionarMotores(PNEU_ANDA_ESQ, PNEU_VOLTA_DIR);
	 }
};
