#include<AccelStepper.h>

AccelStepper stepperX(1,8,9);
AccelStepper stepperY(1,10,11);
int motion[] = {};

int sensor1Val;
int sensor2Val;
int buttonInputSAG = 2;
int buttonInputSOL = 3;
int buttonInputSTART = 4;
int buttonInputSTOP = 5;
int buttonInputRESET = 6;
bool state = false;


void setup(){
  
  //X Motoru
  stepperX.setMaxSpeed(1000);
  stepperX.setAcceleration(1000);
  stepperX.disableOutputs();

  //Y Motoru
  stepperY.setMaxSpeed(1000);


}
void loop(){

  
}

void ResetMotion(){
  if(state == true){
    memset(motion, 0, sizeof(motion));
    state = false;
  }
}



void OneStepR(){
  stepperX.moveTo(10);
  stepperX.runToPosition();
}

void OneStepL(){
  stepperX.moveTo(-10);
  stepperX.runToPosition();
}

void MotionSave(){
  if (digitalRead(buttonInputSAG) == HIGH){
    OneStepR();
    motion[sizeof(motion)] = 10;
  }

  else if (digitalRead(buttonInputSOL)==HIGH){
    OneStepL();
    motion[sizeof(motion)+1] = -10;
  }
}

void RunMotion(){
  for(int counter = 0; counter < int(sizeof(motion)); counter++){
    stepperX.moveTo(motion[counter]);
    stepperX.runToPosition();
  }
}


