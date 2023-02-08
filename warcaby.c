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

int (*FindLegalMoves_White(int xPosition, int yPosition, int (*Board)[10]))[3]{
  static int LegalMovesW[4][3] = {{-1, -1, 0},{-1, -1, 0},{-1, -1, 0},{-1, -1, 0}};
  int LegalMovesCounter = 0;

    if(Board[(xPosition) + 1][(yPosition) + 1] == 0){
      LegalMovesW[LegalMovesCounter][0] = (xPosition) + 1;
      LegalMovesW[LegalMovesCounter][1] = (yPosition) + 1;
      ++LegalMovesCounter;
    }
    else if(Board[(xPosition) + 1][(yPosition) + 1] == 2){
      if(Board[(xPosition) + 2][(yPosition) + 2] == 0){
        LegalMovesW[LegalMovesCounter][0] = (xPosition) + 2;
        LegalMovesW[LegalMovesCounter][1] = (yPosition) + 2;
        LegalMovesW[LegalMovesCounter][2] = 1;
        ++LegalMovesCounter;  
      }
    }

    if(Board[(xPosition) - 1][(yPosition) + 1] == 0){
      LegalMovesW[LegalMovesCounter][0] = (xPosition) - 1;
      LegalMovesW[LegalMovesCounter][1] = (yPosition) + 1;
      ++LegalMovesCounter;
    }
    else if(Board[(xPosition) - 1][(yPosition) + 1] == 2){
      if(Board[(xPosition) - 2][(yPosition) + 2] == 0){
        LegalMovesW[LegalMovesCounter][0] = (xPosition) - 2;
        LegalMovesW[LegalMovesCounter][1] = (yPosition) + 2;
        LegalMovesW[LegalMovesCounter][2] = 1;
        ++LegalMovesCounter;      
      }
    }

    if(Board[(xPosition) + 1][(yPosition) - 1] == 2){
      if(Board[(xPosition) + 2][(yPosition) - 2] == 0){
        LegalMovesW[LegalMovesCounter][0] = (xPosition) - 2;
        LegalMovesW[LegalMovesCounter][1] = (yPosition) + 2;
        LegalMovesW[LegalMovesCounter][2] = 1;
        ++LegalMovesCounter;
      }
    }

    if(Board[(xPosition) - 1][(yPosition) - 1] == 2){
      if(Board[(xPosition) - 2][(yPosition) - 2] == 0){
        LegalMovesW[LegalMovesCounter][0] = (xPosition) - 2;
        LegalMovesW[LegalMovesCounter][1] = (yPosition) + 2;
        LegalMovesW[LegalMovesCounter][2] = 1;
        ++LegalMovesCounter;
      }
    }
  int CaptureAvailable = 0;
  for(int i = 0; i < 4; ++i){
    if(LegalMovesW[i][2] == 1)
      CaptureAvailable = 1;
  }
  if(CaptureAvailable == 1){
    for(int i = 0; i < 4; ++i){
      if(LegalMovesW[i][2] == 0){
        LegalMovesW[i][0] = -1;
        LegalMovesW[i][1] = -1;
      }
    }
  }

  return LegalMovesW;
}

