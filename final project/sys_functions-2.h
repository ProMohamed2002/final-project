#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<time.h>
int v=1;
int big,i;
int board[100][100];
int counter = 0;
int difference = 0;
int indecator = 1;
int counter0 = 0;
int r, c;
int Highscore;
int sw=0;
int mod, color;
int score1 = 0, score2 = 0;
FILE * fb;
typedef struct{
    int x;
    int y;

}turn_t;

turn_t turn[100], arr[4];
typedef struct{
    char name[20];
    int score;
    int rank;

}user;

struct game
{
    int hours;
    int min;
    int sec;

}diff,time1,time2;



void PrintBoard(/*int r, int c*/){


    for(int i=0; i<c; i++)
        printf("  %d ",i+1);
    printf("\n");
    for(int i=0; i<c; i++)
        printf("____");
    printf("_\n");
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(board[i][j] == 88){
                if(color == 1)
                    COLOR(4);
                else if(color == 2)
                    COLOR(6);
                else
                    COLOR(7);
            }
            else if(board[i][j] == 79){
                if(color == 1)
                    COLOR(6);
                else if(color == 2)
                    COLOR(4);
                else
                    COLOR(7);
            }

            printf("| %c ", board[i][j]);
            COLOR(7);
        }
        printf("|\n");
        for(int i=0; i<c; i++){
            printf("____");
        }
        printf("_\n");
    }

}
void COLOR(int color_value){
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, color_value);

}


int check_four(int a1, int a2, int b1, int b2, int c1, int c2, int d1, int d2){
    if((board[a1][a2] == board[b1][b2]) && (board[b1][b2] == board[c1][c2]) && (board[c1][c2] == board[d1][d2]) && (board[d1][d2] != 32)){
        return board[a1][a2];
    }else{
        return 0;
    }
}


int * check_rows(int label, int *pscore){
    int count = 0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c-3; j++){

            if(check_four(i, j, i, j+1, i, j+2, i, j+3) == label)
                count++;
        }
    }
    *pscore = *pscore + (count - *pscore);
    return pscore;
}


int * check_columns(int label, int *pscore){
    int count = 0;
    for(int i=0; i<=r; i++){
        for(int j=0; j<=c; j++){

            if(check_four(j, i, j+1, i, j+2, i, j+3, i) == label)
                count++;
        }
    }
    *pscore = *pscore + (count - *pscore);
    return pscore;
}


int * check_diagonals(int label, int *pscore){
    int count = 0;
    for(int i=0; i<r-3; i++){
        for(int j=0; j<c-3; j++){
            if(check_four(i, j, i+1, j+1, i+2, j+2, i+3, j+3) == label)
                count++;
        }
    }
    for(int i=r; i>=3; i--){
        for(int j=0; j<c-3; j++){
            if(check_four(i, j, i-1, j+1, i-2, j+2, i-3, j+3) == label)
                count++;
        }
    }
    *pscore = *pscore + (count - *pscore);
    return pscore;

}


int * score(int label, int *pscore){
    *pscore = *check_rows(label, pscore) + *check_columns(label, pscore) + *check_diagonals(label, pscore);

    return pscore;
}


