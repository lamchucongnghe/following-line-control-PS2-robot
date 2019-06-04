//***************************************************************//
//  Author       : RedFox                                        //
//  Website      : lamchucongnghe.com                            //
//  Fanpage      : fb.com//lamchucongnghevn                      //
//  Shop sendo   : sendo.vn/shop/lamchucongnghe_com              //
//  Shop shopee  : shopee.vn/lamchucongnghe                      //
//***************************************************************//

#include <PS2X_lib.h>

#define PS2_DAT       6       // Data Pin
#define PS2_CMD       7       // Command Pin
#define PS2_CS        8       // Attention Pin
#define PS2_CLK       9       // Clock Pin
#define dongCoTrai    13      // Đảo chiều động cơ trái ( 0: chạy thuận, 1: chạy ngược)
#define dongCoPhai    12      // Đảo chiều động cơ phải ( 1: chạy thuận, 0: chạy ngược)
#define bamXungTrai   11      // Băm xung điều chỉnh tốc độ động cơ trái
#define bamXungPhai   10      // Băm xung điều chỉnh tốc độ động cơ phải
#define Buzzer        4       // Chân còi chip
PS2X ps2;                     // create PS2 Controller Class

void setup() {
  Serial.begin(9600);
  // Khởi tạo còi chip, động cơ trái, động cơ phải là đầu ra
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW); 
  pinMode(dongCoTrai, OUTPUT);
  pinMode(dongCoPhai, OUTPUT);
  // Khởi tạo kết nối tay PS2
  ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_CS, PS2_DAT);
}

void loop() {
  // Bắt đầu đọc dữ liệu nhấn nút từ tay PS2
  ps2.read_gamepad();
  if(ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             // Tiến
    digitalWrite(dongCoTrai, LOW);
    analogWrite(bamXungTrai, 250);
    digitalWrite(dongCoPhai, HIGH);
    analogWrite(bamXungPhai, 250);
  } 
  if(!ps2.Button(PSB_PAD_UP) && ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             // Lùi
    digitalWrite(dongCoTrai, HIGH);
    analogWrite(bamXungTrai, 250);
    digitalWrite(dongCoPhai, LOW);
    analogWrite(bamXungPhai, 250);
  }
    
  if(!ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             // Quay trái
    digitalWrite(dongCoTrai, HIGH);
    analogWrite(bamXungTrai, 200);
    digitalWrite(dongCoPhai, HIGH);
    analogWrite(bamXungPhai, 200);
  }
  if(!ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && ps2.Button(PSB_PAD_RIGHT)) {             // Quay phải
    digitalWrite(dongCoTrai, LOW);
    analogWrite(bamXungTrai, 200);
    digitalWrite(dongCoPhai, LOW);
    analogWrite(bamXungPhai, 200);
  }
  if(ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             // Cua trái
    digitalWrite(dongCoTrai, LOW);
    analogWrite(bamXungTrai, 60);
    digitalWrite(dongCoPhai, HIGH);
    analogWrite(bamXungPhai, 250);
  }
  if(ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && ps2.Button(PSB_PAD_RIGHT)) {            // Cua phải
    digitalWrite(dongCoTrai, LOW);
    analogWrite(bamXungTrai, 250);
    digitalWrite(dongCoPhai, HIGH);
    analogWrite(bamXungPhai, 60);
  }
  if(!ps2.Button(PSB_PAD_UP) && ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && ps2.Button(PSB_PAD_RIGHT)) {            // Lùi phải
    digitalWrite(dongCoTrai, HIGH);
    analogWrite(bamXungTrai, 250);
    digitalWrite(dongCoPhai, LOW);
    analogWrite(bamXungPhai, 60);
  }
  if(!ps2.Button(PSB_PAD_UP) && ps2.Button(PSB_PAD_DOWN) && ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {            // Lùi trái
    digitalWrite(dongCoTrai, HIGH);
    analogWrite(bamXungTrai, 40);
    digitalWrite(dongCoPhai, LOW);
    analogWrite(bamXungPhai, 250);
  }
  if(!ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {         // Dừng khi nhả các nút
    analogWrite(bamXungTrai, 0);
    analogWrite(bamXungPhai, 0);
  }
  if(ps2.Button(PSB_R2))          // Hú còi
    digitalWrite(Buzzer, HIGH);
  else
    digitalWrite(Buzzer, LOW);    
}
