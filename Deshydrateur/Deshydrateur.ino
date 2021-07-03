/*
 * H3O Fablab
 * Animateur : Willy T.
Code pour atelier Arduino
Projet Déshydrateur
*/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);

int RlLampe=12;
int RlCompr=11;

uint32_t delayMS;




String EtatLampe;
String EtatCompr;



void Message(){
 String ETAT= EtatLampe + EtatCompr;
  if (ETAT>0) Serial.println("{"+ ETAT +"}");
}

void RelaiLampeOn(){
  digitalWrite(RlLampe, HIGH);
EtatLampe= "\"LAMPE\": " + String(1) ;

}

void RelaiLampeOff(){
  digitalWrite(RlLampe, LOW);
EtatLampe= "\"LAMPE\": " + String(0) ;

}



void RelaiComprOn() {
  digitalWrite(RlCompr, HIGH);
 EtatCompr= "\"relaiCompr\": " + String(1) ;
  
}

void RelaiComprOff() {
  digitalWrite(RlCompr, LOW);
   EtatCompr= "\"relaiCompr\": " + String(0) ;
}


//TEMPERATURE AMBIANT 27.20

//SONDE ROUGE 978 TEMPERATURE AMBIANT 27.20
//100 DEGRE POUR 742
//SONDE BLEU 1003 TEMPERATURE AMBIANT 27.20
//100 DEGRE POUR 880
//SONE TRANSPARENTE 976 TEMPERATURE AMBIANT 27.20
//100 DEGRE POUR 836
void sondeBleu(){
    sensorValue = analogRead(A0);
   float convSondeBleu=map(sensorValue,880,1003,1000,272);
   Serial.print("sonde bleu : ");
Serial.println(convSondeBleu/10);
 delay(1000);
}
void sondeTransparent(){
    sensorValue = analogRead(A1);
   float convSondeTransparent=map(sensorValue,836,976,1000,272);
   Serial.print("sonde transparent : ");
Serial.println(convSondeTransparent/10);
 delay(1000);
}
void sondeRouge(){
    sensorValue = analogRead(A2);
   float convSondeRouge=map(sensorValue,742,978,1000,272);
   Serial.print("sonde rouge : ");
Serial.println(convSondeRouge/10);
 delay(1000);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RlLampe, OUTPUT);
  pinMode(RlCompr, OUTPUT);
  Serial.begin(9600); 
   dht.begin();
}

// the loop function runs over and over again forever
void loop() {
  String  LectureSerie;
  //bLinK();
  //dth();
  delay (500);
  //Serial.println ("ici");
   if (Serial.available() > 0) {
    // read the incoming byte:
    delay (100);
    LectureSerie = Serial.readString();
    Serial.println (LectureSerie);
  }
  if ( LectureSerie=="RlLampOn")RelaiLampeOn();
 if ( LectureSerie=="RlLampOff")RelaiLampeOff();
if ( LectureSerie=="RlLComprOn")RelaiComprOn();
 if ( LectureSerie=="RlLComprOff")RelaiComprOff();

 Message();
 
}
void bLinK() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);// wait for a second
  Serial.println(" programme blink");
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
void dth() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("�C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