int one_turn(int player, int label, int *pscore1, int *pscore2, turn_t turn[]){
    char col[5];
    int row = r;
    int col1;
    FILE * fb;

    printf("\npress u for undo\n");
    printf("press r for redo\n");
    printf("press s for save\n");
    printf("press x for exit\n");
time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);///////////////i add it
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           timegame(time1,time2,&diff);
           printf("timer(mints:  %d|seconds:  %d)\n",diff.min,diff.sec);

    printf("\nplayer %d to play\n", player);
    scanf("%s", &col);

    while(strcmp(col, "u") != 0 && strcmp(col, "r") != 0 && strcmp(col, "x") != 0 && strcmp(col, "s") != 0 && isdigit(col) != 0){

        printf("unavailable\n");
        printf("\nplayer %d to play\n", player);
        printf("please try again\n");

        scanf("%s", &col);
        fflush(stdin);
    }
    while((difference == 0 && strcmp(col, "u") == 0) || (difference == counter && strcmp(col, "r") == 0) || (indecator == 3 && strcmp(col, "r") == 0) || (difference == counter0 && strcmp(col, "u") == 0)){
        printf("unavailable\n");
        printf("please try again\n");
        scanf("%s", &col);
    }
    if(strcmp(col, "s") == 0){
        char choise;
        printf("\nsave the current game ?????\n");
        printf("press y for yes\n");
        printf("press n for no\n");
        scanf(" %c", &choise);
        while(choise != 'y' && choise != 'n'){
            printf("ERROR please try again");
            scanf(" %c", &choise);
        }
        if(choise == 'y'){
            save();
            printf("\nsaved\n");
        }
        PrintBoard();
        printf("\npress u for undo\n");
        printf("press r for redo\n");
        printf("press s for save\n");
        printf("press x for exit\n");
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);

        printf("\nplayer %d to play\n", player);
        scanf("%s", &col);
    }
    if(strcmp(col, "x") == 0){      //check for exiting
        char choise;
        printf("\nsave the current game ?????\n");
        printf("press y for yes\n");
        printf("press n for no\n");
        scanf(" %c", &choise);
        while(choise != 'y' && choise != 'n'){
            printf("ERROR please try again");
            scanf(" %c", &choise);
        }
        if(choise == 'n'){
            return 2;                   //exiting th game without saving
        }
    }
    if(strcmp(col, "u") == 0){          //check for redo

        board[turn[difference-1].x][turn[difference-1].y] = 32;
        PrintBoard();
        printf("%d %d %d\n",counter, turn[difference-1].x, turn[difference-1].y);
        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        printf("undo\n");
        indecator = 0;
        return 0;                       //return value for undo command to check later
    }
    else if(strcmp(col, "r") == 0){     //check for redo
        board[turn[difference].x][turn[difference].y] = label;
        PrintBoard();
        printf("%d %d %d\n",counter, turn[difference].x, turn[difference].y);
        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        printf("redo\n");
        indecator = 1;
        return 1;                       //return value for redo command to check later
    }
    else if(strcmp(col, "x") == 0){     //check for exit command

        save();
        printf("exit");
        return 2;                       // return value of exit command to check later
    }
    else{                               //normal process
        col1 = atoi(col);


        while(col1 > c){
            printf("unavailable\nplayer %d to play\n", player);
            scanf("%d", &col1);
        }
        while(board[row-1][col1-1] != 32){
            fflush(stdin);
            row--;
            if(row < 0){
                row = r;
                printf("unavailable\nplayer %d to play\n", player);
                scanf("%d", &col1);
            }
        }
        board[row-1][col1-1] = label;

        turn[difference].x = row - 1;
        turn[difference].y = col1 - 1;
        counter++;
        difference++;
        PrintBoard();
        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        indecator = 3;
    }
    return 3;                 //return value in case of normal process to check later
}


int computer(int *pscore1, int *pscore2){

    int col2 = 0;
    int row = r;
    if(indecator == 0){                     //check that the last play was undoed
        board[turn[difference-1].x][turn[difference-1].y] = 32;
        PrintBoard();

        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        printf("undo\n");
        indecator = 0;
        return 0;
    }
    else if(indecator == 1){                //check that the last play was redoed
        board[turn[difference].x][turn[difference].y] = 79;
        PrintBoard();

        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        printf("redo\n");
        indecator = 1;
        return 1;
    }
    else{                                   //normal process
        printf("\n");
        col2 = (rand() % c) + 1;
        while(board[row-1][col2-1] != 32){
            row--;
            if(row < 0){
                row = r;
                col2 = (rand() % c) + 1;
            }
        }

        board[row-1][col2-1] = 79;
        turn[difference].x = row - 1;
        turn[difference].y = col2 - 1;
        counter++;
        difference++;
        PrintBoard();
        *pscore2 = *score(79, pscore2);
        *pscore1 = *score(88, pscore1);

        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
    }
}

