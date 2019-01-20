#ifndef Grabber_h  // если библиотека Grabber не подключена
#define Grabber_h  // тогда подключаем ее

  #include <Arduino.h>
  #include "Motor.h"

class Grabber {

   private:
    const byte CLK_LEFT_PIN = 6;
    const byte CLK_RIGHT_PIN = 7;
    const byte CW_LEFT_MOTOR = 8;
    const byte CW_RIGHT_MOTOR = 9;
    const byte BRAKES_PIN = 5;
    const int MOTOR_SPEED = 30;
    
    int x = 0;                   //absolute coord X
    int y = 0;                   //absolute coord Y
    
    Motor leftMotor = Motor(CLK_LEFT_PIN, MOTOR_SPEED, CW_LEFT_MOTOR);
    Motor rightMotor = Motor(CLK_RIGHT_PIN, MOTOR_SPEED, CW_RIGHT_MOTOR);
  
  public:
    Grabber(){
      pinMode(BRAKES_PIN, OUTPUT);
    }
  
    void changeCoord() {
      if(leftMotor.getDir() == HIGH && rightMotor.getDir() == HIGH && x > 0) { x--; }
      if(leftMotor.getDir() == HIGH && rightMotor.getDir() == LOW) { y++; }
      if(leftMotor.getDir() == LOW && rightMotor.getDir() == HIGH && y > 0) {y--; }
      if(leftMotor.getDir() == LOW && rightMotor.getDir() == LOW){ x++; }
    }

    // change rotating direction to certain motor
    // motorNumber - address for clk+ output
    void changeDir(boolean isCwPlus, int motorNumber){
      if(isCwPlus == true){
       digitalWrite(motorNumber, HIGH);
      }
      else{
        digitalWrite(motorNumber, LOW);
      }    
    }

    void releaseBrakes() {
      digitalWrite(BRAKES_PIN, HIGH);
    }
    void activateBrakes() {
      digitalWrite(BRAKES_PIN, LOW);
    }

    Motor getLeftMotor() { return leftMotor; }
    Motor getRightMotor() { return rightMotor; }

    byte getCwLeftMotor() { return CW_LEFT_MOTOR; }
    byte getCwRightMotor() { return CW_RIGHT_MOTOR; }

    int getX() { return x; }
    int getY() { return y; }
};

#endif
