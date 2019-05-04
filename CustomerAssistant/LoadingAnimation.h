#include "MCUFRIEND_kbv.h"

#define BLACK 0x0000
#define WHITE 0xFFFF

class LoadingAnimation {
    int col[8];
    int screenWidth;
    int screenHeight;

  public:
    LoadingAnimation(int RequestedScreenWidth, int RequestedScreenHeight) {
      screenWidth = RequestedScreenWidth;
      screenHeight = RequestedScreenHeight;
    }

    void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg, MCUFRIEND_kbv tft) {
      int16_t x1, y1;
      uint16_t wid, ht;
      tft.setFont(f);
      tft.setCursor(x, y);
      tft.setTextColor(WHITE);
      tft.setTextSize(sz);
      tft.print(msg);
    }

    void loadParameters(MCUFRIEND_kbv tft) {
      showmsgXY(screenWidth / 2 - 35, screenHeight / 2 + 60, 1, &FreeSans9pt7b, "Loading...", tft);

      //Loading
      col[0] = tft.color565(155, 0, 50);
      col[1] = tft.color565(170, 30, 80);
      col[2] = tft.color565(195, 60, 110);
      col[3] = tft.color565(215, 90, 140);
      col[4] = tft.color565(230, 120, 170);
      col[5] = tft.color565(250, 150, 200);
      col[6] = tft.color565(255, 180, 220);
      col[7] = tft.color565(255, 210, 240);
    }

    void loadAnimation(MCUFRIEND_kbv tft) {
      tft.fillScreen(BLACK);

      //Loading Animation
      showmsgXY(screenWidth / 2 - 35, screenHeight / 2 + 60, 1, &FreeSans9pt7b, "Loading...", tft);
      for (int i = 48; i > 0; i--) {
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-i * PI / 4)), screenHeight / 2 + 40 * (sin(-i * PI / 4)) - 40, 10, col[0]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 1)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 1)*PI / 4)) - 40, 10, col[1]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 2)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 2)*PI / 4)) - 40, 10, col[2]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 3)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 3)*PI / 4)) - 40, 10, col[3]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 4)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 4)*PI / 4)) - 40, 10, col[4]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 5)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 5)*PI / 4)) - 40, 10, col[5]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 6)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 6)*PI / 4)) - 40, 10, col[6]); delay(15);
        tft.fillCircle(screenWidth / 2 + 40 * (cos(-(i + 7)*PI / 4)), screenHeight / 2 + 40 * (sin(-(i + 7)*PI / 4)) - 40, 10, col[7]); delay(15);
      }
    }
};
