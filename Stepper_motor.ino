#include<AccelStepper.h>                   //kütüphane

//X motorunun pinleri ve adım ölçeği
#define HALFSTEPX 8
#define motorXPin1 9
#define motorXPin2 11
#define motorXPin3 10
#define motorXPin4 12

//Y motorunun pinleri
//#define HALFSTEPY 8
//#define motorYPin4 12
//#define motorYPin4 12
//#define motorYPin4 12
//#define motorYPin4 12


AccelStepper stepperX(HALFSTEPX,motorXPin1,motorXPin2,motorXPin3,motorXPin4);               //X motorunun kurulumu(Sürücüye göre parantez içi değerleri değişecek)
//AccelStepper stepperY(HALFSTEPY,motorYPin1,motorYPin2,motorYPin3,motorYPin4);               //Y motorunun kurulumu(Sürücüye göre parantez içi değerleri değişecek)
int motion[] = {};

int sensor1Val;                             //Eklenecek sensörlerden birinin input değeri
int sensor2Val;                             //Eklenecek sensörlerden birinin input değeri
int buttonInputSAG = 2;                     //Sağ buton pini
int buttonInputSOL = 3;                     //Sol buton pini
int buttonInputSTART = 4;                   //Start buton pini               
int buttonInputRESET = 5;                   //Reset buton pini
int buttonInputHOME = 6;                    //Home buton pini
int buttonInputEND = 7;                     //End buton pini
//int buttonInputToHome = 13;               //To home buton pini
//int buttonInputToEnd = 13;                //To End buton pini
bool state = false;                         //Motion başladı mı başlamadı mı kontrolü
int endpos = 1000;
int homepos = 0;
int counter = 0;

void setup(){
  Serial.begin(9600);
  pinMode(buttonInputSAG,INPUT);
  pinMode(buttonInputSOL,INPUT);
  pinMode(buttonInputSTART,INPUT);
  pinMode(buttonInputRESET,INPUT);
  pinMode(buttonInputHOME,INPUT);
  pinMode(buttonInputEND,INPUT);
  
  //X Motoru
  Serial.println("Motor Testi");            //Motor testi
  stepperX.setMaxSpeed(1000);               
  stepperX.setAcceleration(1000);

  Serial.println("Deneme baslatiliyor");
  stepperX.moveTo(homepos);
  stepperX.run();
  stepperX.moveTo(endpos);
  stepperX.run();
  

  //Y Motoru
  //stepperY.setMaxSpeed(1000);


}
void loop(){
  if(state == false){
    Serial.print("Kayit Modu, StepperX'in anlık konumu: ");
    Serial.println(stepperX.currentPosition());
    Direction();
    stepperX.enableOutputs();
    stepperX.runSpeed();
    Home();
    End();
  }

  else{
    Serial.println("Motion modu, StepperX'in anlık konumu: ");
    Serial.println(stepperX.currentPosition());
    Motion();
  }

  if(digitalRead(buttonInputSTART)==HIGH){
    Serial.println("Motion moduna gecildi");
    state = true;
    delay(300);
  }

  if(digitalRead(buttonInputRESET)==HIGH){
    Serial.println("Program bastan baslatiliyor");
    Reset();
    delay(300);
    }
  delay(100);


}

//Sağ Sol yaptırma işlemi
void Direction(){
  if(digitalRead(buttonInputSAG) == HIGH && digitalRead(buttonInputSOL) == LOW){
    stepperX.setSpeed(500);
  }
  else if(digitalRead(buttonInputSOL) == HIGH && digitalRead(buttonInputSAG) == LOW){
    stepperX.setSpeed(-500);
  }
  else{
    stepperX.setSpeed(0);
  }
}

//Home pozisyonu ayarlama
void Home(){
  if(digitalRead(buttonInputHOME)==HIGH){
    Serial.print("home pozisyonu ayarlandı StepperX'in anlık konumu: ");
    Serial.println(stepperX.currentPosition());    
    stepperX.setCurrentPosition(homepos);
  }
}
//End pozisyonu ayarlama
void End(){
  if(digitalRead(buttonInputEND)==HIGH){
    Serial.print("end pozisyonu ayarlandı StepperX'in anlık konumu: ");
    Serial.println(stepperX.currentPosition());
    endpos = stepperX.currentPosition();
  }
  
}
//Kaydedilen konumlar üzerinden hareketi başlatma
void Motion(){

    if (stepperX.distanceToGo() == 0)
   {
     if (counter%2 == 0){
       stepperX.moveTo(homepos);
       counter+=1;
     }
     else{
       stepperX.moveTo(endpos);
       counter+=1;
     }
     
   }
   stepperX.runToPosition();

}

//Programı başa alma
void Reset(){
  state = false;
  stepperX.disableOutputs();
}




