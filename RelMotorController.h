#ifndef RelMotorController_h  // если библиотека RelMotorController не подключена
#define RelMotorController_h  // тогда подключаем ее

#include <Arduino.h>
#include "Grabber.h"

class RelMotorController {
    private:
    Grabber grabber = Grabber();
    public:
    void moveMotors(int impulseCount){
      for(int i = 0; i < impulseCount; i++){
          grabber.getLeftMotor().moveMotor();
          grabber.getRightMotor().moveMotor();
          grabber.changeCoord();
      }
    }
    
    // xRel = relative coordinate changes
    void executeMoving(boolean leftMotorDir, boolean rightMotorDir, int dist){
        grabber.releaseBrakes();
        delay(100);
        grabber.changeDir(leftMotorDir, grabber.getCwLeftMotor());
        grabber.changeDir(rightMotorDir, grabber.getCwRightMotor());
        moveMotors(dist);
        delay(10);
        grabber.activateBrakes();
        delay(100);
    }
    
    // change direction to down and move
      void moveLeft(int dist){
        executeMoving(true, true, dist);
      }
    // change direction to left and move  
      void moveRight(int dist){
        executeMoving(false, false, dist);
      }
    // change direction to upward and move
      void moveUp(int dist){
        executeMoving(false, true, dist);
      }
    // change direction to downward and move
      void moveDown(int dist){
        executeMoving(true, false, dist);
    }

    Grabber getGrabber() { return grabber; }
    
    int getX() { grabber.getX(); }
    
    int getY() { grabber.getY(); }
};
#endif
