#include <Arduino.h>
#include <string.h>

#define LED_ROSU 6 // LED roșu conectat la pinul 6
#define LED_VERDE 5 // LED verde conectat la pinul 5
#define LED_ALBASTRU 4 // LED albastru conectat la pinul 4
#define BUTON_START 3 // Butonul de start conectat la pinul 3
#define BUTON_DIFICULTATE 2 // Butonul de dificultate conectat la pinul 2
#define DICTIONARY_SIZE 20 // Dimensiunea dicționarului (numărul de cuvinte)

// Variabile pentru starea jocului
bool jocul_a_inceput = false; // Starea jocului (dacă a început sau nu)
bool buton_Start = 1; // Starea butonului de start
int word_interval = 10000; // Intervalul de timp per cuvânt, în milisecunde
bool runda_a_inceput = false; // Starea rundei (dacă a început sau nu)
bool greseala; // Starea pentru eroare
int dificultate = 1; // Nivelul de dificultate (1 - ușor, 2 - mediu, 3 - dificil)
int currentMillis = millis(); // Timpul curent în milisecunde
int currentWord = 0; // Indexul cuvântului curent în dicționar
int previousMillis = currentMillis; // Timpul anterior pentru acțiuni generale
int previousWordMillis = currentMillis; // Timpul anterior pentru afișarea cuvântului
bool dificultate_schimbata = false; // Indicator pentru schimbarea dificultății
unsigned int Current_letter = 0; // Indexul literei curente în cuvânt
int scor = 0; // Scorul jucătorului
bool selectare_dificultate = false; // Indicator pentru afișarea mesajului de selectare a dificultății

// Lista de cuvinte folosită în joc
const char* dictionary[DICTIONARY_SIZE] = {
    "carte", "vraja", "minge", "frunza", "calatorie", "prietenie", 
    "floare", "zambet", "vreme", "culoare", "cer", "lumina", 
    "zbor", "poveste", "dragoste", "anihilare", "indignare", 
    "cirese", "turbina", "finisaj"
};

// Funcția pentru a schimba starea butonului de start
void schimba_buton_start() {
  buton_Start = !buton_Start; // Inversează starea butonului de start
}

// Funcția pentru a schimba nivelul de dificultate
void schimba_dificultate() {
  dificultate_schimbata = true; // Setează indicatorul de schimbare a dificultății
  dificultate++; // Crește dificultatea cu o unitate
  if (dificultate > 3) // Dacă dificultatea trece de nivelul 3
    dificultate = 1; // Revine la nivelul 1 (ușor)
}

// Funcția pentru a porni jocul
void startGame() {
  if (!jocul_a_inceput) { // Dacă jocul nu a început deja
    jocul_a_inceput = true; // Marchează jocul ca pornit
    int currentMillis = millis(); 
    int previousMillis = currentMillis;
    int previousMillis2 = currentMillis;

    // Pornește toate LED-urile (alb)
    digitalWrite(LED_ROSU, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ALBASTRU, HIGH);
    char numarator_invers = '2'; // Numărătoare inversă de la 3 la 1
    Serial.println("3\n");
    while (currentMillis - previousMillis < 3000) { // Timp de numărătoare inversă (3 secunde)
      currentMillis = millis();
      if (currentMillis - previousMillis2 >= 1000 && numarator_invers != '0') { // daca a trecut o secunda
        Serial.print(numarator_invers); // Afisam secunda 2 si 1
        Serial.println("\n");

        numarator_invers--; // Scade numărătoarea
        previousMillis2 = currentMillis;
      }
     
      // Face LED-urile să pâlpâie în timpul numărătorii inverse
      digitalWrite(LED_ROSU, !digitalRead(LED_ROSU));
      digitalWrite(LED_VERDE, !digitalRead(LED_VERDE));
      digitalWrite(LED_ALBASTRU, !digitalRead(LED_ALBASTRU));
      delay(500); // Întârziere de 500 ms pentru pâlpâire
    }

    // Setează LED-ul verde pentru a indica începutul rundei
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROSU, LOW);
    digitalWrite(LED_ALBASTRU, LOW);
    randomSeed(millis()); // Inițializează generatorul de numere aleatoare

    // Amestecă cuvintele din dicționar aleatoriu
    for (int i = DICTIONARY_SIZE - 1; i > 0; i--) {

        
      int r = random(i + 1); // Obține un index aleatoriu
        
      const char* t = dictionary[i];
        
      dictionary[i] = dictionary[r];
        
      dictionary[r] = t;
    }

    currentWord = 0; // Resetează indexul cuvântului
    scor = 0; // Resetează scorul
  }
}

