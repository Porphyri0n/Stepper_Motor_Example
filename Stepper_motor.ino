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
bool state = false;                         //Motion başladı mı başlamadı mı kontrolü


void setup(){
  
  //X Motoru
  stepperX.setMaxSpeed(1000);               //Motor kurulumu
  stepperX.setAcceleration(1000);
  stepperX.disableOutputs();

  //Y Motoru
  stepperY.setMaxSpeed(1000);


}
void loop(){

  
}

void ResetMotion(){            //Hareketi hafızadan siler
  if(state == true){
    memset(motion, 0, sizeof(motion));
    state = false;
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
  for(int counter = 0; counter < int(sizeof(motion)); counter++){
    stepperX.moveTo(motion[counter]);
    stepperX.runToPosition();
  }
}








