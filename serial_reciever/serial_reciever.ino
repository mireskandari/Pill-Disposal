#include <Stepper.h>

String got;
int motor;
int degree;
int flag = false;
int cnt = 0;
int last = millis();
int time_past = 0;
int stepsPerRevolution = 2048;

Stepper myStepper2(stepsPerRevolution, 8, 7, 6, 5);
Stepper myStepper(stepsPerRevolution, 12, 10, 11, 9);

void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(10);
  myStepper2.setSpeed(10);
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  time_past += millis() - last;
  last = millis();
//  Serial.println(time_past);
  
  // put your main code here, to run repeatedly:
  if (Serial) {
    if (Serial.available()) {
      got += (char)(Serial.read());
      cnt++;
//      Serial.print(cnt);D
//      Serial.print(got);
    }
    if (cnt > 5 && !flag) {
      Serial.print("Rotating:");
      motor = got.toInt() % 10;
      degree = (int)(got.toInt() / 10);
      Serial.print(degree);
      Serial.println("true");

      if (motor == 1){ myStepper.step(degree); }
      if (motor == 2){ myStepper2.step(degree); }
      
      time_past = 0;
      flag = true;
      cnt = 0;
    }
    else if (cnt > 5 && flag) {
      if (time_past > 5000){
        Serial.print("Rotating:");
        motor = got.toInt() % 10;
        degree = (int)(got.toInt() / 10);
        Serial.print(degree);
        Serial.println("true");
        
        if (motor == 1){ myStepper.step(degree); }
        if (motor == 2){ myStepper2.step(degree); }
        
        time_past = 0;
        cnt = 0;
      }
    }
  }
}
