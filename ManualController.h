#ifndef ManualController_h  // если библиотека ManualController_h не подключена
#define ManualController_h  // тогда подключаем ее

#include <Arduino.h>
#include "AbsMotorController.h"
#include "RelMotorController.h"
#include "Grabber.h"
#include "ScadaRouting.h"
/*
 * During manual mode it's possible to move grabber
 * 21 - if manual mode is active
 * 26 - release stop using SCADA
 * 22 - move UP; 23 - move DOWN; 24 - move LEFT; 25 - move RIGHT
 * x and y are current absolute coordinates which has to be sync with: 
 * C.29 and C.30 (absolute coordinates in SCADA)
 */
class ManualController {
public:
  void manualMode(AbsMotorController amc, ScadaRouting sr){
    RelMotorController rmc = amc.getRelMotorController();
    Grabber grabber = rmc.getGrabber();
    while(sr.scanDataCoils(21) == 1){
      sr.scan();
      if(sr.scanDataCoils(26) == 1){
          grabber.releaseBrakes();
          while(sr.scanDataCoils(26) == 1){
          sr.scan();
         }
      }
      ifUpThenExecute(sr, amc, grabber, rmc);
      ifDownThenExecute(sr, amc, grabber, rmc);
      ifLeftThenExecute(sr, amc, grabber, rmc);
      ifRightThenExecute(sr, amc, grabber, rmc);
    }
  }
      
    void ifUpThenExecute(ScadaRouting sr, AbsMotorController amc, Grabber grabber, RelMotorController rmc) {
      if(sr.scanDataCoils(22) == 1){
        grabber.releaseBrakes();
        while(sr.scanDataCoils(22) == 1){ // moveUp
          moveUpManual(10, grabber, rmc);
          sendToScada(sr, amc.getX(), amc.getY());
        }
      }
      grabber.activateBrakes();
    }
  
    void ifDownThenExecute(ScadaRouting sr, AbsMotorController amc, Grabber grabber, RelMotorController rmc) {
      if(sr.scanDataCoils(23) == 1){
        grabber.releaseBrakes();
        while(sr.scanDataCoils(23) == 1){ // moveDown
          moveDownManual(10, grabber, rmc);
          sendToScada(sr, amc.getX(), amc.getY());
        }
      }
      grabber.activateBrakes();
    }
  
    void ifLeftThenExecute(ScadaRouting sr, AbsMotorController amc, Grabber grabber, RelMotorController rmc) {
      if(sr.scanDataCoils(24) == 1){
        grabber.releaseBrakes();
        while(sr.scanDataCoils(24) == 1){ // moveLeft
          moveLeftManual(10, grabber, rmc);
          sendToScada(sr, amc.getX(), amc.getY());
        }
      }
      grabber.activateBrakes();
    }
  
    void ifRightThenExecute(ScadaRouting sr, AbsMotorController amc, Grabber grabber, RelMotorController rmc) {
      if(sr.scanDataCoils(25) == 1){
        grabber.releaseBrakes();
        while(sr.scanDataCoils(25) == 1){ // moveRight
          moveRightManual(10, grabber, rmc);
          sendToScada(sr, amc.getX(), amc.getY());
        }
      }
      grabber.activateBrakes();
    }
   
    void sendToScada(ScadaRouting sr, int x, int y) {
           sr.writeDataRegisters(29, x); 
           sr.writeDataRegisters(30, y);
           sr.scan();
      }
    
    void moveLeftManual(int rel, Grabber grabber, RelMotorController rmc) {
      startMoving(true, true, rel, grabber, rmc);
    }
    
    void moveRightManual(int rel, Grabber grabber, RelMotorController rmc) {
      startMoving(false, false, rel, grabber, rmc);
    }
    
    void moveUpManual(int rel, Grabber grabber, RelMotorController rmc) {
      startMoving(false, true, rel, grabber, rmc);
    }
    
    void moveDownManual(int rel, Grabber grabber, RelMotorController rmc) {
      startMoving(true, false, rel, grabber, rmc);
    }
    
    void startMoving(boolean left, boolean right, int rel, Grabber grabber, RelMotorController rmc) {
       grabber.changeDir(left, grabber.getCwLeftMotor());
       grabber.changeDir(right, grabber.getCwRightMotor());
       rmc.moveMotors(rel);
    }
};
#endif
