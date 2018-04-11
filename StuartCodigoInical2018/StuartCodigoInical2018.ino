  
#include <robo_hardware2.h> 
#include <Servo.h>

//********PINOS PARA SENSORES REFLETANCIA***********//
//
//SENSOR_LINHA_MAIS_ESQUERDO            A0
//SENSOR_LINHA_ESQUERDO			            A1
//SENSOR_LINHA_DIREITO			            A3
//SENSOR_LINHA_MAIS_DIREITO	            A2
//
//*********PINOS PARA SENSORES REFLETANCIA*********//

#define PNEU_ANDA 45
#define PNEU_VOLTA -40

float valor_sensor_dir;
float valor_sensor_mais_dir;
float valor_sensor_esq;
float valor_sensor_mais_esq;

// VARIAVEIS DE CALIBRACAO

int caliPretoEsquerdo, caliPretoMaisEsquerdo, caliPretoDireito, caliPretoMaisDireito;
int caliBrancoEsquerdo, caliBrancoMaisEsquerdo, caliBrancoDireito, caliBrancoMaisDireito; 
int mediaEsquerdo = 45;
int mediaDireito = 45;
int mediaMaisDireito = 45;
int mediaMaisEsquerdo = 45;

// Mostra os valores do branco dos sensores de refletancia

void calibracao(){
  char controle = 't';
  Serial.println("CALIBRE BRANCO");
  while(1){
    Serial.print("MAIS ESQUERDO : ");
    Serial.print(robo.lerSensorLinhaMaisEsq());
    Serial.print("  ||  ESQUERDO : ");
    Serial.print(robo.lerSensorLinhaEsq());
    Serial.print("  ||  DIREITO : ");
    Serial.print(robo.lerSensorLinhaDir());
    Serial.print("  ||  MAIS DIREITO : ");
    Serial.println(robo.lerSensorLinhaMaisDir());
    
 // Verifica se o testador  quer terminar ou não a calibração para esse sensor
     
    if(Serial.available()){
       controle = Serial.read();
       if(controle == 's'){
         controle = 't';
         caliBrancoEsquerdo = robo.lerSensorLinhaEsq();
         caliBrancoMaisEsquerdo = robo.lerSensorLinhaMaisEsq();
         caliBrancoDireito = robo.lerSensorLinhaDir();
         caliBrancoMaisDireito = robo.lerSensorLinhaMaisDir(); 
         break;
       }
     }
    delay(500);  
  }
// Mostra os valores do preto do sensor de refletancia mais esquerdo

  Serial.println("CALIBRE PRETO MAIS ESQUERDO");
  while(1){
     Serial.print("MAIS ESQUERDO : ");
     Serial.println(robo.lerSensorLinhaMaisEsq());
     if(Serial.available()){
      controle = Serial.read();
      if(controle == 's'){
       controle = 't';
       caliPretoMaisEsquerdo = robo.lerSensorLinhaMaisEsq();
       break;
      } 
     } 
     delay(500);
   }
  Serial.println("CALIBRE PRETO ESQUERDO");
  while(1){
    Serial.print("ESQUERDO : ");
    Serial.println(robo.lerSensorLinhaEsq());
    if(Serial.available()){
       controle = Serial.read();
      if(controle == 's'){
       controle = 't';
       caliPretoEsquerdo = robo.lerSensorLinhaEsq();
       break; 
      }
    }
    delay(500);
  }
   
    Serial.println("CALIBRE PRETO DIREITO");
  while(1){
    Serial.print("DIREITO : ");
    Serial.println(robo.lerSensorLinhaDir());
    if(Serial.available()){
       controle = Serial.read();
      if(controle == 's'){
       controle = 't';
       caliPretoDireito = robo.lerSensorLinhaDir();
       break;
      } 
    }
    delay(500);
  }
   Serial.println("CALIBRE PRETO MAIS DIREITO");
  while(1){
    Serial.print("MAIS DIREITO : ");
    Serial.println(robo.lerSensorLinhaMaisDir());
    
    if(Serial.available()){
       controle = Serial.read();
      if(controle == 's'){
         controle = 't';
         caliPretoMaisDireito = robo.lerSensorLinhaMaisDir();
         break; 
      }
    }
    delay(500);  
  }

  // Faz a média de acordo com os valores "capturados"
  
  mediaEsquerdo = (caliBrancoEsquerdo + caliPretoEsquerdo) / 2;
  mediaMaisEsquerdo = (caliBrancoMaisEsquerdo + caliPretoMaisEsquerdo) / 2;
  mediaDireito = (caliBrancoDireito + caliPretoDireito) / 2;
  mediaMaisDireito = 45;

  Serial.println(" ");
  // Imprime os valores das médias
  Serial.println("Valores finais: ");
  Serial.print("MAIS ESQUERDO : ");
    Serial.print(mediaMaisEsquerdo);
    Serial.print("  ||  ESQUERDO : ");
    Serial.print(mediaEsquerdo);
    Serial.print("  ||  DIREITO : ");
    Serial.print(mediaDireito);
    Serial.print("  ||  MAIS DIREITO : ");
    Serial.println(mediaMaisDireito);
    
  Serial.println(".");
  Serial.println(".");
  Serial.println(".");
  // Espera conectar o Jumper para o robo poder funcionar
  Serial.println("ESPERANDO JUMPER ");
  

}

