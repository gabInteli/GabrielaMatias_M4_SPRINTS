#include <iostream>
#include <string>
#include <limits.h>
#include <math.h>

 
// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor

using namespace std;

int ajuste(){
  float medida;
  float val_min;
  float val_max;
  
  cout << "Indique um valor" << endl;
  cin >> medida; 

  cout << "Indique um valor minimo:" << endl;
  cin >> val_min;

  cout << "Indique um valor maximo:" << endl;
  cin >> val_max;
  
  float resultado; //Indica a porcentagem em que o valor medida esta posicionado entre o minimo e o maximo.

  resultado = (medida - val_min) / (val_max - val_min);
  cout << resultado << endl;
  return 0;
};


// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna e ste valor

float leitura(){ 
  float valor;
	
  cout << "Entrada do Sensor:" << endl;
  cin >> valor;
  cout << valor << endl;
  return 0;
}

// 3 - Faça uma função que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C não possui vetores 
// nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em 
// uma área de memória fora do vetor

int vetores(int val_max, int val_final, int vetor[]){
  int prox_valor;
  int medida;

  cout << "Indique um valor:" << endl;
	cin >> medida;
  
	prox_valor = val_final + 1;
	if((medida) > val_max){
		cout << "Erro:" << endl;
    cout << "Valor Maximo:" << endl;
    cout << val_max << endl;
    cout << "Ultima Posição:" << endl;
    cout << val_final << endl;
    
	} else {
		vetor[prox_valor] = medida;
	}

  cout << vetor << endl;
	return 0;
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém 
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção 
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda é esta maior distância.




// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso

bool mapeamento(){
  bool verificacao;
  cout << "Ola, gostariamos de saber se você deseja continuar o mapeamento" << endl;
  cout << "Orientações: \n 0 - sim  \n 1 - nao"<< endl;
  cout << "Gostaria de Continuar?"<<endl;
  cin >> verificacao;
  
  if(verificacao == 1){
    cout << "O mapeamento irá continuar"<<endl;
  }
  else{
    cout << "O mapeamento será encerrado"<<endl;
  }
  return 0;
}

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô 
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
//      Complete a função com a chamada das funções já criadas
int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){		
		int medida = /// .. Chame a função de de leitura da medida para a "Direita"
		medida = converteSensor(medida,0,830);
		posAtualVetor = // Chame a função para armazenar a medida no vetor
        ///////////////////////////////////////////////////////////////////////////		
		// Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
		// ................
		///////////////////////////////////////////////////////////////////////////
		dirigindo = leComando();		
	}
	return posAtualVetor;
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}