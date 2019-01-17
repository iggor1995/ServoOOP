#ifndef AbsMotorController_h  // если библиотека AbsMotorController_h не подключена
#define AbsMotorController_h  // тогда подключаем ее

#include <Arduino.h>
#include <RelMotorController.h>

class AbsMotorController {

    RelMotorController rmc;

  // move grabber to absolute position by x coordinates
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
  
// move grabber to absolute position by y coordinates
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
};
#endif
