#include "primlib.h"
#include <stdlib.h>

#define BOARD_SIZE 700
#define FIELD_SIZE (BOARD_SIZE / 10)

#define BEGIN_OF_BOARD_W (((gfx_screenWidth()  - 1) / 2) - (BOARD_SIZE / 2))
#define BEGIN_OF_BOARD_H (((gfx_screenHeight() - 1) / 2) - (BOARD_SIZE / 2))
#define END_OF_BOARD_W   (((gfx_screenWidth()  - 1) / 2) + (BOARD_SIZE / 2))
#define END_OF_BOARD_H   (((gfx_screenHeight() - 1) / 2) + (BOARD_SIZE / 2))



struct WhitePawn{
    int xPosition;
    int yPosition;
    int size;
    int isKing;
    enum color c;
  };

void makeCheckersBackground(void){
  gfx_filledRect(BEGIN_OF_BOARD_W, BEGIN_OF_BOARD_H, END_OF_BOARD_W, END_OF_BOARD_H, LIGHT_GREEN); 
  for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j){
      if(pow(-1, (i+j)) == 1)   //checking color of the field
        gfx_filledRect(BEGIN_OF_BOARD_W + (i * FIELD_SIZE), BEGIN_OF_BOARD_H + (j * FIELD_SIZE), BEGIN_OF_BOARD_W + (i * FIELD_SIZE) + FIELD_SIZE, BEGIN_OF_BOARD_H + (j * FIELD_SIZE) + FIELD_SIZE, LIGHT_YELLOW);
    }
  }
  gfx_updateScreen();
}

void makePawns(void){


}

int main() {
  if (gfx_init())
    exit(3);
  makeCheckersBackground();

  struct WhitePawn *WP = malloc(15 * sizeof(*WP));

  int counter = 0;

  for(int i = 0; i <= 4; ++i, ++counter){
    WP[counter].xPosition = 2 * i;
    WP[counter].yPosition = 0;
    WP[counter].size = 15;
    WP[counter].isKing = 0;
    WP[counter].c = WHITE;
  }

  for(int i = 0; i <= 4; ++i, ++counter){
    WP[counter].xPosition = (2 * i) + 1;
    WP[counter].yPosition = 1;
    WP[counter].size = 15;
    WP[counter].isKing = 0;
    WP[counter].c = WHITE;
  }

  for(int i = 0; i <= 4; ++i, ++counter){
    WP[counter].xPosition = 2 * i;
    WP[counter].yPosition = 2;
    WP[counter].size = 15;
    WP[counter].isKing = 0;
    WP[counter].c = WHITE;
  }
  
  /*for(int i = 0; i < 15; ++i){
    printf("x:%d y:%d\n", WP[i].xPosition, WP[i].yPosition);
  }*/
  gfx_getkey();
  return 0;
}