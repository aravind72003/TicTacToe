#include<stdio.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
int pmCount;
int cmCount;

int main(){
    char winner = ' ';
    char response;
    do
    {
        pmCount = 0;
        cmCount = 0;
        winner = ' ';
        response = ' ';
        resetBoard();
        while(winner == ' ' && checkFreeSpaces() != 0){
            printBoard();
            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces()==0)
            break;

            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces()==0)
            break;

        }
        printBoard();
        printWinner(winner);
        printf("\nWanna play again? [Y/N]: ");
        scanf(" %c",&response);
        response = toupper(response);
    } while (response == 'Y');

    printf("Thanks for Playing!\n");
    return 0;
}

void resetBoard(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(){
    printf("| %c | %c | %c |\n",board[0][0],board[1][0],board[2][0]);
    printf("|---|---|---|\n");
    printf("| %c | %c | %c |\n",board[0][1],board[1][1],board[2][1]);
    printf("|---|---|---|\n");
    printf("| %c | %c | %c |\n",board[0][2],board[1][2],board[2][2]);
    printf("|---|---|---|\n");
}


int checkFreeSpaces(){
    int freeSpaces = 9;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!=' ')
            freeSpaces--;
        }
    }
    return freeSpaces;
}

void playerMove(){
    int x;
    int y;

    do{
        printf("Enter row #[1-3]: ");
        scanf("%d",&y);
        printf("Enter column #[1-3]: ");
        scanf("%d",&x);
        x--;
        y--;
        if(board[x][y]!=' ' || x<0 || x>2 || y<0 || y>2)
        printf("Invalid Move\n");
        else{
            board[x][y] = PLAYER;
            pmCount++;
        }
    } while (board[x][y]==' ');





}

void computerMove(){
    srand(time(0));
    int x;
    int y;
    if(cmCount<pmCount){
        if(checkFreeSpaces()>0){
            do
            {
                x = rand()%3;
                y = rand()%3;
            } while (board[x][y]!=' ');

            board[x][y] = COMPUTER;
            cmCount++;
        }
        else printWinner(' ');
    }


}
char checkWinner(){
    for(int i=0;i<3;i++){
        if(board[i][0]==board[i][1]&&board[i][1]==board[i][2]){
            return board[i][0];
        }
    }
    for(int i=0;i<3;i++){
        if(board[0][i]==board[1][i]&&board[1][i]==board[2][i]){
            return board[1][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    return board[0][2];
    return ' ';
}
void printWinner(char winner){
    if(winner == PLAYER) printf("YOU WIN!");
    else if(winner == COMPUTER) printf("YOU LOSE!");
    else printf("TIE");
}
