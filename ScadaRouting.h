#ifndef ScadaRouting_h  // если библиотека ScadaRouting_h не подключена
#define ScadaRouting_h  // тогда подключаем ее

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Mudbus.h"

class ScadaRouting {
  private:
    Mudbus Mb;
    byte ROWS = 4;
    byte COLS = 3;
    char keys[4][3] = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'*','0','#'}
    };
    byte rowPins[4] = {28, 27, 26, 25};
    byte colPins[3] = {24, 23, 22};

  public:
    ScadaRouting(){
        uint8_t mac[]     = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
        uint8_t ip[]      = { 192, 168, 1, 100 };
        uint8_t gateway[] = { 192, 168, 0, 4 };
        uint8_t subnet[]  = { 255, 255, 255, 0 };
        Ethernet.begin(mac, ip, gateway, subnet);
    }

    void scan(){
      Mb.Run();    
    }

    boolean scanDataCoils(byte address) {
      return Mb.C[address];
    }

    void writeDataRegisters(byte address, int data) {
      Mb.R[address] = data;  
    }
    void writeDataCoils(byte address, int data) {
      Mb.R[address] = data;  
    }
    void sendData(int redPartCount, int transparentPartCount, int metalPartCount, int colorNumber){
        Mb.Run();
        Mb.R[31] = redPartCount;
        Mb.R[32] = transparentPartCount;
        Mb.R[33] = metalPartCount;
        Mb.R[34] = colorNumber;
        Mb.Run();
    }
    void setCoordinates(int x, int y) {
      Mb.Run();
      Mb.R[26] = x;
      Mb.R[27] = y;
      Mb.Run();
    }
};
#endif
