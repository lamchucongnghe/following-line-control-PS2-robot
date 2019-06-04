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

PS2X ps2;                     // create PS2 Controller Class

int doLine, trangThai, trangThaiCu;
void setup() {
  Serial.begin(9600);
  // Khởi tạo còi chip, động cơ trái, động cơ phải là đầu ra
  pinMode(dongCoTrai, OUTPUT);
  pinMode(dongCoPhai, OUTPUT);
  // Khởi tạo kết nối tay PS2
  ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_CS, PS2_DAT);
}

void loop() {
  // Bắt đầu đọc dữ liệu nhấn nút từ tay PS2
  ps2.read_gamepad();
  
  
  if(ps2.ButtonPressed(PSB_R2))          // Bật tắt chế độ dò line
    doLine = 1 - doLine;
  
  if(doLine) {
    chayDoLine();
    Serial.println("doLine ON");
  }
  else {
    // Tiến
    if(ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             
      dkDongCo(250, 250);
    }
    // Lùi
    if(!ps2.Button(PSB_PAD_UP) && ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             
      dkDongCo(-250, -250);
    }
    
    // Quay trái
    if(!ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             
      dkDongCo(-200, 200);
    }
    // Quay phải
    if(!ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && ps2.Button(PSB_PAD_RIGHT)) {             
      dkDongCo(200, -200);
    }
    // Cua trái
    if(ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {             
      dkDongCo(0, 250);
    }
    // Cua phải
    if(ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && ps2.Button(PSB_PAD_RIGHT)) {            
      dkDongCo(250, 0);
    }
    // Lùi phải
    if(!ps2.Button(PSB_PAD_UP) && ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && ps2.Button(PSB_PAD_RIGHT)) {            
      dkDongCo(-250, 0);
    }
    // Lùi trái
    if(!ps2.Button(PSB_PAD_UP) && ps2.Button(PSB_PAD_DOWN) && ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {            
      dkDongCo(0, -250);
    }
    // Dừng khi nhả các nút
    if(!ps2.Button(PSB_PAD_UP) && !ps2.Button(PSB_PAD_DOWN) && !ps2.Button(PSB_PAD_LEFT) && !ps2.Button(PSB_PAD_RIGHT)) {
      dkDongCo(0, 0);
    }
  }
}

void chayDoLine() {
  trangThai = docDoLine(A0, A1, A2, A3, A4);     // Vị trí sensor tính từ trái sang phải,  Phát hiện line, trả về 0, Không có line, trả về 1
  if(trangThai == 0x1F || trangThai == 0 || trangThai == 0x0E)
    trangThai = trangThaiCu;
  else
    trangThaiCu = trangThai;
  switch(trangThai) {
    case 0x01:    // 0b00000001
    case 0x02:    // 0b00000010
    case 0x03:    // 0b00000011
    case 0x06:    // 0b00000110
    case 0x07:    // 0b00000111
    case 0x0F:    // 0b00001111
              dkDongCo(250, 0);
              break;
    case 0x04:    //  0b00000100
              dkDongCo(250, 250);
              break;
    case 0x0C:    // 0b00001100
    case 0x08:    // 0b00001000
    case 0x10:    // 0b00010000
    case 0x18:    // 0b00011000
    case 0x1C:    // 0b00011100
    case 0x1E:    // 0b00011110
              dkDongCo(0, 250);
              break;
  }
}

void dkDongCo(float xungTrai, float xungPhai) {
  Serial.print(xungTrai);
  Serial.print("\t");
  Serial.println(xungPhai);
  if(xungTrai >=0 )
    digitalWrite(dongCoTrai, HIGH);
  else
    digitalWrite(dongCoTrai, LOW);
  if(xungPhai >=0 )
    digitalWrite(dongCoPhai, HIGH);
  else
    digitalWrite(dongCoPhai, LOW);
  analogWrite(bamXungTrai, abs(xungTrai));
  analogWrite(bamXungPhai, abs(xungPhai));
}

uint8_t docDoLine(int sensor1, int sensor2, int sensor3, int sensor4, int sensor5) {
  int val;
  val = digitalRead(sensor1);
  val = val<<1 | digitalRead(sensor2);
  val = val<<1 | digitalRead(sensor3);
  val = val<<1 | digitalRead(sensor4);
  val = val<<1 | digitalRead(sensor5);
  return val;
}
