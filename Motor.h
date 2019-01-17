#ifndef Motor_h  // если библиотека Motor не подключена
#define Motor_h  // тогда подключаем ее

#include <Arduino.h>

class Motor {

  private:
    byte _clkPin;          //pin for impulse
    byte _cwPin;            //pin for direction
    int _motorSpeed;
    
    public:
     Motor(byte clkPin, int motorSpeed, byte cwPin) {
        _clkPin = clkPin;
        _motorSpeed = motorSpeed;
        _cwPin = cwPin;
        pinMode(clkPin, OUTPUT);
        pinMode(cwPin, OUTPUT);
     }
     
     void moveMotor() {
        digitalWrite(_clkPin, HIGH);
        delayMicroseconds(_motorSpeed);
        digitalWrite(_clkPin, LOW);
        delayMicroseconds(_motorSpeed);
     }
     
     boolean getDir() {
        return digitalRead(_cwPin);
     }
};

#endif
