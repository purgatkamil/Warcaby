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
    int outerSize;
    int innerSize;
    int isKing;
    enum color outerC;
    enum color innerC;
    int moving;
  };

  struct BlackPawn{
    int xPosition;
    int yPosition;
    int outerSize;
    int innerSize;
    int isKing;
    enum color outerC;
    enum color innerC;
    int moving;
  };

  struct FieldSelection{
      int xPosition;
      int yPosition;
      int whoseTurn;
      enum color col;
  };

void makeCheckersBackground(void){
  gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
  gfx_filledRect(BEGIN_OF_BOARD_W, BEGIN_OF_BOARD_H, END_OF_BOARD_W, END_OF_BOARD_H, LIGHT_GREEN); 
  for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j){
      if(pow(-1, (i+j)) == 1)   //checking color of the field
        gfx_filledRect(BEGIN_OF_BOARD_W + (i * FIELD_SIZE), BEGIN_OF_BOARD_H + (j * FIELD_SIZE),
         BEGIN_OF_BOARD_W + (i * FIELD_SIZE) + FIELD_SIZE, BEGIN_OF_BOARD_H + (j * FIELD_SIZE) + FIELD_SIZE, LIGHT_YELLOW);
    }
  }
}


int main() {
  if (gfx_init())
    exit(3);

  struct FieldSelection *FS = malloc(sizeof(*FS));
  FS[0].xPosition = 3;
  FS[0].yPosition = 0;
  FS[0].whoseTurn = 1;
  FS[0].col = RED;



  struct WhitePawn *WP = malloc(15 * sizeof(*WP));  //memory allocation for white pawns

  int counter = 0;

  //Creating structs objects that are representing white pawns
  for(int i = 0; i <= 4; ++i, ++counter){
    WP[counter].xPosition = ((2 * i) + 1);
    WP[counter].yPosition = 0;
    WP[counter].outerSize = 23;
    WP[counter].innerSize = 20;
    WP[counter].isKing = 0;
    WP[counter].outerC = BLACK;
    WP[counter].innerC = WHITE;
    WP[counter].moving = 0;
  }

  for(int i = 0; i <= 4; ++i, ++counter){
    WP[counter].xPosition = 2 * i;
    WP[counter].yPosition = 1;
    WP[counter].outerSize = 23;
    WP[counter].innerSize = 20;
    WP[counter].isKing = 0;
    WP[counter].outerC = BLACK;
    WP[counter].innerC = WHITE;
    WP[counter].moving = 0;
  }

  for(int i = 0; i <= 4; ++i, ++counter){
    WP[counter].xPosition = ((2 * i) + 1);
    WP[counter].yPosition = 2;
    WP[counter].outerSize = 23;
    WP[counter].innerSize = 20;
    WP[counter].isKing = 0;
    WP[counter].outerC = BLACK;
    WP[counter].innerC = WHITE;
    WP[counter].moving = 0;
  }

  struct BlackPawn *BP = malloc(15 * sizeof(*BP));  //memory allocation for black pawns

  counter = 0;

  //Creating structs objects that are representing black pawns
  for(int i = 0; i <= 4; ++i, ++counter){
    BP[counter].xPosition = 9 - ((2 * i) + 1);
    BP[counter].yPosition = 9;
    BP[counter].outerSize = 23;
    BP[counter].innerSize = 20;
    BP[counter].isKing = 0;
    BP[counter].outerC = BLACK;
    BP[counter].innerC = BLACK;
    BP[counter].moving = 0;
  }

  for(int i = 0; i <= 4; ++i, ++counter){
    BP[counter].xPosition = 9 - (2 * i);
    BP[counter].yPosition = 8;
    BP[counter].outerSize = 23;
    BP[counter].innerSize = 20;
    BP[counter].isKing = 0;
    BP[counter].outerC = BLACK;
    BP[counter].innerC = BLACK;
    BP[counter].moving = 0;
  }

  for(int i = 0; i <= 4; ++i, ++counter){
    BP[counter].xPosition = 9 - ((2 * i) + 1);
    BP[counter].yPosition = 7;
    BP[counter].outerSize = 23;
    BP[counter].innerSize = 20;
    BP[counter].isKing = 0;
    BP[counter].outerC = BLACK;
    BP[counter].innerC = BLACK;
    BP[counter].moving = 0;
  }
  int enterPressed = 0;
  while(1){

     makeCheckersBackground();

    //Drawing pawns in starting positions
    for(int i = 0; i < 15; ++i){
      gfx_filledCircle((BEGIN_OF_BOARD_W + (FIELD_SIZE / 2) + (FIELD_SIZE * WP[i].xPosition)), (BEGIN_OF_BOARD_H + (FIELD_SIZE / 2) + (FIELD_SIZE * WP[i].yPosition)), WP[i].outerSize, WP[i].outerC);
      gfx_filledCircle((BEGIN_OF_BOARD_W + (FIELD_SIZE / 2) + (FIELD_SIZE * WP[i].xPosition)), (BEGIN_OF_BOARD_H + (FIELD_SIZE / 2) + (FIELD_SIZE * WP[i].yPosition)), WP[i].innerSize, WP[i].innerC);
    }
    for(int i = 0; i < 15; ++i){
      gfx_filledCircle((BEGIN_OF_BOARD_W + (FIELD_SIZE / 2) + (FIELD_SIZE * BP[i].xPosition)), (BEGIN_OF_BOARD_H + (FIELD_SIZE / 2) + (FIELD_SIZE * BP[i].yPosition)), BP[i].outerSize, BP[i].outerC);
      gfx_filledCircle((BEGIN_OF_BOARD_W + (FIELD_SIZE / 2) + (FIELD_SIZE * BP[i].xPosition)), (BEGIN_OF_BOARD_H + (FIELD_SIZE / 2) + (FIELD_SIZE * BP[i].yPosition)), BP[i].innerSize, BP[i].innerC);
    }
    
    

    switch (gfx_pollkey()){
      
      case 'w':
        if(FS[0].yPosition > 0)
          FS[0].yPosition -= 1;
        break;

      case 's':
        if(FS[0].yPosition < 9)
          FS[0].yPosition += 1;
        break;

      case 'a':
        if(FS[0].xPosition > 0) 
          FS[0].xPosition -= 1;
        break;

      case 'd':
        if(FS[0].xPosition < 9)
          FS[0].xPosition += 1;
        break;

      case '\r':
        if(enterPressed == 0){
          enterPressed = 1;
          for(int i = 0; i < 15; ++i){
            if((FS[0].xPosition == WP[i].xPosition) && FS[0].yPosition == WP[i].yPosition){
              WP[i].moving = 1;
            }
          }
        }
        else{
          for(int i = 0; i < 15; ++i){
            if(WP[i].moving == 1){
              WP[i].xPosition = FS[0].xPosition;
              WP[i].yPosition = FS[0].yPosition;
              WP[i].moving = 0;
              enterPressed = 0;
            }
          }
        }

      case -1:
        break;

    }

    gfx_rect(BEGIN_OF_BOARD_W + FIELD_SIZE * FS[0].xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE * FS[0].yPosition,
     BEGIN_OF_BOARD_W + FIELD_SIZE + FIELD_SIZE * FS[0].xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE + FIELD_SIZE * FS[0].yPosition, FS[0].col);

    gfx_rect(BEGIN_OF_BOARD_W - 1 + FIELD_SIZE * FS[0].xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE * FS[0].yPosition - 1,
     BEGIN_OF_BOARD_W + FIELD_SIZE + FIELD_SIZE * FS[0].xPosition - 1, BEGIN_OF_BOARD_H + FIELD_SIZE + FIELD_SIZE * FS[0].yPosition - 1, FS[0].col);

    gfx_rect(BEGIN_OF_BOARD_W + 1 + FIELD_SIZE * FS[0].xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE * FS[0].yPosition + 1,
     BEGIN_OF_BOARD_W + FIELD_SIZE + FIELD_SIZE * FS[0].xPosition + 1, BEGIN_OF_BOARD_H + FIELD_SIZE + FIELD_SIZE * FS[0].yPosition + 1, FS[0].col);

    /*for(int i = 0; i < 15; ++i){
        printf("Numer: %d x:%d, y:%d - FS: x:%d y:%d | moving:%d\n",i, WP[i].xPosition, WP[i].yPosition, FS[0].xPosition, FS[0].yPosition, WP[i].moving);
    }*/

    gfx_updateScreen();
    SDL_Delay(60);
}
  return 0;
}