int check_rows_for_three(int label){
    turn_t index;
    int count = 0, found = 0;
    int i, j, k;
    for(i=0; i<r; i++){
        for(j=0; j<c-3; j++){
            count = 0;
            for(k=0; k<4; k++){
                arr[k].x = i;
                arr[k].y = j+k;
                if(board[i][j+k] == label){
                    count++;
                }
            }
            if(count == 3 && ((board[i][j] == 32) || (board[i][j+1] == 32) || (board[i][j+2] == 32) || (board[i][j+3] == 32))){
                found = 1;
                break;
            }
        }
        if(found)
            break;
    }
    if(found){
        for(i=0; i<4; i++){
            if(board[arr[i].x][arr[i].y] == 32){
                index.x = arr[i].x;
                index.y = arr[i].y;
            }
        }
        if((index.x == r - 1) || (board[index.x + 1][index.y] != 32)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }

}
int check_columns_for_three(int label){
    int i, j, k;
    int count = 0, found = 0;
    for(i=0; i<c; i++){
        for(j=r-1; j>3 ; j--){
            count = 0;
            for(k=0; k<4; k++){
                arr[k].y = i;
                arr[k].x = j-k;
                if(board[j-k][i] == label){
                    count++;
                }

            }
            if(count == 3 && (board[j-3][i] == 32)){
                found = 1;
                break;
            }
        }
        if(found)
            break;
    }
    if(found){
        return 1;
    }
    else{
        return 0;
    }
}
int check_diagonals_for_three_left(int label){
    int i, j, k;
    turn_t index;
    int count = 0, found = 0;
    for(i=0; i<r-3; i++){
        for(j=0; j<c-3; j++){
            count = 0;
            for(k=0; k<4; k++){
                arr[k].x = i + k;
                arr[k].y = j + k;
                if(board[i+k][j+k] == label){
                    count++;
                }
            }
            if(count == 3 && ((board[i][j] == 32) || (board[i+1][j+1] == 32) || (board[i+2][j+2] == 32) || (board[i+3][j+3] == 32))){
                found = 1;
                break;
            }
        }
        if(found)
            break;
    }
    if(found){
        for(i=0; i<4; i++){
            if(board[arr[i].x][arr[i].y] == 32){
                index.x = arr[i].x;
                index.y = arr[i].y;
            }
        }
        if((index.x == r - 1) || (board[index.x + 1][index.y] != 32)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }

}
int check_diagonals_for_three_right(int label){
    int i, j, k;
    turn_t index;
    int count = 0, found = 0;
    for(i=r; i>=3; i--){
        for(j=0; j<c-3; j++){
            count = 0;
            for(k=0; k<4; k++){
                arr[k].x = i - k;
                arr[k].y = j + k;
                if(board[i-k][j+k] == label){
                    count++;
                }
            }
            if(count == 3 && ((board[i][j] == 32) || (board[i-1][j+1] == 32) || (board[i-2][j+2] == 32) || (board[i-3][j+3] == 32))){
                found = 1;
                break;
            }
        }
        if(found)
            break;
    }
    if(found){
        for(i=0; i<4; i++){
            if(board[arr[i].x][arr[i].y] == 32){
                index.x = arr[i].x;
                index.y = arr[i].y;
            }
        }
        if((index.x == r - 1) || (board[index.x + 1][index.y] != 32)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }

}
int hard_computer(int *pscore1, int *pscore2){
    int i, j;
    int col = 0;
    int row = r;
    if(indecator == 0){                     //check that the last play was undoed
        board[turn[difference-1].x][turn[difference-1].y] = 32;
        PrintBoard();

        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        printf("undo\n");
        indecator = 0;
        return 0;
    }
    else if(indecator == 1){                //check that the last play was redoed
        board[turn[difference].x][turn[difference].y] = 79;
        PrintBoard();

        *pscore1 = *score(88, pscore1);
        *pscore2 = *score(79, pscore2);
        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
        printf("redo\n");
        indecator = 1;
        return 1;
    }
    else{                                   //normal process
        printf("\n");
        if((check_rows_for_three(88) == 1) || (check_columns_for_three(88) == 1) || (check_diagonals_for_three_right(88) == 1) || (check_diagonals_for_three_left(88) == 1)){
            for(i=0; i<4; i++){
                if(board[arr[i].x][arr[i].y] == 32){
                    break;
                }
            }
            col = arr[i].y + 1;
                while(board[row-1][col-1] != 32){
                    row--;
                    if(row < 0){
                        row = r;
                        col = (rand() % c) + 1;
                    }
                }
        }
        else if((check_rows_for_three(79) == 1) || (check_columns_for_three(79) == 1) || (check_diagonals_for_three_right(79) == 1) || (check_diagonals_for_three_left(79) == 1)){
            for(i=0; i<4; i++){
                if(board[arr[i].x][arr[i].y] == 32){
                    break;
                }
            }
            col = arr[i].y + 1;
            while(board[row-1][col-1] != 32){
                row--;
                if(row < 0){
                    row = r;
                    col = (rand() % c) + 1;
                }
            }
        }
        else{
            col = (rand() % c) + 1;
            while(board[row-1][col-1] != 32){
                row--;
                if(row < 0){
                    row = r;
                    col = (rand() % c) + 1;
                }
            }
        }


        board[row-1][col-1] = 79;
        turn[difference].x = row - 1;
        turn[difference].y = col - 1;
        counter++;
        difference++;
        PrintBoard();
        *pscore2 = *score(79, pscore2);
        *pscore1 = *score(88, pscore1);

        if(color == 1)
            COLOR(4);
        else if(color == 2)
            COLOR(6);
        printf("score 1: %d     number of moves: %d  \n", *pscore1, count_turns(88));
        if(color == 1)
            COLOR(6);
        else if(color == 2)
            COLOR(4);
        printf("score 2: %d     number of moves: %d  \n", *pscore2, count_turns(79));
        COLOR(7);
    }

}

/*void undo(int *pscore1, int *pscore2){
    board[turn[difference-1].x][turn[difference-1].y] = 32;
    PrintBoard();
    printf("%d %d %d\n",counter, turn[difference-1].x, turn[difference-1].y);
    *pscore1 = *score(88, r, c, pscore1);
    *pscore2 = *score(79, r, c, pscore2);
    printf("score 1: %d  score 2: %d\n", *pscore1, *pscore2);
    printf("undo\n");

}*/              //still under test

void game(){

    char winner[20];
    int return_value;
    char test;


    int dim = r*c;
    if(mod == 1){       //vs player game

        for(int i=counter/2; i<dim/2; i++){

            return_value = one_turn(1, 88,/* r, c, */&score1, &score2, turn);

            if(return_value == 0){          //user undoed
                difference--;
                i--;
            }
            else if(return_value == 1){     //user redoed
                difference++;
            }
            else if(return_value == 2){     //user exited

                return;
            }


            return_value = one_turn(2, 79, &score1, &score2, turn);
            if(return_value == 0){
                difference--;
                i--;
            }
            else if(return_value == 1){
                difference++;
            }
            else if(return_value == 2){

                return;
            }
        }
        if(r*c % 2 != 0){

            one_turn(1, 88, &score1, &score2, turn);
        }
        printf("\n");

        if(score1 > score2){
            if(color == 1)
                COLOR(4);
            else
                COLOR(6);
                sw=score1;///add score of the winner
            printf("player 1 wins\n");
            printf("***********************************\n");
            printf("**********congratulations**********\n");
            printf("***********************************\n");
            COLOR(7);
            time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
            high_score();
        }
        else if(score1 < score2){
            if(color == 1)
                COLOR(6);
            else
                COLOR(4);
                sw=score2;///add score of the winner
            printf("player 2 wins\n");
            printf("***********************************\n");
            printf("**********congratulations**********\n");
            printf("***********************************\n");
            COLOR(7);
             time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
            high_score();
        }
        else{
            printf("**********draw**********\n");
              time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           printf("the time of the game\n");
          timegame(time1,time2,&diff);
           printf("hours:  %d/mints:  %d/seconds:  %d\n",diff.hours,diff.min,diff.sec);
            printf("press any key to continue\n");
            getchar();
        }
    }
    else if(mod == 2){     //vs computer game


        for(int i=counter/2; i<(r*c) / 2; i++){

            return_value = one_turn(1, 88, &score1, &score2, turn);
            if(return_value == 0){
                difference--;
                i -= 2;

                computer(&score1, &score2);
                difference--;

            }
            else if(return_value == 1){
                difference++;
                computer(&score1, &score2);
                difference++;
            }
            else if(return_value == 2){
                return;
            }
            else{

                computer(&score1, &score2);
            }

        }
        if(r*c % 2 != 0){

            one_turn(1, 88, &score1, &score2, turn);
        }
        printf("\n");

        if(score1 > score2){
            if(color == 1)
                COLOR(4);
            else
                COLOR(6);
                sw=score1;///add score of the winner
            printf("player 1 wins\n");
            printf("***********************************\n");
            printf("**********congratulations**********\n");
            printf("***********************************\n");
             time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           high_score();
        }
        else if(score1 < score2){
            if(color == 1)
                COLOR(6);
            else
                COLOR(4);
            printf("the computer has just beated you\n");

            COLOR(7);
              time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           printf("the time of the game\n");
          timegame(time1,time2,&diff);
           printf("hours:  %d/mints:  %d/seconds:  %d\n",diff.hours,diff.min,diff.sec);
        }

        else{
            printf("**********draw**********\n");
              time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           printf("the time of the game\n");
          timegame(time1,time2,&diff);
           printf("hours:  %d/mints:  %d/seconds:  %d\n",diff.hours,diff.min,diff.sec);
            printf("press any key to continue\n");
            getchar();
        }
    }
    else{               //vs hard computer game

        for(int i=counter/2; i<(r*c) / 2; i++){

            return_value = one_turn(1, 88, &score1, &score2, turn);
            if(return_value == 0){
                difference--;
                i -= 2;

                hard_computer(&score1, &score2);
                difference--;

            }
            else if(return_value == 1){
                difference++;
                hard_computer(&score1, &score2);
                difference++;
            }
            else if(return_value == 2){
                return;
            }
            else{

                hard_computer(&score1, &score2);
            }

        }

        if(r*c % 2 != 0){

            one_turn(1, 88, &score1, &score2, turn);
        }
        printf("\n");

        if(score1 > score2){
            if(color == 1)
                COLOR(4);
            else
                COLOR(6);
                sw=score1;///add score of winner
            printf("player 1 wins\n");
            printf("***********************************\n");
            printf("**********congratulations**********\n");
            printf("***********************************\n");
             time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           high_score();
        }
        else if(score1 < score2){
            if(color == 1)
                COLOR(6);
            else
                COLOR(4);
            printf("the computer has just beated you\n");
              time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           printf("the time of the game\n");
           timegame(time1,time2,&diff);
           printf("hours:  %d/mints:  %d/seconds:  %d\n",diff.hours,diff.min,diff.sec);
            getchar();
        }
        else{
            printf("**********draw**********\n");
              time_t stop=time(NULL);
            struct tm  *t2=localtime(&stop);
            time2.hours=t2->tm_hour;
            time2.min=t2->tm_min;
            time2.sec=t2->tm_sec;
           printf("the time of the game\n");
          timegame(time1,time2,&diff);
           printf("hours:  %d/mints:  %d/seconds:  %d\n",diff.hours,diff.min,diff.sec);
            printf("press any key to continue\n");
            getchar();
        }
    }

}


void load(int file_num){       //saving the current board


    if(file_num == 1){
        fb = fopen("save_1.bin", "rb");
    }
    else if(file_num == 2){
        fb = fopen("save_2.bin", "rb");
    }
    else if(file_num == 3){
        fb = fopen("save_3.bin", "rb");
    }


    if(fb == NULL){
        printf("ERROR!!!!!!!!!!\n");
    }
    fread(&r, sizeof(r), 1, fb);

    fread(&c, sizeof(c), 1, fb);

    fread(&color, sizeof(color), 1, fb);

    fread(&mod, sizeof(mod), 1, fb);

    for(int j=0; j<r; j++){
        for(int k=0; k<c; k++){
            fread(&board[j][k], sizeof(board[j][k]), 1, fb);
        }
    }

    fclose(fb);

    for(int j=0; j<r; j++){
        for(int k=0; k<c; k++){
            if(board[j][k] != 32){
                counter++;
            }
        }
    }
    difference = counter;
    counter0 = counter;
}

void save(){
    int file;
    printf("save in:\n");
    printf("1- save_1\n");
    printf("2- save_2\n");
    printf("3- save_3\n");
    scanf("%d", &file);
    while(file != 1 && file != 2 && file != 3){
        printf("please try again\n");
        scanf("%d", file);
    }
    if(file == 1){
        fb = fopen("save_1.bin", "wb");
    }
    else if(file == 2){
        fb = fopen("save_2.bin", "wb");
    }
    else if(file == 3){
        fb = fopen("save_3.bin", "wb");
    }
    if(fb == NULL){
        printf("ERROR!!!!!!!\n");
    }

    fwrite(&r, sizeof(r), 1, fb);
    fwrite(&c, sizeof(c), 1, fb);
    fwrite(&color, sizeof(color), 1, fb);
    fwrite(&mod, sizeof(mod), 1, fb);
    for(int j=0; j<r; j++){
        for(int k=0; k<c; k++){
            fwrite(&board[j][k], sizeof(board[j][k]), 1, fb);
        }
    }
    fclose(fb);
}
void xml(){
    char y,x[100]= {'0'},conf_1[]="<Configurations>",width_1[]="<Width>",height_1[]="<Height>",highscores_1[]="<Highscores>";
    char conf_2[]="</Configurations>",width_2[]="</Width>",height_2[]="</Height>",highscores_2[]="</Highscores>";
    int i=0,start,end,start_w,end_w,start_h,end_h,start_hs,end_hs,len=0,a,size,HS,H,W;
   FILE *fr;
   fr=fopen("m.xml","r");///open file to read
   if((fr=fopen("m.xml","r"))==NULL)
   {
       printf("can not find the file,please enter path:");
       char path[60];
       gets(path);
       printf("%s\n",path);
        fr=fopen(path,"r");
        printf("\n%d\n",fr);
        while((y=fgetc(fr))!=EOF)
       {
        if(y!=' '&&y!='\n'&&y!='\t')
            {           //IGNORING ANY SPACES OR TABS OR BREAKING LINE
            x[i]=y;
            i++;
           }

        }
     fclose(fr);///close file
    start=get_indx(conf_1,x);
    end =get_indx(conf_2,x);
    size=end-start+1;
    size=size+20;
    char array[size];
    for(a=0; a<size; a++){array[a]=x[start+a];
    }
    start_w=get_indx(width_1,array);
    end_w=get_indx(width_2,array);
    char col [3];                               //CHECKING OPENING AND CLOSING THE TAGS IN RIGHT WAY
    col[0]=array[start_w+7];

    col[1]=array[start_w+8];

    col[2]='\0';

    if(start_w!=-1&&end_w!=-1&&(end_w-start_w==8||end_w-start_w==9)&&atoi(col)>=4)
    {
      printf("check number of colums\n");
      sleep(5);
        W=atoi(col);
    }

    else{                                       //SET THE DEFULT IN THERE IS WRONG IN READING THE XML FILE
        system("COLOR ");
        W=7;
        printf("\nWidth is Not found !! the defult is Width =7\n");
        printf("Wait to load the default!!\n");
        Sleep(7000);
    }
    start_h=get_indx(height_1,array);
    end_h=get_indx(height_2,array);
    char row [3];                                  //CHECK OPENING AND CLOSING THE TAGS IN WRIGHT WAY
    row[0]=array[start_h+8];

    row[1]=array[start_h+9];

    row[2]='\0';

    if(start_h!=-1&&end_h!=-1&&(end_h-start_h==9||end_h-start_h==10)&&atoi(row)>=4)
    {
         printf("\ncheck number of rows");
        sleep(5);
        H=atoi(row);}
    else{
        H=6;                                        //SET THE DEFULT IF THERE IS ERROR WHILE READING FROM XML FILE

        printf("\nHeight is Not found !! the defult is Height =6\n");
        printf("\nWait to load the default!!\n");
        ///Sleep(5000);
    }

    start_hs=get_indx(highscores_1,array);
    end_hs=get_indx(highscores_2,array);
    char score[3];
    score[0]=array[start_hs+12];
    score[1]=array[start_hs+13];
    score[2]='\0';
    if(start_hs!=-1&&end_hs!=-1&&end_hs-start_hs==13||end_hs-start_hs==14)
    {
        printf("\ncheck high score ");
        sleep(5);
        HS=atoi(score);}
    else{
        HS=10;                                       //SET THE DEFULT VALUE
        printf("\nHigh_score is Not found !! the defult is Highscore =10\n");      //PRINTING ERROR
        printf("Wait to load the default!!\n");                                 //ERROR MESSAGE
        Sleep(5000);
    }

    c=W;                                     //CHANGING THE GLOBAL VALUE FOR WIDTH
    r=H;                                     //CHANGING THE GLOBAL VALUE FOR HEIGHT
    Highscore=HS;                                   //CHANGING THE GLOBAL VAUE FOR HIGH SCORE



   }
   else{
   while((y=fgetc(fr))!=EOF)
       {
        if(y!=' '&&y!='\n'&&y!='\t')
            {           //IGNORING ANY SPACES OR TABS OR BREAKING LINE
            x[i]=y;
            i++;
           }

        }
     fclose(fr);///close file
    start=get_indx(conf_1,x);
    end =get_indx(conf_2,x);
    size=end-start+1;
    size=size+20;
    char array[size];
    for(a=0; a<size; a++){array[a]=x[start+a];
    }
    start_w=get_indx(width_1,array);
    end_w=get_indx(width_2,array);
    char col [3];                               //CHECKING OPENING AND CLOSING THE TAGS IN RIGHT WAY
    col[0]=array[start_w+7];

    col[1]=array[start_w+8];

    col[2]='\0';

    if(start_w!=-1&&end_w!=-1&&(end_w-start_w==8||end_w-start_w==9)&&atoi(col)>=4)
    {
      //printf("check number of colums");
      sleep(1);
        W=atoi(col);
    }

    else{                                       //SET THE DEFULT IN THERE IS WRONG IN READING THE XML FILE
        system("COLOR ");
        W=7;
        printf("Width is Not found !! the defult is Width =7\n");
        printf("Wait to load the default!!\n");
        Sleep(7000);
    }
    start_h=get_indx(height_1,array);
    end_h=get_indx(height_2,array);
    char row [3];                                  //CHECK OPENING AND CLOSING THE TAGS IN WRIGHT WAY
    row[0]=array[start_h+8];

    row[1]=array[start_h+9];

    row[2]='\0';

    if(start_h!=-1&&end_h!=-1&&(end_h-start_h==9||end_h-start_h==10)&&atoi(row)>=4)
    {
         //printf("\ncheck number of rows");
        sleep(1);
        H=atoi(row);}
    else{
        H=6;                                        //SET THE DEFULT IF THERE IS ERROR WHILE READING FROM XML FILE
        printf("Height is Not found !! the defult is Height =6\n");
        printf("Wait to load the default!!\n");
        Sleep(5000);
    }

    start_hs=get_indx(highscores_1,array);
    end_hs=get_indx(highscores_2,array);
    char score[3];
    score[0]=array[start_hs+12];
    score[1]=array[start_hs+13];
    score[2]='\0';
    if(start_hs!=-1&&end_hs!=-1&&end_hs-start_hs==13||end_hs-start_hs==14)
    {
        //printf("\ncheck high score ");
        sleep(1);
        HS=atoi(score);}
    else{
        HS=10;                                       //SET THE DEFULT VALUE
        printf("High_score is Not found !! the defult is Highscore =10\n");      //PRINTING ERROR
        printf("Wait to load the default!!\n");                                 //ERROR MESSAGE
        Sleep(5000);
    }

    c=W;                                     //CHANGING THE GLOBAL VALUE FOR WIDTH
    r=H;                                     //CHANGING THE GLOBAL VALUE FOR HEIGHT
    Highscore=HS;                                   //CHANGING THE GLOBAL VAUE FOR HIGH SCORE

   }
   ///printf("%d %d %d",c , r, Highscore);


}
int get_indx(char s1[],char s2[]){
    int counter1=-1,i=0;
    while(s2[i]!='\0'){
        int j=0;
        if(s2[i]==s1[j]){
            int k=i;
            while(s2[k]==s1[j] && s1[j]!='\0'){
                k++;
                j++;
            }
            if(s1[j]=='\0'){
                counter1=i;
            }
        }
        i++;
    }
    return counter1;
}



int count_turns(int label){
    int count;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(board[i][j] == label)
                count++;
        }
    }
    return count;
}
void high_score()
{

          printf("the time of the game\n");
          timegame(time1,time2,&diff);
           printf("hours:  %d/mints:  %d/seconds:  %d\n",diff.hours,diff.min,diff.sec);


      big=0;
      user scorse[10];
      int c=0;
      FILE *frh;
      frh=fopen("high.bin","rb");

      while(!feof(frh))
      {
      if((fread(&scorse[c].name,sizeof(scorse[c].name),1,frh))==0) break;

       fread(&scorse[c].score,sizeof(scorse[c].score),1,frh);

        fread(&scorse[c].rank,sizeof(scorse[c].rank),1,frh);

        c++;

      }
      fclose(frh);


    printf("your name:");
    fflush(stdin);
    gets(scorse[c].name);
    strupr(scorse[c].name);///take name in upper case///
    printf("\nyour score:");
    scanf("%d",&scorse[c].score);
    while(sw!=scorse[c].score)
    {
        printf("please enter real score:");
        scanf("%d",&scorse[c].score);
    }


   if(c!=0)
    big=scorse[0].score; ///to git max score after sorting


 if(scorse[c].score>big)
    {
  for(i=0;i<c;i++)
   {
       if(strcmp(scorse[c].name,scorse[i].name)==0){
          strcpy(scorse[c].name,scorse[i].name);
          scorse[i].score=scorse[c].score;
          c--;}
   }
     sort(scorse,c);

      for(i=0;i<c+1;i++)///for rank
      {

          scorse[i].rank=v;
          v++;
      }}
      else{
            c--;
       for(i=0;i<c+1;i++)///for rank
           {

          scorse[i].rank=v;
          v++;}
          }
for(i=0;i<c+1;i++)
{
    printf("%s %d %d\n",scorse[i].name,scorse[i].score,scorse[i].rank);
}

   frh=fopen("high.bin","wb");

  for(i=0;i<c+1;i++)
  {
      fwrite(&scorse[i].name,sizeof(scorse[i].name),1, frh);
      fwrite(&scorse[i].score,sizeof(scorse[i].score),1, frh);
      fwrite(&scorse[i].rank,sizeof(scorse[i].rank),1, frh);
  }
  fclose(frh);
}
void sort(user s[],int x)
{
    int i=0,j=0;
    user temp;
    for(i=0;i<x+1;i++)
     {
      for(j=i+1;j<x+1;j++)
        if(s[i].score<s[j].score)
    {
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
    }
     }

}


void print_data(user a){
        printf("%s   %d     %d\n",a.name,a.score,a.rank);
}

void readhighscore()
{
     user p[10];
    int g=0;
    FILE * frh;
     frh=fopen("high.bin","rb");
     if(frh==NULL)
      {
          printf("it is the first game\n");
      }
      else{
      for(int ii=1;ii<=Highscore;ii++){////H read from xml///
      while(fread(&p[g],sizeof(p[g]),1,frh),!feof( frh))
      {  if  (p[g].name='\0'||p[g].score=NULL||p[g].rank=NULL)
             printf("ERORRRR in file !!");

          if(p[g].name!='\0'&&p[g].score!=NULL&&p[g].rank!=NULL){//////add it instruction ////
          printf("name:%s            score:%d           rank=%d\n",p[g].name,p[g].score,p[g].rank);}
          g++;
      }
}}



}
void timegame(struct game a,struct game b,struct game *po)
{


   if(a.sec>b.sec)
   {
       b.sec+=60;
       --b.min;
   }

  if(a.min>b.min)
  {
      b.min+=60;
      --b.hours;
  }
    po->sec=abs(b.sec-a.sec);
    po->min=abs(b.min-a.min);
    po->hours=abs(b.hours-a.hours);


}
void printtime()
{

   time_t curenttime=time(NULL);
   struct tm *tm=localtime(&curenttime);
   printf("%s",asctime(tm));


}
