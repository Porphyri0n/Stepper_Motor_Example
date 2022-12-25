#include <AccelStepper.h>

#define HALFSTEP 8

#define motorPin1  9     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define motorPin2  10     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define motorPin3  11    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define motorPin4  12    // IN4 on ULN2003 ==> Orange on 28BYJ-48

int endPoint = 1024;        // Move this many steps - 1024 = approx 1/4 turn

// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
  Serial.begin(9600);
  Serial.println(stepper1.currentPosition());
  delay(5000);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(endPoint);
}

void loop()
{
  //Change direction at the limits
    if (stepper1.distanceToGo() == 0)
   {
     Serial.println(stepper1.currentPosition());
     stepper1.setCurrentPosition(0);
     endPoint = -endPoint;
     stepper1.moveTo(endPoint);
     Serial.println(stepper1.currentPosition());
   }
    stepper1.run();
}
