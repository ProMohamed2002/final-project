#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "sys_functions-1.h"
#include<time.h>

/*int score1 = 0, score2 = 0;*/
int i,k;

int start(/*int r, int c*/);
void help(void);
void red();
void yellow();
void reset();
char op;

int main()
{

    //int r, c;

    /*printf("number of rows\n");
    scanf("%d", &r);
    printf("number of columns\n");
    scanf("%d", &c);*/


    //int board[r][c];


    while(start() == 6){
        fflush(stdin);

    }

    return 0;
}

int start(){
    int choose;
    int save;
    xml();


    //system("cls");                              //CLEAR SCREEN AFTER EACH PLAY
    for(i=0;i<15;i++)printf("\n");
    //system("COLOR 3C");  //CHANGING THE COLOR OF SCREEN
    //printtime();
    printf(" \n                             Welcome to connect four\n");              //WELCOME MESSAGE
    //Sleep(1000);///--->?
    //for(k=0;k<3;k++)printf("\n");
    //system("COLOR EC");                           //CHANGING COLR OF THE SCREEN
    printf("                                   1-new game\n"                ////////////////////////////
           "                                   ----------  \n"              //                          //
          "                                   2-high scores\n"              //    MAIN MENU            //
          "                                   -------------\n"              ////////////////////////////
          "                                   3-load game\n"
          "                                   -----------\n"
          "                                   4-help \n"
          "                                   -------------     \n "
          "                                  5-exit           \n "
         "                                   -------------       "
          "                                   \n");
    printf("choose from the previous options: \n");
    for(i=0;i<32;i++)
        printf("-");                                              //SCAN THE OPERATION TYPE FROM THE USER
    printf("\n");
    scanf(" %d", &choose); //GET THE USER CHOOSE
    /*while(choose < 1 && choose > 5){
        printf("unavailable\n");
        printf("please try again");
        choose = getchar;
        printf(" %c", choose);
    }*/

    switch(choose){
        case 1:
            for(int i=0; i<r; i++){
                for(int j=0; j<c; j++){
                    board[i][j] = 32;
                }
            }
            printf("choose mode\n");
            printf("1- player VS player\n");
            printf("2- player VS computer\n");
            printf("3- player VS hard computer");
            scanf(" %d", &mod);
            while(mod != 1 && mod != 2 && mod != 3){
                printf("unavailable");
                scanf(" %d", &mod);
            }
            for(int i=0; i<r; i++){
                for(int j=0; j<c; j++){
                    board[i][j] = 32;
                }
            }
            counter = 0;
            difference = 0;
            PrintBoard(/*r, c*/);
        time_t start=time(NULL);
        struct tm *t1=localtime(&start);
        time1.hours=t1->tm_hour;
        time1.min=t1->tm_min;
        time1.sec=t1->tm_sec;
            printf("player one color\n");
            printf("1- red\n");
            printf("2- yellow\n");
            scanf("%d", &color);
            while(color != 1 && color != 2){
                printf("please try again");
                scanf("%d", &color);
            }
            game(/*r, c, */);
            counter = 0;
            difference = 0;
            counter0 = 0;
            mod = 0;
            reset();
            return 6;    ///function of mode and play
        case 2: readhighscore();
                sleep(100000);
            break;
        case 3:

            printf("choose a save to load\n");
            //printf("save in:\n");
            printf("1- save_1\n");
            printf("2- save_2\n");
            printf("3- save_3\n");
            scanf("%d", &save);
            if(save == 1)
                load(1);
            else if(save == 2)
                load(2);
            else if(save == 3)
                load(3);
            printf("\n%d %d\n", r, c);
            if(counter%2 != 0){

                PrintBoard();
                one_turn(2, 79, &score1, &score2, turn);

                printf("\n");
                PrintBoard();
                game();
                counter = 0;
                difference = 0;
                counter0 = 0;
                mod = 0;

            }
            else{
                counter0 = counter;
                PrintBoard();
                game();
                counter = 0;
                difference = 0;
                counter0 = 0;
                mod = 0;

            }
            reset();
            return 6;///function of load and save
        case 4: help();
            return 4;///function of help

        case 5:
            printf("are you sure to exit y/n: ");
            scanf("%c",&op);  ///----->to read character %ch///
            if(getchar() == 'y'){
                system("cls");
                return 5;
            }
            else
                return 6;
    }

}

void help(void){

        printf("             ****        HOW TO PLAY        **** \n\n\n");          //GAME INSTRUCTIONS
        printf("the aim of the game is to connect 4 (x) or 4 (0) vertically or\n horizontally or diagonally \n");
        printf("the player who connect 4 more than the other will be the winner\n\n\n");
        printf("press u or undo :    to go back one step , you can return back to first turn in the board\n");
        printf("press r or redo :    to go forward for one step, you can return the board again\n");
        printf("press any key to return back to main menu\n");
        getchar();
        return 6;

///from https://mathworld.wolfram.com/Connect-Four.html
}
void red(){
    system("COLOR 4");
}
void yellow(){
    system("COLOR 6");
}
void reset(){
    system("COLOR 7");
}

void redo(){

}
