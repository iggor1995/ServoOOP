#ifndef BusinessController_h  // если библиотека BusinessController_h не подключена
#define BusinessController_h  // тогда подключаем ее

#include <Arduino.h>
#include "AbsMotorController.h"
#include "ScadaRouting.h"
#include "ManualController.h"

class BusinessController {

  private:
    int redPartCount = 0;
    int transparentPartCount = 0;
    int metalPartCount = 0;
    int maxPartsOnLevel = 8;
    int maxPartsInRow = 4;
    int firstLevelY = 20500;
    int secondLevelY = 16600;
    int thirdLevelY = 12800; 
    int fourthLevelY = 9200; 
    int fifthLevelY = 5500; 
    int sixthLevelY = 1800; 
    byte typeA = 2;
    byte isGripperPlaced = 4;
    byte allowToMove = 1;
    byte typeB = 3;
    byte lowerLevel;
    byte higherLevel;
    int partCount = 0;;
    ScadaRouting sr;
    AbsMotorController amc;
    ManualController mc;

  public:

  void firstMove(){

    sr.scan();
    digitalWrite(isGripperPlaced, LOW);
    while(digitalRead(allowToMove) != true){
          sr.scan();
          checkIfManual();
          sr.sendData(redPartCount, transparentPartCount, metalPartCount, 0);
    }
    delay(1000);
    if(digitalRead(allowToMove) == true){
      amc.moveToGrabbingPos(sr);
      int colorNumber = processColor();
      incrementCount(colorNumber);
      digitalWrite(isGripperPlaced, HIGH);
      delay(2300);
      digitalWrite(isGripperPlaced, LOW);
    }
  }

  void secondMove(){
    sr.scan();
    digitalWrite(isGripperPlaced, LOW);
    while(digitalRead(allowToMove) != true){
      checkIfManual();
    }
    sr.scan();
    digitalWrite(isGripperPlaced, LOW);
    if(digitalRead(allowToMove) == true){
       int colorNumber = processColor();
       if(colorNumber != 0){
         movePart(colorNumber);        //move grabber
         digitalWrite(isGripperPlaced, HIGH);
       }
    }
    sr.scan();
    delay(1000);
    digitalWrite(isGripperPlaced, LOW);
}

  void movePart(int color){
      delayForScadaSetup(color);
      setLevelsandPartCount(color);
      waitIfFull(color);
      if(partCount < 17){
        moveToYFirstCell(color);
        moveToXCell(color);
      }
    }

  void delayForScadaSetup(int color){
    for(int i = 0; i < 100; i++){
        sr.sendData(redPartCount, transparentPartCount, metalPartCount, color);
      }  
  }
  
  void waitIfFull(int color) {
    if(partCount > 16){
      while(true){
         checkIfManual();  
         sr.sendData(redPartCount, transparentPartCount, metalPartCount, color);
         delay(200);        
      }
    }
  }
  
  void moveToXCell(int color) {
      int delta;
      int xDelta = 2275;
      if(partCount <= maxPartsInRow){
          delta = xDelta * (partCount - 1);
      }
      else{
          delta = xDelta * (partCount - maxPartsInRow - 1);
      }
      sr.setCoordinates(delta, amc.getY());
      sr.sendData(redPartCount, transparentPartCount, metalPartCount, color);
      amc.moveRight(delta);
  }
  
  void moveToYFirstCell(int color) {
      int xFirstCellPos = 600;
      if(partCount <= maxPartsOnLevel){
          amc.yMoveToPos(lowerLevel);
          sr.setCoordinates(amc.getX(), lowerLevel);
          sr.sendData(redPartCount, transparentPartCount, metalPartCount, color);
        } 
      else{
          amc.yMoveToPos(higherLevel);
          sr.setCoordinates(amc.getX(), higherLevel);
          partCount = partCount - maxPartsOnLevel;
          sr.sendData(redPartCount, transparentPartCount, metalPartCount, color);
        }
      amc.xMoveToPos(xFirstCellPos); // move to first sell int row
      sr.setCoordinates(xFirstCellPos, amc.getY());
      sr.sendData(redPartCount, transparentPartCount, metalPartCount, color);
    }
    
  void setLevelsandPartCount(int color){
    sr.scan();
    switch(color) {
      case 1: //RED COLOR
        setLevelsAndCount(firstLevelY, secondLevelY, redPartCount);
        break;
      case 2:    //TRANSPARENT COLOR
        setLevelsAndCount(thirdLevelY, fourthLevelY, transparentPartCount);
        break;
      case 3:    //METAL COLOR
        setLevelsAndCount(fifthLevelY, sixthLevelY, metalPartCount);
        break;
    }
    sr.scan();   
  }
 
  void setLevelsAndCount(byte lLevel, byte hLevel, int count ) {
    lowerLevel = lLevel;
    higherLevel = hLevel;
    partCount = count;
  }
  
  int processColor() {
      sr.scan();
      if (digitalRead(typeA) == HIGH) {
        if (digitalRead(typeB) == HIGH) {
            return 1;      //1* - means red part      
        }
        else {
            transparentPartCount++;
            return 2;  //2* - means transparent part*
          }
      }
      else {
        if (digitalRead(typeB) == HIGH) {
            return 0;
          }
        else {
           metalPartCount++;
           return 3;    //3* - means metal part
          }
      }
    }
    
  void incrementCount(byte color) {
      switch (color) {
        case 1:
          redPartCount++;
          break;
        case 2:
          transparentPartCount++;
          break;
        case 3:
          metalPartCount++;
          break;  
      }
  }

  boolean checkIfManual(){
      if(sr.scanDataCoils(21) == true){   //if manual mode
        mc.manualMode(amc, sr);
  }
}
};
#endif
