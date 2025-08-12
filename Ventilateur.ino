// CODE

#include <LiquidCrystal.h>    //librairie ecran
#include <DHT.h>        //librairie capteur humidite
#include "IRremote.h"   //IR SENSOR

DHT dht(2, DHT11);      //reglages capteur humidite
#define ENABLE 11        //ports ventilateur  
#define DIRA 12
#define DIRB 13
IRrecv irrecv(3);         //mise en place IR SENSOR
decode_results results;
LiquidCrystal lcd(4, 5, 6, 7,8,9);  //ecran


bool debut = false;           //pour certains mode, variable à n'effectuer qu'une fois
String mode = "off      ";  // Declaration de la variable mode
int power = 0;              //puissance moteur
unsigned long delai = 0;    //delai pour mode alterné
unsigned long compteur = 0;   //compteur pour intervalles
bool en_route = false;        //hélice en route ? 
bool demarage = false;        //ordre de démarrage

void translateIR() {      //fonction de decodage récéption télécomande
    switch (results.value) {
      //allume /  éteint (bouton power)
        case 0xFFA25D:              //allume (mode manuel par défaut)
        if (mode == "off      "){
          mode = "manuel   ";
          power = 0;
          screenClear(2);
        }else if (mode == "continu  "){       //éteint pour les différents modes
          mode = "off      ";
          digitalWrite(DIRA,LOW);
          demarage = false;
          en_route = false;
          screenClear(2);
        }else if (mode == "alterne  "){
          mode = "off      ";
          digitalWrite(DIRA,LOW);
          demarage = false;
          en_route = false;
          screenClear(2);
        }else if (mode == "manuel   "){
          mode = "off      ";
          digitalWrite(DIRA,LOW);
          demarage = false;
          en_route = false;
          screenClear(2);
        }else if (mode == "auto"){
          mode = "off      ";
          digitalWrite(DIRA,LOW);
          demarage = false;
          en_route = false;
          screenClear(2);
        } break;
        case 0xFFE21D: Serial.println("fn /stop"); break;
        case 0xFF629D: Serial.println("VOL+"); break;
        case 0xFFA857: Serial.println("VOL-"); break;

      //monte de 1 mode (ordre : Auto -> continu -> alterne -> manuel)
        case 0xFF22DD: 
        if (mode == "off      "){

          Serial.print("Ventilateur off         ");

        }else if (mode == "continu  "){
          mode = "alterne  ";
          en_route = false;
          debut == false;
          screenClear(2);
        }else if (mode == "alterne  "){
          mode = "manuel   ";
          debut = false;
          power = 0;
          delai = 0;
          en_route = false;
          screenClear(2);
        }else if (mode == "manuel   "){
          mode = "auto     ";
          debut = false;
          en_route = false;
          screenClear(2);
        }else if (mode == "auto     "){
          mode = "continu  ";
          screenClear(2);
        } break;

      //descend de 1 (ordre : ordre : Auto <- continu <- alterne <- manuel)
        case 0xFFC23D: 
        if (mode == "off      "){
          
          Serial.print("Ventilateur off         ");

        }else if (mode == "continu  "){
          mode = "auto     ";
          en_route = false;
        }else if (mode == "alterne  "){
          debut = false;
          mode = "continu  ";
          en_route = false;
          screenClear(2);
        }else if (mode == "manuel   "){
          mode = "alterne  ";
          debut = false;
          en_route = false;
          screenClear(2);

        }else if (mode == "auto     "){
          mode = "manuel   ";
          power = 0;
          en_route = false;
        } break;

      //bouton pause / play pour activer / desactiver en mode manuel
        case 0xFF02FD:      
        demarage = true;
        break;
        
        case 0xFFE01F: Serial.println("DOWN"); break;
        case 0xFF906F: Serial.println("UP"); break;
        case 0xFF9867: Serial.println("EQ"); break;
        case 0xFFB04F: Serial.println("ST/REPT"); break;
      //réglages nombres (puissance et délai selon mode)
        case 0xFF6897:            
        if (mode == "manuel   "){
          power = 0;
        }else if (mode == "alterne  "){
          delai = 10000;
        }else if (mode == "continu  "){
          power = -4,2;
        }
        break;
        case 0xFF30CF:
        if (mode == "manuel   "|| mode == "continu  "){
          power = 1;
        }else if (mode == "alterne  "){
          delai = 20000;
          Serial.println("1");
        }
        break;
        case 0xFF18E7: 
        if (mode == "manuel   "|| mode == "continu  "){
          power = 2;
        }else if (mode == "alterne  "){
          delai = 40000;
        }
        break;
        case 0xFF7A85: 
        if (mode == "manuel   "|| mode == "continu  "){
          power = 3;
        }else if (mode == "alterne  "){
          delai = 60000;
        }
        break;
        case 0xFF10EF:
        if (mode == "manuel   "|| mode == "continu  "){
          power = 4;
        }else if (mode == "alterne  "){
          delai = 80000;
        }
        break;
        case 0xFF38C7: 
        if (mode == "manuel   "|| mode == "continu  "){
          power = 5;
        }else if (mode == "alterne  "){
          delai = 100000;
        }
        break;
        case 0xFF5AA5:
        if (mode == "manuel   "|| mode == "continu  "){
          power = 6;
        }else if (mode == "alterne  "){
          delai = 120000;
        }
        break;
        case 0xFF42BD:
        if (mode == "manuel   "|| mode == "continu  "){
          power = 7;
        }else if (mode == "alterne  "){
          delai = 140000;
        }
        break;
        case 0xFF4AB5:
        if (mode == "manuel   "|| mode == "continu  "){
          power = 8;
        }else if (mode == "alterne  "){
          delai = 160000;
        }
        break;

        case 0xFF52AD:
        if (mode == "manuel   "|| mode == "continu  "){
          power = 9;
        }else if (mode == "alterne  "){
          delai = 180000;
        }
        break;
        case 0xFFFFFFFF: Serial.print("repet"); break;
        default: Serial.println("Code inconnu"); break;
    }
    delay(500);
}

