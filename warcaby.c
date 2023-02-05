#include "primlib.h"
#include <stdlib.h>

#define BOARD_SIZE 700
#define FIELD_SIZE (BOARD_SIZE / 10)

#define BEGIN_OF_BOARD_W (((gfx_screenWidth()  - 1) / 2) - (BOARD_SIZE / 2))
#define BEGIN_OF_BOARD_H (((gfx_screenHeight() - 1) / 2) - (BOARD_SIZE / 2))
#define END_OF_BOARD_W   (((gfx_screenWidth()  - 1) / 2) + (BOARD_SIZE / 2))
#define END_OF_BOARD_H   (((gfx_screenHeight() - 1) / 2) + (BOARD_SIZE / 2))

int WhitePawnsCounter = 15;
int BlackPawnsCounter = 15;

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

int isFieldEmpty(int x, int y, struct WhitePawn WPtab[], struct BlackPawn BPtab[]){
  for(int i = 0; i < 15; ++i){
    if((WPtab[i].xPosition == x) && (WPtab[i].yPosition == y))
      return 1;
    if((BPtab[i].xPosition == x) && (BPtab[i].yPosition == y))
      return 2;
  }
  return 0;
}

void makeCheckersBackground(void){
  gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLUE);
  gfx_filledRect(BEGIN_OF_BOARD_W, BEGIN_OF_BOARD_H, END_OF_BOARD_W, END_OF_BOARD_H, LIGHT_GREEN); 
  for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j){
      if(pow(-1, (i+j)) == 1)   //checking color of the field
        gfx_filledRect(BEGIN_OF_BOARD_W + (i * FIELD_SIZE), BEGIN_OF_BOARD_H + (j * FIELD_SIZE),
         BEGIN_OF_BOARD_W + (i * FIELD_SIZE) + FIELD_SIZE, BEGIN_OF_BOARD_H + (j * FIELD_SIZE) + FIELD_SIZE, LIGHT_YELLOW);
    }
  }
}

int WhiteLegalityCheck(struct WhitePawn *pawn, struct FieldSelection *select,struct WhitePawn WPtab[], struct BlackPawn BPtab[]){
  if((abs(pawn->xPosition - select->xPosition) != 1) || (abs(pawn->yPosition - select->yPosition) != 1))
    return 0;
  if(isFieldEmpty(select->xPosition, select->yPosition, WPtab, BPtab) == 1){
    return 0;
  }
 else if(isFieldEmpty(select->xPosition, select->yPosition, WPtab, BPtab) == 2){
    for(int i = 0; i < 15; ++i){
      if((select->xPosition == BPtab[i].xPosition) && (select->yPosition == BPtab[i].yPosition)){
        if(BlackPawnsCounter > 10){
          BPtab[i].xPosition = 10;
          BPtab[i].yPosition = 15 - BlackPawnsCounter; 
        }
        else if(BlackPawnsCounter > 5){
          BPtab[i].xPosition = 11;
          BPtab[i].yPosition = 10 - BlackPawnsCounter;
        }
        else{
          BPtab[i].xPosition = 12;
          BPtab[i].yPosition = 5 - BlackPawnsCounter;
        }
        --BlackPawnsCounter;

      }
    }
    return 1; 
  }




  return 1;
}

int BlackLegalityCheck(struct BlackPawn *pawn, struct FieldSelection *select,struct WhitePawn WPtab[], struct BlackPawn BPtab[]){
  if((abs(pawn->xPosition - select->xPosition) != 1) || (abs(pawn->yPosition - select->yPosition) != 1))
    return 0;
  if(isFieldEmpty(select->xPosition, select->yPosition, WPtab, BPtab) == 2){
    return 0;
  }
  else if(isFieldEmpty(select->xPosition, select->yPosition, WPtab, BPtab) == 1){
    for(int i = 0; i < 15; ++i){
      if((select->xPosition == WPtab[i].xPosition) && (select->yPosition == WPtab[i].yPosition)){
        if(WhitePawnsCounter > 10){
           WPtab[i].xPosition = -1;
           WPtab[i].yPosition = -6 + WhitePawnsCounter;
        }
        else if(WhitePawnsCounter > 5){
           WPtab[i].xPosition = -2;
           WPtab[i].yPosition = -1 + WhitePawnsCounter;
        }
        else{
           WPtab[i].xPosition = -3;
           WPtab[i].yPosition = 4 + WhitePawnsCounter;
        }
        --WhitePawnsCounter;
      }
    }
    return 1; 
  }
  return 1;
}


