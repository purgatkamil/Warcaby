#include "primlib.h"
#include <stdlib.h>

#define BEGIN_OF_BOARD_W (((gfx_screenWidth()  - 1) / 2) - 250)
#define BEGIN_OF_BOARD_H (((gfx_screenHeight() - 1) / 2) - 250)
#define END_OF_BOARD_W   (((gfx_screenWidth()  - 1) / 2) + 250)
#define END_OF_BOARD_H   (((gfx_screenHeight() - 1) / 2) + 250)


void makeCheckersBackground(void){
  gfx_filledRect(BEGIN_OF_BOARD_W, BEGIN_OF_BOARD_H, END_OF_BOARD_W, END_OF_BOARD_H, LIGHT_GREEN);  //board size is 500px x 500px
  //gfx_filledRect(BEGIN_OF_BOARD_W + (50 * 0), BEGIN_OF_BOARD_H + (50 * 0), BEGIN_OF_BOARD_W + (50* 2), BEGIN_OF_BOARD_H + (50 * 1), LIGHT_YELLOW);
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      if(pow(-1, (i+j)) == 1){
        gfx_filledRect(BEGIN_OF_BOARD_W + (i * 50), BEGIN_OF_BOARD_H + (j * 50), BEGIN_OF_BOARD_W + (i * 50) + 50, BEGIN_OF_BOARD_H + (j * 50) + 50, LIGHT_YELLOW);
      }
    }
  }

}

int main() {
  if (gfx_init())
    exit(3);
  makeCheckersBackground();
  //gfx_filledRect(BEGIN_OF_BOARD_W, BEGIN_OF_BOARD_H, END_OF_BOARD_W, END_OF_BOARD_H, LIGHT_GREEN);  //board size is 500px x 500px
  /* clear screen */
  //gfx_filledRect(0, 0, 500, 500, BLUE);
  //gfx_filledCircle(gfx_screenWidth() / 2, gfx_screenHeight() / 4, 100, YELLOW);
  gfx_updateScreen();
  gfx_getkey();
  return 0;
}