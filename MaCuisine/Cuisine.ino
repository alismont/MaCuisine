//-------------------------------------------------------------------

#include "TimerOne.h"

int TpsEv = 300;
int TpsHot = 300;
int Cpt_BpHot = 0;
int BpHot = 5 ;
int EtatBpHot = 0;
int BpEv = 2;
int EtatBpEv = 0;
int SpotEv = 11;
int SpotHotOn = 0;
int SpotEvOn = 0;
int SpotHot = 12;
int BpEscalHot = 7;
int BpEscalEv = 3;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;
int B3[20];
int TpsSgen = 50;
int Led13 = 13;
boolean firstscan = true;
char octetReception;
char caractereReception;
char octetReceptionProc;
char caractereReceptionProc;
String chaineReception, Tram;
String chaineReceptionProc, TramProc;
boolean Processing = true;
int outSpothot = 0;
int outSpotEv = 0;
char charVal[10];
int BpSeq = 0;
int val1Memo = 0;
int BpHotTps = 10;
int BpEvTps = 10;
int Cpt_BpEv_val = 0;
int Cpt_BpHot_val = 0;


int T[10];
int TDN[10];
boolean CptT[10];

//**********************************************************
void setup() {

  Serial.begin(9600);
  //pinMode(BpHot, INPUT);
  //pinMode(BpEv, INPUT);
  //pinMode(BpEscalHot, INPUT);
  //pinMode(BpEscalEv, INPUT);

  pinMode(BpHot, INPUT_PULLUP);
  pinMode(BpEv, INPUT_PULLUP);
  pinMode(BpEscalHot, INPUT_PULLUP);
  pinMode(BpEscalEv, INPUT_PULLUP);


  pinMode(SpotHot, OUTPUT);
  pinMode(SpotEv, OUTPUT);
  pinMode(Led13, OUTPUT);
  BpHotTps = 0;
  BpEvTps = 0;
  digitalWrite(SpotHot, HIGH);
  digitalWrite(SpotEv, HIGH);
  B3[2] = 0;
  B3[4] = 0;

  Timer1.initialize(100000);         // initialize timer1
  Timer1.attachInterrupt(callback);

}
//***********************************************************
void loop() {

  // Temporisation  TON
  if (!digitalRead(BpEv)) {
    CptT[8] = true;
  }
  else {
    T[8] =  0.0;
    TDN[8] =  0.0;
    CptT[8] = false;
  }
  if (T[8] >= 25) { // présélection de 600 donc 60 secondes
    TDN[8] =  1.0;   // bit down
    T[8] = 25;
  }


  //-cond ons
  if (!digitalRead(BpEv)| !digitalRead(BpHot) ) {
    if (!B3[2]) {  //---bit ons
      B3[2] = 1.0;
      B3[4] = 1.0;  //----Action
    }
    else {
      B3[4] = 0.0; //------erase action au scan suivant
    }
  }
  else {
    B3[2] = 0.0;//---plus la condition
    B3[4] = 0.0;
  }

  //Gestion éclairage & (digitalRead(BpEv) | digitalRead(!BpHot)))
  if (B3[4]) {
    BpSeq = BpSeq + 1;
    if (BpSeq > 3) {
      BpSeq = 0;
    }
  }

  //digitalWrite(SpotHot, HIGH);
  //digitalWrite(SpotEv, LOW);
  switch (BpSeq) {
    case 0:
      digitalWrite(SpotHot, HIGH);
      digitalWrite(SpotEv, HIGH);
      break;
    case 1:
      digitalWrite(SpotHot, HIGH);
      digitalWrite(SpotEv, LOW);
      break;
    case 2:
      digitalWrite(SpotHot, LOW);
      digitalWrite(SpotEv, HIGH);
      break;
    case 3:
      digitalWrite(SpotHot, LOW);
      digitalWrite(SpotEv, LOW);
      break;
    default:
      // statements
      break;
  }


  Serial.println(digitalRead(BpHot));
}

//************************************************************************
void callback() {

  if (CptT[8]) {
    T[8] =  T[8] + 1.0;
  }
}