void screenClear(int ligne) {          //fonction efface un ligne précise
  if (ligne == 1){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  }
  if (ligne == 2){
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  }
}   

void setup() {
  String mode = "off         ";
  irrecv.enableIRIn();  //IR SENSOR
  pinMode(ENABLE,OUTPUT);//Ventilateur
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  dht.begin();                //HUMIDITE TEMPERATURE
  lcd.begin(16, 2);         //ecran (16 lignes 2 colonnes)
  Serial.begin(9600);
  lcd.print("Mode : ");
  digitalWrite(ENABLE,HIGH);
}

void loop() {
  lcd.setCursor(0,0);         //Affiche le mode
  lcd.print("Mode : ");
  lcd.setCursor(7,0);
  lcd.print(mode);
  lcd.setCursor(0,0);
  if (irrecv.decode(&results)) {    //appelle la reception de la télécomande
    translateIR();
    irrecv.resume(); // Reinitialise le recepteur pour la prochaine lecture
  }
  if (en_route == false){       //check de en route pour éteindr si besoin
    digitalWrite(DIRA, LOW);
  }
  if (mode == "continu  "){     //mode continu
      lcd.setCursor(0,1);
      lcd.print("Power : ");
      if (power == -4){     //exception si puissance = 0, éteint
        lcd.print("0");
        Serial.println(power);
        digitalWrite(DIRA, LOW);
        en_route = false;
      }else{
        int puissance = (80+power*19);      //choisit puissance entre 80 et 250 (0 de base)
        lcd.print(power);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB,LOW);
        analogWrite(ENABLE,puissance);
        en_route = true;
      }

  }else if (mode == "off      "){       //mode off
    en_route = false;
  }else if (mode == "manuel   "){     //mode manuel
    lcd.setCursor(0,1);
    lcd.print("Power : ");
    lcd.print(power);
    if (debut == false){              //off de base
      lcd.print("   OFF");
      debut = true;
    }
    if (en_route == true){            //allumé à la puissance demandée (de base 0 mais off) 
      int puissance = (80+power*19);
      analogWrite(ENABLE,puissance);
    }
    if (demarage == true){            //quand on recoit l'ordre de démarrer ou d'éteindre selon ce qui est activé
      if (en_route == false){
        int puissance = (80+power*19);
        Serial.print(puissance);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB,LOW);
        analogWrite(ENABLE,puissance);
        demarage = false;
        en_route = true;
        lcd.print("    ON");
      }else if (en_route = true){
        digitalWrite(DIRA, LOW);
        demarage = false;
        en_route = false;
        lcd.print("   OFF");
      }
    }
  }else if(mode == "alterne  "){
    lcd.setCursor(0,1);           //affiche le délai choisi
    lcd.print("Delai : ");
    Serial.println(delai);
    if (debut == false){
      compteur = 0;
      debut = true;
      lcd.print("indefini");
    }
    if (delai == 10000){
      lcd.print("10s     ");
    }else if (delai == 20000){
      lcd.print("20s     ");
    }else if (delai == 40000){
      lcd.print("40s     ");
    }else if (delai == 60000){
      lcd.print("1min    ");
    }else if (delai == 80000){
      lcd.print("1min20  ");
    }else if (delai == 100000){
      lcd.print("1min40  ");
    }else if (delai == 120000){
      lcd.print("2min    ");
    }else if (delai == 140000){
      lcd.print("2min20  ");
    }else if (delai == 160000){
      lcd.print("2min40  ");
    }else if (delai == 180000){
      lcd.print("3min    ");
    }else{
      lcd.print("indefini");
    }
    if (compteur < delai){
      delay(500);
      compteur += 500;
    }else if(compteur = delai){           //quand compteur = delai, active pendant 1/3 du délai
      if (delai != 0)
        delay(delai);
        digitalWrite(DIRA, HIGH);
        en_route = true;
        digitalWrite(DIRB,LOW);
        delay(delai/3);
        digitalWrite(DIRA,LOW);
        en_route = false;
        compteur = 0;
    }
  }else if(mode == "auto     "){
    lcd.setCursor(0,1);
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();  
    lcd.print("temp: ");                //affiche humidité et température
    lcd.print(int(temp));
    lcd.print(" ");
    lcd.print("hum :");
    lcd.print(int(hum));
    lcd.setCursor(13,0);
    if (temp > 28 || hum > 70){         // condition sous laquelle ça se met en route (recheck toutes les 5 secondes)
      lcd.print("ON");
      digitalWrite(DIRA, HIGH);
      en_route = true;
      delay(5000);
      digitalWrite(DIRA, LOW);
      en_route = false;
    }else{
      lcd.print("OFF");
      delay(5000);
    }
  }
}