#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED 디스플레이 너비(픽셀 단위)
#define SCREEN_HEIGHT 64 // OLED 디스플레이 높이(픽셀 단위)

// I2C(SDA, SCL 핀)에 연결된 SSD1306 디스플레이에 대한 선언
#define OLED_RESET     -1 // 리셋 핀 #(또는 Arduino 리셋 핀을 공유하는 경우 -1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // 애니메이션 예제의 눈송이 수

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = 내부적으로 3.3V에서 디스플레이 전압 생성
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // 진행하지 않고 계속 반복합니다.
  }

  // 화면에 초기 디스플레이 버퍼 내용 표시 --
  // 라이브러리는 Adafruit 시작 화면으로 이것을 초기화합니다.
  display.display();
  delay(2000); //  2초간 정지

  //버퍼 비우기
  display.clearDisplay();

  // 단일 픽셀을 흰색으로 그립니다.
  display.drawPixel(10, 10, WHITE);

  // 디스플레이 버퍼를 화면에 표시합니다. 이후에 display()를 호출해야 합니다.
  // 화면에 보이도록 명령을 그립니다!
  display.display();
  delay(2000);
  // display.display()는 매 그리기 명령마다 필요하지 않습니다.
  // 원하는 것이 아니라면...오히려 여러 개를 일괄 처리할 수 있습니다.
  // 드로잉 작업 후 호출하여 한번에 화면 업데이트
  // 디스플레이.디스플레이(). 이 예제는 두 가지 접근 방식을 모두 보여줍니다...

  testdrawline();      // 여러 줄 그리기

  testdrawrect();      // 사각형 그리기(윤곽선)

  testfillrect();      // 사각형 그리기(채워짐)

  testdrawcircle();    // 원 그리기(윤곽선)

  testfillcircle();    // 원 그리기(채워짐)

  testdrawroundrect(); // 둥근 사각형 그리기(윤곽선)

  testfillroundrect(); // 둥근 사각형을 그립니다(채워짐).

  testdrawtriangle();  // 삼각형 그리기(윤곽선)

  testfilltriangle();  // 삼각형 그리기(채움)

  testdrawchar();      // 기본 글꼴의 문자 그리기

  testdrawstyles();    // 스타일화된' 문자 그리기

  testscrolltext();    // 스크롤 텍스트 그리기

  testdrawbitmap();    // 작은 비트맵 이미지를 그립니다

  // 디스플레이 반전 및 복원, 중간에 일시 중지
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}

void loop() {
}

void testdrawline() {
  int16_t i;

  display.clearDisplay(); // 디스플레이 버퍼 지우기

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display(); // 새로 그린 각 선으로 화면 업데이트
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
    display.display();
    delay(1);
  }

  delay(2000); // 2초간 정지
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display(); // 새로 그린 각 사각형으로 화면을 업데이트합니다
    delay(1);
  }

  delay(2000);
}

void testfillrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=3) {
    // INVERSE 색상이 사용되므로 직사각형이 흰색/검정색으로 번갈아 나타납니다
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, INVERSE);
    display.display(); // 새로 그린 각 사각형으로 화면을 업데이트합니다
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
    // TINVERSE 색상이 사용되므로 원이 흰색/검정색으로 번갈아 나타납니다
    display.fillCircle(display.width() / 2, display.height() / 2, i, INVERSE);
    display.display(); // 새로 그린 각 원으로 화면 업데이트
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // INVERSE 색상이 사용되므로 둥근 사각형이 흰색/검은색을 번갈아 사용합니다
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // 삼각형이 흰색/검은색으로 번갈아 나타나도록 INVERSE 색상이 사용됩니다
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // 일반 1:1 픽셀 스케일
  display.setTextColor(WHITE); // 흰색 텍스트 그리기
  display.setCursor(0, 0);     // 왼쪽 상단에서 시작
  display.cp437(true);         // 전체 256자 '코드 페이지 437' 글꼴 사용

  // 모든 문자가 디스플레이에 표시되는 것은 아닙니다. 이것은 정상입니다.
  // 라이브러리는 가능한 모든 것을 그리고 나머지는 잘립니다.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // 일반 1:1 픽셀 스케일
  display.setTextColor(WHITE);        // 흰색 텍스트 그리기
  display.setCursor(0,0);             // 왼쪽 상단에서 시작 
  display.println(F("Hello, world!"));

  display.setTextColor(BLACK, WHITE); // '역' 텍스트 그리기
  display.println(3.141592);

  display.setTextSize(2);             // 2X 스케일 텍스트 그리기
  display.setTextColor(WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // 2X 스케일 텍스트 그리기
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // 초기 텍스트 표시
  delay(100);

  // 다양한 방향으로 스크롤하고 중간에 일시 중지합니다.
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

#define XPOS   0 // 아래 함수의 'icons' 배열에 대한 인덱스
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // '눈송이' 위치 초기화
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // 무한 반복...
    display.clearDisplay(); //디스플레이 버퍼 지우기

    // 각 눈송이를 그립니다.
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }

    display.display(); // 디스플레이 버퍼를 화면에 표시
    delay(200);        // 1/10초 동안 일시 중지

    // 그런 다음 각 플레이크의 좌표를 업데이트합니다...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // 눈송이가 화면 하단에서 벗어난 경우...
      if (icons[f][YPOS] >= display.height()) {
        // 임의의 위치로 다시 초기화합니다.
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}