// Funcoes para o branco

bool ehBrancoMaisEsquerdo(){
  return (valor_sensor_mais_esq > mediaMaisEsquerdo);
} 
bool ehBrancoEsquerdo(){
  return (valor_sensor_esq > mediaEsquerdo);
}
bool ehBrancoDireito(){
  return (valor_sensor_dir > mediaDireito);
}
bool ehBrancoMaisDireito(){
  return (valor_sensor_mais_dir > mediaMaisDireito);
}

// Funcoes para condicoes

boolean branco_branco_branco_branco(){
  return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito());  //BBBB
}
boolean preto_branco_branco_branco(){
  return (!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito()); //PBBB
}
boolean branco_branco_branco_preto(){
  return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && ehBrancoDireito() && !ehBrancoMaisDireito()); //BBBP
}
boolean branco_branco_preto_branco(){
  return (ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito()); //BBPB
}
boolean branco_preto_branco_branco(){
  return (ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito()); //BPBB
} 

// Condicao para acionar os motores inicialmente

void setup(){
  Serial.begin(9600);
  
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  robo.configurar(false);
  calibracao();
  while(!digitalRead(8)){}
  robo.acionarMotores(0,0);
  delay(2000);
}

void loop(){

  if(digitalRead(8) == HIGH){
    // ler os valores dos sensores. Cada sensor retornar um valor de 0 100
        
    valor_sensor_esq = robo.lerSensorLinhaEsq();
	  valor_sensor_dir = robo.lerSensorLinhaDir();
    
    valor_sensor_mais_esq = robo.lerSensorLinhaMaisEsq();
    valor_sensor_mais_dir = robo.lerSensorLinhaMaisDir();

      
    if(branco_preto_branco_branco()){                     //BPBB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
    }else if(branco_branco_preto_branco()){               //BBPB
      robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA);
    }else if(branco_branco_branco_preto()){               //BBBP
      robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA);
    }else if(preto_branco_branco_branco()){               //PBBB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
    }else if(branco_branco_branco_branco()){              //BBBB
      robo.acionarMotores(PNEU_ANDA, PNEU_ANDA);
    }else{  
    robo.acionarMotores(0,0);  
  }
 }      
}
/*
    }else if(!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && ehBrancoDireito() && ehBrancoMaisDireito()){       //PPBB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
      delay(200);
    }else if(!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito()){      //PPPB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
      delay(200);
    }else if(ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito()){       //BBPP
      robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA);
      delay(200);
    }else if(ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && !ehBrancoMaisDireito()){      //BPPP
      robo.acionarMotores(PNEU_ANDA, PNEU_VOLTA);
      delay(200);
    }else if(!ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito()){      //PPPB
      robo.acionarMotores(PNEU_VOLTA, PNEU_ANDA);
      delay(200);
    }else if(!ehBrancoMaisEsquerdo() && ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito()){       //PBPB
      robo.acionarMotores(PNEU_VOLTA, PNEU_VOLTA); 
    }else if(ehBrancoMaisEsquerdo() && !ehBrancoEsquerdo() && !ehBrancoDireito() && ehBrancoMaisDireito()){       //BPPB
      robo.acionarMotores(PNEU_VOLTA, PNEU_VOLTA); 
*/      
