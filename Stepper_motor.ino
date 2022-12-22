#include<AccelStepper.h>                    //kütüphane

AccelStepper stepperX(2000,9,10,11,12);               //X motorunun kurulumu(Sürücüye göre parantez içi değerleri değişecek)
//AccelStepper stepperY(1,10,11);             //Y motorunun kurulumu(Sürücüye göre parantez içi değerleri değişecek)
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
int endpos;
int homepos = 0;

void setup(){
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
  stepperX.disableOutputs();

  //Y Motoru
  //stepperY.setMaxSpeed(1000);


}
void loop(){
  if(state == false){
    stepperX.enableOutputs();
    Right();
    Left();
    stepperX.run();
    Home();
    End();
  }
  else{
    Motion();
  }
  if(digitalRead(buttonInputSTART)==HIGH){
    state = true;
    delay(300);
  }

  stepperX.run();
}


void Right(){
  if(digitalRead(buttonInputSAG) == HIGH){
  stepperX.moveTo(1);
  }
}

void Left(){
  if(digitalRead(buttonInputSAG) == HIGH){
  stepperX.moveTo(-1);
  }
  
}
void Home(){
  if(digitalRead(buttonInputHOME)==HIGH){
    stepperX.setCurrentPosition(0);
  }
}

void End(){
  if(digitalRead(buttonInputEND)==HIGH){
    endpos = stepperX.currentPosition();
  }
  
}
void Motion(){
    while (stepperX.currentPosition() != 0){
      stepperX.moveTo(0);
    }
    while (stepperX.currentPosition() != endpos){
      stepperX.moveTo(endpos);
    }
}

void Reset(){
  state = false;
  stepperX.disableOutputs();
}




