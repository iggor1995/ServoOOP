#ifndef AbsMotorController_h  // если библиотека AbsMotorController_h не подключена
#define AbsMotorController_h  // тогда подключаем ее

#include <Arduino.h>
#include "RelMotorController.h"
#include "ScadaRouting.h"

class AbsMotorController {

    RelMotorController rmc;
    
  private:
    int grabbingPartXCoord = 1400;
    int grabbingPartYCoord = 24780;
    byte isGripperPlaced = 4;
    
  public:  
  
  void moveToGrabbingPos(ScadaRouting sr){
        sr.writeDataCoils(28, 1);
        sr.setCoordinates(grabbingPartXCoord, grabbingPartYCoord);
        xMoveToPos(grabbingPartXCoord);
        yMoveToPos(grabbingPartYCoord);
    }

  void xMoveToPos(int pos){
    digitalWrite(isGripperPlaced, LOW);
    int moveX;
    int x = rmc.getX();
    if(pos > x){
      moveX = pos - x;
      rmc.moveRight(moveX);
    }
    if(pos < x){
      moveX = x - pos;
      rmc.moveLeft(moveX);
    }    
  }
  
  void moveRight(int delta) {
    rmc.moveRight(delta);
  }
  
  int getX() { rmc.getX(); }
  
  int getY() { rmc.getY(); }
  
  void yMoveToPos(int pos){
    digitalWrite(isGripperPlaced, LOW);
    int moveY;
    int y = rmc.getY();
    if(pos > y){
      moveY = pos - y;
      rmc.moveDown(moveY);
    }
    else if(pos < y){
      moveY = y - pos;
      rmc.moveUp(moveY);
    }
  }
  
  RelMotorController getRelMotorController() {return rmc;}
};
#endif
