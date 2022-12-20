#include<AccelStepper.h>                    //kütüphane

AccelStepper stepperX(1,8,9);               //X motorunun kurulumu(Sürücüye göre parantez içi değerleri değişecek)
AccelStepper stepperY(1,10,11);             //Y motorunun kurulumu(Sürücüye göre parantez içi değerleri değişecek)
int motion[] = {};

int sensor1Val;                             //Eklenecek sensörlerden birinin input değeri
int sensor2Val;                             //Eklenecek sensörlerden birinin input değeri
int buttonInputSAG = 2;                     //Sağ buton pini
int buttonInputSOL = 3;                     //Sol buton pini
int buttonInputSTART = 4;                   //Start buton pini
int buttonInputSTOP = 5;                    //Stop buton pini
int buttonInputRESET = 6;                   //Reset buton pini
int buttonInputHOME = 7;                   //Reset buton pini
int buttonInputEND = 12;                   //Reset buton pini
int buttonInputToHome = 13;                   //Reset buton pini
bool state = false;                         //Motion başladı mı başlamadı mı kontrolü
int endpos;
int homepos = 0;

void setup(){
  
  //X Motoru
  stepperX.setMaxSpeed(1000);               //Motor kurulumu
  stepperX.setAcceleration(1000);
  stepperX.disableOutputs();

  //Y Motoru
  stepperY.setMaxSpeed(1000);


}
void loop(){
  Home();
  End();
  RunMotion();
}

void Home(){
  if(buttonInputHOME == HIGH){
    stepperX.setCurrentPosition(0);
  }
}
void End(){
  if(buttonInputEND == HIGH){
    endpos = stepperX.currentPosition();
  }


}
void OneStepR(){               //Sağa doğru bir adım motoru sürer
  stepperX.moveTo(10);
  stepperX.runToPosition();
}

void OneStepL(){               //Sola doğru bir adım motoru sürer
  stepperX.moveTo(-10);
  stepperX.runToPosition();
}

void MotionSave(){             //Hareketi kaydeder
  if (digitalRead(buttonInputSAG) == HIGH){
    OneStepR();
    motion[sizeof(motion)] = 10;
  }

  else if (digitalRead(buttonInputSOL)==HIGH){
    OneStepL();
    motion[sizeof(motion)+1] = -10;
  }
}

void RunMotion(){            //Hareketi başlatır
  if(buttonInputSTART == HIGH){
    stepperX.moveTo(homepos);
    stepeprX.runToPosition()
    stepperX.moveTo(endpos);
    stepeprX.runToPosition();
  }
}

void ToHome(){
  if(buttonInputToHome == HIGH){
    stepperX.runToNewPosition(homepos);
  }
}






