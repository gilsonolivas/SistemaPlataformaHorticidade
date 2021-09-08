#include <SoftwareSerial.h>

// Configuração Serial Bluetooth
SoftwareSerial mySerial(10, 11); // RX, TX


// Módulos Sensores ---------------------------------
#define sensorTemperatura 2
#define sensorTDP 3
#define sensorLumi 4
#define sensorPh 5

// Módulos controladores
#define modCorrente 6
#define modRele 7


// Variaveis de Controle -----------------------------
unsigned long regaTempo=60000;
unsigned long regaInter=1800000;
int corrente=1000;

// Valores dos Sensores
int lumi=0;
int temperatura=0;
int tdp=0;
int ph=0;



// Funções Personalizadas --------------------------------
void ligando(int pino) {
  pinMode (pino, OUTPUT);
  digitalWrite (pino, HIGH);
  }
void desligando(int pino) {
  pinMode (pino, OUTPUT);
  digitalWrite (pino, LOW);
  }
int millisCheck(unsigned long interVal) { //arrumei aqui tirei "void" e coloquei "int". Void indica que a função não tem retorno. O int na frente da função indica que ela deve retornar
  //um valor inteiro
  
  unsigned long lastRun = 0;
  unsigned long lapse = 0;
  unsigned long tmpMax = 4294967295;

  // Checa se o millis foi zerado
  if(millis() < lastRun) {
    // Se o millis zerou, ele gera a variavel lapse
    lapse = tmpMax - lastRun;  
    // E zera a variavel lastRun
    lastRun = 0;
  }
  // Checa se chegou a hora de ligar o Rele
  if(millis() + lapse - lastRun >= interVal) {
    //  Renova o lastRun
    lastRun = millis(); // arumei aqui  estava millis e tinha que ser millis() que chama a função millis().
    //  Zera a variavel auxiliar, se estiver ativa
    if(lapse != 0){
    lapse = 0;
    }
    //  Retorna 1, ativo
    return 1;
  }
  //Se não atingiu o intervalo, retorna 0, inativo
  else {
    return 0;
  }
}


// Inicialização do programa -------------------------------
void setup () {

  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");  

pinMode (sensorTemperatura, INPUT);
pinMode (sensorTDP, INPUT);
pinMode (sensorLumi, INPUT);
pinMode (sensorPh, INPUT);
pinMode (modCorrente, OUTPUT);
pinMode (modRele, OUTPUT);

}



// Rotinas 
void loop() {

  // Checa a hora de ligar
  if (millisCheck(regaInter) == 1){ //arrumei aqui coloquei "==" ao invés de "="
    ligando(modRele);
  }

  // Aguarda o intervalo, desliga e retorna ao loop
  if (modRele == HIGH){ // coloquei "==" ao invés de "=". O "==" é no sentido de comparar uma coisa com outra. O "=" é atribuição de valor, tipo: a = 5, diz que a variavel "a" recebe 5
    mySerial.println("Irrigando");
    delay(regaTempo);
    mySerial.println("Rega Concluída");
    desligando(modRele);// PIN1 nao está definido no programa. Mudei para modRele. Depois dá uma conferida
    
  }

  else {
    mySerial.println("Que lindo dia!");
  }
  
}
