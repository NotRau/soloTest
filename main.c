#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void setBoard(int board[][7])
{
    for(int x = 0 ; x < 7 ; x++)
    {
        for(int y = 0 ; y < 7 ; y++)
        {
            board[x][y] = 1;
            if(x == 0 || x == 1 || x == 5 || x == 6)
            {
                if(y == 0 || y == 1 || y == 5 || y == 6)
                {
                    board[x][y] = 2;
                }
            }
        }
        board[3][3] = 0;
    }

}

void printBoard(int board[][7], char empty, char pawn, char cursorX, char cursorY, char cursorL, char cursorR)
{
    char coor[7] = {'A','B','C','D','E','F','G'};

    printf("\n ");
    for(int x = 0 ; x<7 ; x++)
    {
        printf("   %d  ",x+1);
    }
    printf("\n\n\n");

    for(int y = 0 ; y < 7 ; y++)
    {
        for(int x = 0; x < 7 ; x++)
        {
            if(x == 0)
                printf("%c ",coor[y]);

            if(x != cursorX || y != cursorY)
            {
                switch(board[x][y])
                {
                    case 0: printf("  %c   ",empty); break;
                    case 1: printf("  %c   ",pawn); break;
                    case 2: printf("      "); break;
                }
            }
            else
            {
                switch(board[x][y])
                {
                    case 0: printf(" %c%c%c  ",cursorL, empty, cursorR); break;
                    case 1: printf(" %c%c%c  ",cursorL, pawn, cursorR); break;
                    case 2: printf("      "); break;
                }
            }

        }
        printf("\n\n");
    }
}

int countPieces(int board[][7])
{
    int counter = 0;
    for(int x = 0 ; x<7 ; x++)
    {
        for(int y = 0 ; y<7 ; y++)
        {
            if(board[x][y] == 1)
                counter++;
        }
    }
    return counter;
}

int possibleMoves(int board[][7])
{
    int count=0;
    for(int y=0 ; y<7 ; y++)
    {
        for(int x=0 ; x<7 ; x++)
        {
            if(board[x][y]==1)
            {
                if((x+1<7 && x+2<7) || (x-1>=0 && x-2>=0) ||
                   (y+1<7 && y+2<7) || (y-1>=0 && y-2>=0))
                {
                        if((board[x+1][y] == 1 && board[x+2][y] == 0)||
                       (board[x-1][y] == 1 && board[x-2][y] == 0)||
                       (board[x][y+1] == 1 && board[x][y+2] == 0)||
                       (board[x][y-1] == 1 && board[x][y-2] == 0))
                    {
                        count++;
                    }
                }

            }

        }
    }
    return count;
}

void movePiece(int board[][7],int cursorX, int cursorY, int sX, int sY, int moveCounter[])
{
    if(board[cursorX][cursorY] == 0)
    {
        if(cursorX == sX && abs(cursorY-sY) == 2)
        {
            if(sY < cursorY)
            {
                if(board[sX][sY+1] == 1)
                {
                    board[sX][sY] = 0;
                    board[sX][sY+1] = 0;
                    board[sX][sY+2] = 1;
                    moveCounter[0]++;
                }
            }
            else if(sY > cursorY)
            {
                if(board[sX][sY-1] == 1)
                {
                    board[sX][sY] = 0;
                    board[sX][sY-1] = 0;
                    board[sX][sY-2] = 1;
                    moveCounter[0]++;
                }
            }

        }

        else if(cursorY == sY && abs(cursorX-sX) == 2)
        {
            if(sX < cursorX)
            {
                if(board[sX+1][sY] == 1)
                {
                    board[sX][sY] = 0;
                    board[sX+1][sY] = 0;
                    board[sX+2][sY] = 1;
                    moveCounter[0]++;
                }
            }
            else if(sX > cursorX)
            {
                if(board[sX-1][sY] == 1)
                {
                    board[sX][sY] = 0;
                    board[sX-1][sY] = 0;
                    board[sX-2][sY] = 1;
                    moveCounter[0]++;
                }
            }

        }
    }
}


void gameLoop(int board[][7])
{
    int cursorX=3, cursorY=3;
    int moveCounter[1]= {0};
    char cursorL = '[', cursorR = ']';
    int sX=cursorX,sY=cursorY;
    //moving the cursor
    while(possibleMoves(board) > 0)
    {
        switch(getch())
        {
            case 'w'://up
                if(cursorY != 0 && board[cursorX][cursorY-1] != 2)
                    cursorY--;
            break;
            case 's'://down
                if(cursorY !=6 && board[cursorX][cursorY+1] != 2)
                    cursorY++;
            break;
            case 'd'://right
                if(cursorX != 6 && board[cursorX+1][cursorY] != 2)
                    cursorX++;
            break;
            case 'a'://left
                if(cursorX != 0 && board[cursorX-1][cursorY] != 2)
                    cursorX--;
            break;
            case 'e'://select

                if (cursorL == '[')
                {
                    if(board[cursorX][cursorY] == 1)
                    {
                        if((board[cursorX+1][cursorY] == 1 && board[cursorX+2][cursorY] == 0)||
                           (board[cursorX-1][cursorY] == 1 && board[cursorX-2][cursorY] == 0)||
                           (board[cursorX][cursorY+1] == 1 && board[cursorX][cursorY+2] == 0)||
                           (board[cursorX][cursorY-1] == 1 && board[cursorX][cursorY-2] == 0))
                        {
                            cursorL = '<';
                            cursorR = '>';
                            sX=cursorX;
                            sY=cursorY;
                        }
                    }
                }
                else
                {
                    movePiece(board, cursorX, cursorY, sX, sY, moveCounter);
                    cursorL = '[';
                    cursorR = ']';
                }
            break;
        }
        system("CLS");
        printBoard(board, '.', 254, cursorX, cursorY, cursorL, cursorR);
        printf("Use W,A,S,D to move the cursor\t\t\t\tRemaining pieces : %d\nUse E to select\t\t\t\t\t\tMoves taken : %d\n\n",
                countPieces(board),moveCounter[0]);
    }


    system("CLS");
    printBoard(board,'.',254,0,0,' ',' ');
    printf("\n\tThe Game is Over\n\n\tMoves taken : %d\n\tRemaining pieces : %d\n",moveCounter[0],countPieces(board));
}

int main()
{
    system("COLOR 6");
    getch();

    int board[7][7] = {0};
    do
    {
    setBoard(board);
    gameLoop(board);
    printf("\tPress Y to play again");
    }while(getch() == 'y' );


    return 0;
}
