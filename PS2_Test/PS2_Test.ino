//***************************************************************//
//  Author       : RedFox                                        //
//  Website      : lamchucongnghe.com                            //
//  Fanpage      : fb.com//lamchucongnghevn                      //
//  Shop sendo   : sendo.vn/shop/lamchucongnghe_com              //
//  Shop shopee  : shopee.vn/lamchucongnghe                      //
//***************************************************************//

#include <PS2X_lib.h>

#define PS2_DAT     8       // Data Pin
#define PS2_CMD     9       // Command Pin
#define PS2_CS      10      // Attention Pin
#define PS2_CLK     11      // Clock Pin

PS2X ps2;                   // create PS2 Controller Class

void setup() {
  Serial.begin(9600);
  delay(300);
  // setup pins and settings: GamePad(clock, command, attention, data) check for error
  int ps2Config = ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_CS, PS2_DAT);
}

void loop() {
  ps2.read_gamepad();
  if(ps2.ButtonPressed(PSB_PAD_UP))
    Serial.println("Press UP");
  if(ps2.ButtonPressed(PSB_PAD_DOWN))
    Serial.println("Press DOWN");
  if(ps2.ButtonPressed(PSB_PAD_LEFT))
    Serial.println("Press LEFT");
  if(ps2.ButtonPressed(PSB_PAD_RIGHT))
    Serial.println("Press RIGHT");
  if(ps2.ButtonPressed(PSB_TRIANGLE))
    Serial.println("Press Y");
  if(ps2.ButtonPressed(PSB_CIRCLE))
    Serial.println("Press B");
  if(ps2.ButtonPressed(PSB_CROSS))
    Serial.println("Press A");
  if(ps2.ButtonPressed(PSB_SQUARE))
    Serial.println("Press X");
  if(ps2.ButtonPressed(PSB_L1))
    Serial.println("Press L1");
  if(ps2.ButtonPressed(PSB_L2))
    Serial.println("Press L2");
  if(ps2.ButtonPressed(PSB_L3))
    Serial.println("Press L3");
  if(ps2.ButtonPressed(PSB_R1))
    Serial.println("Press R1");
  if(ps2.ButtonPressed(PSB_R2))
    Serial.println("Press R2");
  if(ps2.ButtonPressed(PSB_R3))
    Serial.println("Press R3");
  if(ps2.Button(PSB_L1) || ps2.Button(PSB_R1)) { //print stick values if either is TRUE
    Serial.print("Stick Values:");
    Serial.print(ps2.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
    Serial.print(",");
    Serial.print(ps2.Analog(PSS_LX), DEC); 
    Serial.print(",");
    Serial.print(ps2.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2.Analog(PSS_RX), DEC); 
  }     
  delay(50);
}