int main() {
  if (gfx_init())
    exit(3);



  struct FieldSelection FS;
  FS.xPosition = 3;
  FS.yPosition = 0;
  FS.whoseTurn = 1;
  FS.col = RED;


  struct WhitePawn WP[15];

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

  struct BlackPawn BP[15];

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
  int turn = 0;
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
        if(FS.yPosition > 0)
          FS.yPosition -= 1;
        break;

      case 's':
        if(FS.yPosition < 9)
          FS.yPosition += 1;
        break;

      case 'a':
        if(FS.xPosition > 0) 
          FS.xPosition -= 1;
        break;

      case 'd':
        if(FS.xPosition < 9)
          FS.xPosition += 1;
        break;

      case '\r':

        if(enterPressed == 0){
          if(turn == 0){
            for(int i = 0; i < 15; ++i){
              if((FS.xPosition == WP[i].xPosition) && FS.yPosition == WP[i].yPosition){
                WP[i].moving = 1;
                enterPressed = 1;
              }
            }
          }
          else{
            for(int i = 0; i < 15; ++i){
              if((FS.xPosition == BP[i].xPosition) && FS.yPosition == BP[i].yPosition){
                BP[i].moving = 1;
                enterPressed = 1;
              }
            }            
          }
        }
        else{
          if(turn == 0){
            for(int i = 0; i < 15; ++i){
              if(WP[i].moving == 1){
                if(WhiteLegalityCheck(&(WP[i]), &FS, WP, BP)){
                  WP[i].xPosition = FS.xPosition;
                  WP[i].yPosition = FS.yPosition;
                  WP[i].moving = 0;
                  enterPressed = 0;
                  turn = 1;
                }
                else{
                  enterPressed = 0;
                  WP[i].moving = 0;
                }
              }
            }
          }
          else{
            for(int i = 0; i < 15; ++i){
              if(BP[i].moving == 1){
                if(BlackLegalityCheck(&(BP[i]), &FS, WP, BP)){
                  BP[i].xPosition = FS.xPosition;
                  BP[i].yPosition = FS.yPosition;
                  BP[i].moving = 0;
                  enterPressed = 0;
                  turn = 0;
                }
                else{
                  enterPressed = 0;
                  BP[i].moving = 0;                 
                }
              }
            }            
          }
        }
        break;

        
      case -1:
        break;

    }


    gfx_rect(BEGIN_OF_BOARD_W + FIELD_SIZE * FS.xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE * FS.yPosition,
     BEGIN_OF_BOARD_W + FIELD_SIZE + FIELD_SIZE * FS.xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE + FIELD_SIZE * FS.yPosition, FS.col);

    gfx_rect(BEGIN_OF_BOARD_W - 1 + FIELD_SIZE * FS.xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE * FS.yPosition - 1,
     BEGIN_OF_BOARD_W + FIELD_SIZE + FIELD_SIZE * FS.xPosition - 1, BEGIN_OF_BOARD_H + FIELD_SIZE + FIELD_SIZE * FS.yPosition - 1, FS.col);

    gfx_rect(BEGIN_OF_BOARD_W + 1 + FIELD_SIZE * FS.xPosition, BEGIN_OF_BOARD_H + FIELD_SIZE * FS.yPosition + 1,
     BEGIN_OF_BOARD_W + FIELD_SIZE + FIELD_SIZE * FS.xPosition + 1, BEGIN_OF_BOARD_H + FIELD_SIZE + FIELD_SIZE * FS.yPosition + 1, FS.col);

    //for(int i = 0; i < 15; ++i){
      //if(!(WP + i * sizeof(*WP)))
    //    printf("Numer: %d x:%d, y:%d - FS: x:%d y:%d | moving:%d\n",i, WP[i].xPosition, WP[i].yPosition, FS.xPosition, FS.yPosition, WP[i].moving);
    //}
    //for(int i = 0; i < 15; ++i){
      //if(!(BP + i * sizeof(*BP)))
     //  printf("Numer: %d x:%d, y:%d - FS: x:%d y:%d | moving:%d\n",i, BP[i].xPosition, BP[i].yPosition, FS.xPosition, FS.yPosition, BP[i].moving);
    //}

    gfx_updateScreen();
    SDL_Delay(60);
}
  return 0;
}


