/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 16.01.2019 20:43:24
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/
#include "BusinessController.h"

  BusinessController bc;
  
  void setup(){}

  void loop() {
      bc.firstMove();
      delay(2000);
      bc.secondMove();
  }
