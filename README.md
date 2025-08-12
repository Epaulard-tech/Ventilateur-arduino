<<<<<<< HEAD
// UTILISATION

//démarre en mode off, Power pour allumer en mode continu de base
//MODES :  (accès avec fleches droites et gauches)
//CONTINU : Est allumé non stop à puissance choisie (0 à 9)
//AUTO : en route puissance max si température > 28 ou humidité > 70 %
//ALTERNE : Selon un délai (réglable avec 0 à 9), attend ce délai puis allume le moteur 1/3 du délai
//MANUEL : allumage on / off avec puissance réglable (0 à 9)

// BRANCHEMENTS : 
//alim noire sur la breadboard avec bonnes polarités
//Capteur IR : G, 5V et PWM 3
//Capteur Temp/humidité : GRD, 5V et PWM 2
//5V venant de l'arduino : 5 prises dessus (pas sur les bordure breadboard, c'est réservé à l'alim)
//GRD venant de l'arduino : 7 prises dessus (pas sur les bordure breadboard, c'est réservé à l'alim)
//sur la puce L293D (demi cercle à gauche)
//PIN_PWM_11, PIN_PWM 12 (dirA), + moteur, GRD de la bordure (alim côté prise noire), RIEN , - moteur, PIN_PWM13 (dirB), + de l'alimentation noire via breadboard
//ECRAN LED : VSS : GRD, VDD : 5V, V0 : pin fin potentiomètre, RS : PWM 4, E : PWM 5, D0-D3 : RIEN, D4-D7 : PWM 6-9 dans l'ordre, A : 5V, K : GRD
//POTENTIOMETRE : Pin seul dans le V0 de l'écran, en entrée, GRD à gauche 5V à droite


// UTILISATION CAPTEURS UN A UN

/*CAPTEUR HUMIDITE / TEMPERATURE
  #include <DHT.h>
  DHT dht(6, DHT11);

  dht.begin();
  
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.print("Temperature : ");
  Serial.println(temp);
  Serial.print("Humidite : ");
  Serial.println(hum);
*/
/* LEDS
#define PIN_RED 7
#define PIN_BLUE 13
#define PIN_GREEN 12

pinMode(PIN_RED, OUTPUT); 
pinMode(PIN_GREEN, OUTPUT); 
pinMode(PIN_BLUE, OUTPUT); 
digitalWrite(PIN_RED, LOW); 
digitalWrite(PIN_GREEN, LOW); 
digitalWrite(PIN_BLUE, LOW); 

analogWrite(PIN_RED, 255);
analogWrite(PIN_BLUE, 120);
analogWrite(PIN_GREEN, 120);
*/
/* VENTILATEUR
#define ENABLE 2  
#define DIRA 3
#define DIRB 4

pinMode(ENABLE,OUTPUT);
pinMode(DIRA,OUTPUT);
pinMode(DIRB,OUTPUT);

digitalWrite(ENABLE,HIGH);          //active le moteur, inutile si l'on precise ensuite une puissance, c'est que pour le on/off         
digitalWrite(ENABLE,LOW);           //desactive le moteur
analogWrite(ENABLE, 255);           //active le moteur ET (set une vitesse entre 80 (en dessous ça galère à demarrer) et 255) MAIS NE FAIT PAS AVANCER !!!
digitalWrite(DIRA, HIGH);           //allume dans l'autre
digitalWrite(DIRB, LOW);            //off          dans un sens
*/
/*STEPPER
#include <Stepper.h>
Stepper Stepper (32, 8, 10, 9, 11);

Stepper.setSpeed(500);
Stepper.step(500); 
*/
/* IR SENSOR
#include "IRremote.h"
IRrecv irrecv(5);
decode_results results;

irrecv.enableIRIn();  

if (irrecv.decode(&results)) {
    translateIR();
    irrecv.resume(); // Reinitialise le recepteur pour la prochaine lecture
  }
void translateIR() {
    switch (results.value) {
        case 0xFFA25D: Serial.println("power"); break;
        case 0xFFE21D: Serial.println("fn /stop"); break;
        case 0xFF629D: Serial.println("VOL+"); break;
        case 0xFFA857: Serial.println("VOL-"); break;
        case 0xFF22DD: Serial.println("FAST BACK"); break;
        case 0xFF02FD: Serial.println("PAUSE"); break;
        case 0xFFC23D: Serial.println("FAST FORWARD"); break;
        case 0xFFE01F: Serial.println("DOWN"); break;
        case 0xFF906F: Serial.println("UP"); break;
        case 0xFF9867: Serial.println("EQ"); break;
        case 0xFFB04F: Serial.println("ST/REPT"); break;
        case 0xFF6897: Serial.println("0"); break;
        case 0xFF30CF: Serial.println("1"); break;
        case 0xFF18E7: Serial.println("2"); break;
        case 0xFF7A85: Serial.println("3"); break;
        case 0xFF10EF: Serial.println("4"); break;
        case 0xFF38C7: Serial.println("5"); break;
        case 0xFF5AA5: Serial.println("6"); break;
        case 0xFF42BD: Serial.println("7"); break;
        case 0xFF4AB5: Serial.println("8"); break;
        case 0xFF52AD: Serial.println("9"); break;
        case 0xFFFFFFFF: Serial.print("repet"); break;
        default: Serial.println("Code inconnu"); break;
    }
    delay(500);
}
*/
>>>>>>> 3cade59 (initial commit)