int WhiteLegalityCheck(struct WhitePawn *pawn, struct FieldSelection *select, struct WhitePawn WPtab[], struct BlackPawn BPtab[], int (*Board)[10]){
  int (*LegalMoves)[3] = FindLegalMoves_White(pawn->xPosition, pawn->yPosition, Board);
  for(int i = 0; i < 4; ++i){
    printf("%d,%d,%d\n", LegalMoves[i][0], LegalMoves[i][1], LegalMoves[i][2]);
  }

  for(int i = 0; i < 4; ++i){
    if((LegalMoves[i][0] == select->xPosition) && (LegalMoves[i][1] == select->yPosition)){
      int X = LegalMoves[i][0];
      int Y = LegalMoves[i][1];
      if(LegalMoves[i][2] == 1){
        for(int i = 0; i < 15; ++i){
          int averageX = 0;
          int averageY = 0;
          averageX = (X + pawn->xPosition) / 2;
          averageY = (Y + pawn->yPosition) / 2;
          printf("SrednieX:%d, SrednieY:%d, BPx:%d, BPy:%d\n", averageX, averageY, BPtab[i].xPosition, BPtab[i].yPosition);
          if((averageX == BPtab[i].xPosition) && (averageY == BPtab[i].yPosition)){
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
      }
      return 1;
    }
  }   

  /*for(int i = 0; i < 4; ++i){
    printf("[%d, %d, %d]", LegalMoves[i][0], LegalMoves[i][1], LegalMoves[i][2]);
  }
  printf("\n");*/

  return 0;
}

int (*FindLegalMoves_Black(int xPosition, int yPosition, int (*Board)[10]))[3]{
  static int LegalMovesB[4][3] = {{-1, -1, 0},{-1, -1, 0},{-1, -1, 0},{-1, -1, 0}};
  int LegalMovesCounter = 0;

  if(Board[(xPosition) - 1][(yPosition) - 1] == 0){
    LegalMovesB[LegalMovesCounter][0] = (xPosition) - 1;
    LegalMovesB[LegalMovesCounter][1] = (yPosition) - 1;
    LegalMovesB[LegalMovesCounter][2] = 0;
    ++LegalMovesCounter;
  }
  else if(Board[(xPosition) - 1][(yPosition) - 1] == 1){
    if(Board[(xPosition) - 2][(yPosition) - 2] == 0){
      LegalMovesB[LegalMovesCounter][0] = (xPosition) - 2;
      LegalMovesB[LegalMovesCounter][1] = (yPosition) - 2;
      LegalMovesB[LegalMovesCounter][2] = 1;
      ++LegalMovesCounter;  
    }
  }

  if(Board[(xPosition) + 1][(yPosition) - 1] == 0){
    LegalMovesB[LegalMovesCounter][0] = (xPosition) + 1;
    LegalMovesB[LegalMovesCounter][1] = (yPosition) - 1;
    LegalMovesB[LegalMovesCounter][2] = 0;
    ++LegalMovesCounter;
  }
  else if(Board[(xPosition) + 1][(yPosition) - 1] == 1){
    if(Board[(xPosition) + 2][(yPosition) - 2] == 0){
      LegalMovesB[LegalMovesCounter][0] = (xPosition) + 2;
      LegalMovesB[LegalMovesCounter][1] = (yPosition) - 2;
      LegalMovesB[LegalMovesCounter][2] = 1;
      ++LegalMovesCounter;      
    }
  }

  if(Board[(xPosition) - 1][(yPosition) + 1] == 1){
    if(Board[(xPosition) - 2][(yPosition) + 2] == 0){
      LegalMovesB[LegalMovesCounter][0] = (xPosition) - 2;
      LegalMovesB[LegalMovesCounter][1] = (yPosition) + 2;
      LegalMovesB[LegalMovesCounter][2] = 1;
      ++LegalMovesCounter;
    }
  }

  if(Board[(xPosition) + 1][(yPosition) + 1] == 1){
    if(Board[(xPosition) + 2][(yPosition) + 2] == 0){
      LegalMovesB[LegalMovesCounter][0] = (xPosition) + 2;
      LegalMovesB[LegalMovesCounter][1] = (yPosition) + 2;
      LegalMovesB[LegalMovesCounter][2] = 1;
      ++LegalMovesCounter;
    }
  }

  int CaptureAvailable = 0;
  for(int i = 0; i < 4; ++i){
    if(LegalMovesB[i][2] == 1)
      CaptureAvailable = 1;
  }
  if(CaptureAvailable == 1){
    for(int i = 0; i < 4; ++i){
      if(LegalMovesB[i][2] == 0){
        LegalMovesB[i][0] = -1;
        LegalMovesB[i][1] = -1;

      }
    }
  }

  return LegalMovesB;
}

int BlackLegalityCheck(struct BlackPawn *pawn, struct FieldSelection *select, struct WhitePawn WPtab[], struct BlackPawn BPtab[], int (*Board)[10]){
  
// <------------
  int AllLegalMoves[15][4][3];
  for(int i = 0; i < 15; ++i){
    int (*LegalMoves)[3] = FindLegalMoves_Black(BPtab[i].xPosition, BPtab[i].yPosition, Board);
    for(int j = 0; j < 4; ++j){

      AllLegalMoves[i][j][0] = LegalMoves[j][0];
      AllLegalMoves[i][j][1] = LegalMoves[j][1];
      AllLegalMoves[i][j][2] = LegalMoves[j][2];
    }
  }

  for(int i = 0; i < 15; ++i){
    for(int j = 0; j < 4; ++j){
      if(AllLegalMoves[i][j][2] == 0){
        continue;
      }
      else{
        printf("[Nr:%d, x:%d,y:%d, C:%d Aktualne koordy: x:%d,y:%d]\n", i, AllLegalMoves[i][j][0], AllLegalMoves[i][j][1], AllLegalMoves[i][j][2], BPtab[i].xPosition, BPtab[i].yPosition);        
      }

    }
  }

  printf("\n");
// <------------
  int (*LegalMoves)[3] = FindLegalMoves_Black(pawn->xPosition, pawn->yPosition, Board); // <------------
  for(int i = 0; i < 4; ++i){
    if((LegalMoves[i][0] == select->xPosition) && (LegalMoves[i][1] == select->yPosition)){
      int X = LegalMoves[i][0];
      int Y = LegalMoves[i][1];
      if(LegalMoves[i][2] == 1){
        for(int i = 0; i < 15; ++i){
          int averageX = 0;
          int averageY = 0;
          averageX = (X + pawn->xPosition) / 2;
          averageY = (Y + pawn->yPosition) / 2;
          if((averageX == WPtab[i].xPosition) && (averageY == WPtab[i].yPosition)){
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
      }

      return 1;
    }
  }  

 

  for(int i = 0; i < 4; ++i){
    printf("[%d, %d, %d]", LegalMoves[i][0], LegalMoves[i][1], LegalMoves[i][2]);
  }
  printf("\n");

  return 0;
}


void BoardUpdate(int (*Board)[10], struct WhitePawn WPtab[], struct BlackPawn BPtab[]){
  for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j){
      Board[i][j] = 0;
    }
  }
  for(int i = 0; i < 15; ++i){
    int xW = WPtab[i].xPosition;
    int yW = WPtab[i].yPosition;
    int xB = BPtab[i].xPosition;
    int yB = BPtab[i].yPosition;
    Board[xW][yW] = 1;
    Board[xB][yB] = 2;
  }
  printf("______________________________\n");
    for(int j = 0; j < 10; ++j){
      for(int i = 0; i < 10; ++i){
        printf(" %d ", Board[i][j]);
      }
     printf("\n");
    }  
  printf("______________________________\n");
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
  int BoardMatrix[10][10];
  BoardUpdate(BoardMatrix, WP, BP);

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
                if(WhiteLegalityCheck(&(WP[i]), &FS, WP, BP, BoardMatrix)){
                  WP[i].xPosition = FS.xPosition;
                  WP[i].yPosition = FS.yPosition;
                  WP[i].moving = 0;
                  enterPressed = 0;
                  turn = 1;
                  BoardUpdate(BoardMatrix, WP, BP);
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
                if(BlackLegalityCheck(&(BP[i]), &FS, WP, BP, BoardMatrix)){
                  BP[i].xPosition = FS.xPosition;
                  BP[i].yPosition = FS.yPosition;
                  BP[i].moving = 0;
                  enterPressed = 0;
                  turn = 0;
                  BoardUpdate(BoardMatrix, WP, BP);
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


