//***************************************************************//
//  Author       : RedFox                                        //
//  Website      : lamchucongnghe.com                            //
//  Fanpage      : fb.com//lamchucongnghevn                      //
//  Shop sendo   : sendo.vn/shop/lamchucongnghe_com              //
//  Shop shopee  : shopee.vn/lamchucongnghe                      //
//***************************************************************//

#define dongCoTrai    13      // Đảo chiều động cơ trái ( 0: chạy thuận, 1: chạy ngược)
#define dongCoPhai    12      // Đảo chiều động cơ phải ( 1: chạy thuận, 0: chạy ngược)
#define bamXungTrai   11      // Băm xung điều chỉnh tốc độ động cơ trái
#define bamXungPhai   10      // Băm xung điều chỉnh tốc độ động cơ phải

int trangThai, trangThaiCu;

void setup() {
  Serial.begin(9600);
  pinMode(dongCoTrai, OUTPUT);
  pinMode(dongCoPhai, OUTPUT);
}

void loop() {
  trangThai = docDoLine(A0, A1, A2, A3, A4);     // Vị trí sensor tính từ trái sang phải,  Phát hiện line, trả về 0, Không có line, trả về 1
  Serial.println(trangThai, BIN);
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
  if(xungTrai >=0 )
    digitalWrite(dongCoTrai, HIGH);
  else
    digitalWrite(dongCoTrai, LOW);
  if(xungPhai >=0 )
    digitalWrite(dongCoPhai, HIGH);
  else
    digitalWrite(dongCoPhai, LOW);
  analogWrite(bamXungTrai, xungTrai);
  analogWrite(bamXungPhai, xungPhai);
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