// Funcția pentru a gestiona o rundă
void round_f() {

  if (runda_a_inceput) { // Dacă runda a început
    if (currentMillis - previousMillis < 30000) { // Runda durează 30 de secunde
      currentMillis = millis();
      bool jumpword = false; // Indicator pentru sărit peste cuvânt (initial false)

      if (Serial.available() > 0) { // Verifică dacă există intrare serială
      //De aici se verifica corectitudinea cuvantului

        char litera = Serial.read(); // Citește o literă
        if (litera == 8) { // Dacă s-a apăsat Backspace
          greseala = false; // Resetează starea de eroare
          Serial.println("Backspace was pressed!");
          
        } 

        else if (litera == dictionary[currentWord - 1][Current_letter] && !greseala) { // Verifică dacă litera e corectă și nu există eroare
          Serial.println("Correct! : " + String(litera));
          Current_letter++; // Treci la următoarea literă

          if (Current_letter == strlen(dictionary[currentWord - 1])) { // Dacă s-a terminat cuvântul
            Serial.println("Word finished! : " + String(dictionary[currentWord - 1]));
            scor++; // Crește scorul
            jumpword = true; // Indicator pentru cuvânt finalizat
            Current_letter = 0; 
            currentWord++;

            if (currentWord >= DICTIONARY_SIZE) { // Dacă s-au parcurs toate cuvintele din dicționar
              currentWord = 0; // Reia de la început
            }
            
            previousWordMillis = currentMillis;
          }
        } 

        
        else {       //litera nu este corecta
          Serial.println("Wrong! : " + String(litera) + " Was expecting: " + String(dictionary[currentWord - 1][Current_letter]));
          greseala = true; // Setează indicatorul de eroare
        }
      }


      

      if (currentWord == 0) { // Afișează primul cuvânt
        Serial.println(dictionary[currentWord]);
        currentWord++;
        previousWordMillis = currentMillis;
      } 
          
      
      else if (currentMillis - previousWordMillis >= word_interval || jumpword) { // Sarim peste cuvant daca e finalizat sau a expirat timpul
        Serial.println(dictionary[currentWord]);

        previousWordMillis = currentMillis;
        currentWord++;
        Current_letter = 0;
        greseala = false; // Resetează indicatorul de eroare
      }
        
    } 
    else {
      // Sfârșitul rundei
      runda_a_inceput = false;
      greseala = false;

      Serial.println("Round finished!");
      Serial.println("score: " + String(scor));

      previousWordMillis = currentMillis;
    }
  }
}

// Funcția de configurare pentru a inițializa pinii și întreruperile
void setup() {
  pinMode(LED_ROSU, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ALBASTRU, OUTPUT);
  pinMode(BUTON_START, INPUT_PULLUP);
  pinMode(BUTON_DIFICULTATE, INPUT_PULLUP);
  Serial.begin(28800);

  // Configurează întreruperile pentru butoane
  attachInterrupt(digitalPinToInterrupt(BUTON_START), schimba_buton_start, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTON_DIFICULTATE), schimba_dificultate, FALLING);
}

// Funcția principală de execuție continuă
void loop() {
  currentMillis = millis();
  if (jocul_a_inceput) { // Dacă jocul a început
    if (buton_Start == LOW) { // Dacă butonul de stop e apăsat
      Serial.println("Stop button pressed!");
      buton_Start = 1;
      jocul_a_inceput = false;

      // Setează toate LED-urile pentru a indica oprirea
      digitalWrite(LED_ROSU, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_ALBASTRU, HIGH);
      delay(500);
    }

    if (runda_a_inceput)
      round_f(); // Execută runda

    if (greseala) { // Dacă există o eroare, aprinde LED-ul roșu
      digitalWrite(LED_ROSU, HIGH);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_ALBASTRU, LOW);
    } 
    
    else { // Altfel, LED-ul verde este aprins
      greseala = false;
      digitalWrite(LED_ROSU, LOW);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_ALBASTRU, LOW);
    }

  } 
  
  
  else { // Înainte de start
    if (!selectare_dificultate) { // Afișează mesajul de selectare dificultate o singură dată
      Serial.println("Select difficulty: ");
      selectare_dificultate = true;
    }
    
    if (dificultate_schimbata) { // Dacă s-a schimbat dificultatea
      delay(200);
      dificultate_schimbata = false;
        
      switch (dificultate) { // Setează intervalul în funcție de dificultate
        case 1:
          word_interval = 10000;
          Serial.println("Easy");
          break;
        case 2:
          word_interval = 7000;
          Serial.println("Medium");
          break;
        case 3:
          word_interval = 5000;
          Serial.println("Hard");
          break;
      }
    }


      
    if (buton_Start == LOW && !jocul_a_inceput) { // Dacă se apasă butonul de start
      Serial.println("Start button pressed!");
      buton_Start = 1;
      previousMillis = currentMillis;
      previousWordMillis = currentMillis;
      runda_a_inceput = true;

      startGame(); // Pornește jocul
      delay(500);
    }
    
    // Aprinde toate LED-urile când jocul e inactiv
    digitalWrite(LED_ROSU, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ALBASTRU, HIGH);
  }
}
