int led1 = 2;
int led2 = 42;
int led3 = 40;
int led4 = 38;
int buzzer = 19;
int button1 = 6;
int button2 = 5;
int ldr = 10;
int full = false;
int binary[4];
const int binariesCount = 10; 
int binaries[binariesCount*4];
int buzzerSounds[binariesCount];
int buzzerIndex = 0;
int n = 0;

void addToBinaries() {
  for (int i = n; i < n+4; i++) {
    binaries[i] = binary[i-n];
  }
}

void convertBinary(int n) {
  int aux;
  for (int i = 3; i >= 0; i--) {
    binary[i] = n % 2;
    n = n / 2;
  }
  // VISIBILIDADE
  for (int element : binary) {
    Serial.print(element);
    Serial.print(" ");
  }
  Serial.print("\n");
  // FIM
}

int convertValue(int n) {
  return n / 259;
}

void setup() {

  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(ldr, INPUT);

}

void loop() {
  int button1Value = digitalRead(button1);
  int button2Value = digitalRead(button2);

  if (button1Value == 1 and full == false) {

    delay(1000);
    int ldrValue = analogRead(ldr);
    ldrValue = convertValue(ldrValue); 
    
    // VISIBILIDADE
    Serial.println(ldrValue);
    // FIM

    convertBinary(ldrValue);
    if (binary[0] == 1) {
      digitalWrite(led1, HIGH);
    }
    if (binary[1] == 1) {
      digitalWrite(led2, HIGH);
    }
    if (binary[2] == 1) {
      digitalWrite(led3, HIGH);
    }
    if (binary[3] == 1) {
      digitalWrite(led4, HIGH);
    }

    buzzerSounds[buzzerIndex] = ldrValue * 300;
    tone(buzzer, buzzerSounds[buzzerIndex]);
    buzzerIndex++;
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    tone(buzzer, 0);
    addToBinaries();
    n += 4;
    if (n == binariesCount*4) {
      full = true;
    }

    // VISIBILIDADE
    for (int element : binaries) {
    Serial.print(element);
    Serial.print(" ");
    }
    Serial.print("\n");
    Serial.print("\n");
    // FIM
    Serial.print("\n");
    for (int element : buzzerSounds) {
      Serial.print(element);
      Serial.print(" ");
      }
      Serial.print("\n");
      Serial.print("\n");
      // FIM
      Serial.print("\n");
  }
  if (button2Value == 1) {

    delay(1000);
    buzzerIndex = 0;
    int playIndex = 0;
    for (int n = 0; n <= binariesCount; n++) {

      if (binaries[playIndex] == 1) {
        digitalWrite(led1, HIGH);
      }
      if (binaries[playIndex+1] == 1) {
        digitalWrite(led2, HIGH);
      }
      if (binaries[playIndex+2] == 1) {
        digitalWrite(led3, HIGH);
      }
      if (binaries[playIndex+3] == 1) {
        digitalWrite(led4, HIGH);
      }

      tone(buzzer, buzzerSounds[buzzerIndex]);

      buzzerIndex++;
      playIndex += 4;

      delay(500);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      tone(buzzer, 0);
      }
    for (int i = 0; i < binariesCount*4; i++) {
      binaries[i] = 0;
    }
    for (int i = 0; i < binariesCount; i++) {
      buzzerSounds[i] = 0;
    }
    for (int element : binaries) {
      Serial.print(element);
      Serial.print(" ");
    }
    Serial.print("\n");
    for (int element : buzzerSounds) {
      Serial.print(element);
      Serial.print(" ");
    };
    Serial.print("\n");
    buzzerIndex = 0;
    n = 0;
    }
  }