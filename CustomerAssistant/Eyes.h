#include "MCUFRIEND_kbv.h"

#define WHITE 0xFFFF
#define DARKGREY 0x7BEF

class Eyes {
    int screenWidth;
    int screenHeight;

  public:
    Eyes(int _screenWidth, int _screenHeight) {
      screenWidth = _screenWidth;
      screenHeight = _screenHeight;
    }

    void createEyes(MCUFRIEND_kbv tft) {
      tft.fillCircle(screenWidth / 4, screenHeight / 2, 50, WHITE);
      tft.fillCircle(screenWidth / 4 * 3, screenHeight / 2, 50, WHITE);

      delay(1000);

      tft.fillCircle(screenWidth / 4, screenHeight / 2, 50, DARKGREY);
      tft.fillCircle(screenWidth / 4 * 3, screenHeight / 2, 50, DARKGREY);

      delay(100);
    }
};
