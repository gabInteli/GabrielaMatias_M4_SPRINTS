// All definitions here
#define LDR_PIN 2
#define BUTTON1_PIN 36
#define BUTTON2_PIN 35
#define BUZZER_PIN 17
#define LED_VERDE 5
#define LED_AMARELO 6
#define LED_BRANCO 7
#define LED_VERMELHO 15

//Posição inicial da lista
int i = 0; 
//Quantidade de elementos que serão armazenados
int quantidade = 15;
//Lista de Armazenamento 
int armazenamento[30];
//Valores para binarios
int binary[4] = {0,0,0,0};
//Possibilidades de som do Buzzer 
int tones[15]; 
int frequencies[15] = { 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217 }; 

//Função para definir valor inteiro (0,15) para as possibilidades de leitura do ldr
int intValueConvert(int value){
    int result = value/273;
    return result;
}

int convertBinario(int value){
  for (int i = 3; i>=0; i--){
    binary[i]= value%2;
    value = value/2;      
  }    
}

void addToList(){
    for(int n = i; n>=0; n++){
       armazenamento[i] =  binary[n-1];
    }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_BRANCO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);  
  pinMode(LDR_PIN, INPUT);
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  
}

void loop() {
  int valueButton1 = digitalRead(BUTTON1_PIN);
  int valueButton2 = digitalRead(BUTTON2_PIN);
    
    if(valueButton1 == 1){
      delay(200);
      int readLDR = analogRead(LDR_PIN);
      readLDR = intValueConvert(readLDR);
      convertBinario(readLDR);
      tones[i] = frequencies[readLDR];
      for(int n = 0; n<4; n++){
        if(binary[n]==1){
          digitalWrite(LED_VERMELHO, 1);
        }
        if(binary[n+1]==1){
          digitalWrite(LED_BRANCO, 1);
        }
        if(binary[n+2]==1){
          digitalWrite(LED_AMARELO, 1);
        }
        if(binary[n+3]==1){
          digitalWrite(LED_VERDE, 1);
        }
        tone(BUZZER_PIN, tones[i]);
        delay(200);
        tone(BUZZER_PIN, 0); 
        digitalWrite(LED_VERMELHO, 0);     
        digitalWrite(LED_BRANCO, 0);
        digitalWrite(LED_AMARELO, 0);
        digitalWrite(LED_VERDE, 0);         
      }   
      addToList();           
      i++;  
    }

    if(valueButton2 == 1){
      delay(500);      
      //Reinicialização da variavel i 
      i = 0; 
      //Varredura de itens da lista de elementos binarios 
      for(int n = 0; n < quantidade;i = i+4){
        if(armazenamento[n]==1){
          digitalWrite(LED_VERMELHO, 1);
        }
        if(armazenamento[n+1]==1){
          digitalWrite(LED_BRANCO, 1);
        }
        if(armazenamento[n+2]==1){
          digitalWrite(LED_AMARELO, 1);
        }
        if(armazenamento[n+3]==1){
          digitalWrite(LED_VERDE, 1);
        }
        tone(BUZZER_PIN, tones[i]);
        delay(200);
        tone(BUZZER_PIN, 0); 
        digitalWrite(LED_VERMELHO, 0);     
        digitalWrite(LED_BRANCO, 0);
        digitalWrite(LED_AMARELO, 0);
        digitalWrite(LED_VERDE, 0);
        i++        
;      }

        for(int j = 0; j< quantidade*2; j++){
            armazenamento[j] = 0; 
        }
        
        for(int j = 0; j<quantidade; j++){
            tones[j] = 0; 
        }
        i = 0;        
    }
}