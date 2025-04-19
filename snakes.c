#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int score1 = 0;
int score2 = 0;
int lower  = 1;
int upper = 6;

int dice = 0;
char ch;

void print_scoreboard() {
    printf("\n================== SCOREBOARD ==================\n");
    printf(" Player 1 [O]  : %3d\n", score1);
    printf(" Player 2 [X]  : %3d\n", score2);

    if (score1 > score2)
        printf("  Leader     : Player 1 [O] \n");
    else if (score2 > score1)
        printf("  Leader     : Player 2 [X] \n");
    else
        printf("  It's a tie right now!\n");
    printf("=================================================\n");
}


void print_board() {
    printf("\n+-----------------------------------------------------+\n");
    for (int row = 9; row >= 0; row--) {
        printf("|");
        for (int col = 0; col < 10; col++) {
            int num;
            if (row % 2 == 0)
                num = row * 10 + col + 1;         
            else
                num = row * 10 + (9 - col) + 1;   

        
            if (score1 == num && score2 == num)
                printf(" [B] ");
            else if (score1 == num)
                printf(" [O] ");
            else if (score2 == num)
                printf(" [X] ");
            else
                printf(" %3d ", num);
        }
        printf("\t|\n");
        if (row != 0)
            printf("|-----------------------------------------------------|\n");
    }
    printf("+-----------------------------------------------------+\n");
}


int score_correction(int score, int player){

    switch(score){
        case 1 : printf("\nPlayer %d has Hit a Ladder!\n",player);
                 return score + 37;
                 break;
        case 4 : printf("\nPlayer %d has Hit a Ladder!\n",player);
                 return score + 10;
                 break;
        case 9 : printf("\nPlayer %d has Hit a Ladder!\n",player);
                 return score + 22;
                 break;
        case 21: printf("\nPlayer %d has Hit a Ladder!\n",player);
                 return score + 21;
                 break;
        case 28: printf("\nPlayer %d has Hit a Ladder!\n",player);
                 return score + 56;
                 break;
        case 51:printf("\nPlayer %d has Hit a Ladder!\n",player);
                return score + 16;
                break;
        case 71:printf("\nPlayer %d has Hit a Ladder!\n",player);
                return score + 20;
                break;
        case 80:printf("\nPlayer %d has Hit a Ladder!\n",player);
                return score + 20;
                break;
       case 17 :printf("\nPlayer %d got Bit a Snake!\n",player);
                return score - 10;
                break;
       case 54 : printf("\nPlayer %d got Bit a Snake!\n",player);
                return score - 20;
                break;
       case 62 : printf("\nPlayer %d got Bit a Snake!\n",player);
                return score - 43;
                break;
       case 64: printf("\nPlayer %d got Bit a Snake!\n",player);
                return score - 4;
                break;
       case 87: printf("\nPlayer %d got Bit a Snake!\n",player);
                return score - 63;
                break;
       case 93:printf("\nPlayer %d got Bit a Snake!\n",player);
               return score - 20;
               break;
       case 95:printf("\nPlayer %d got Bit a Snake!\n",player);
               return score - 20;
               break;
       case 98:printf("\nPlayer %d got Bit a Snake!\n",player);
               return score - 19;
               break;
        
        default: return score;
    }
}

void game_logic(){
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        print_board();
        print_scoreboard();
        
        
        printf("\nClick Player 1");
        scanf(" %c",&ch);
        dice = lower + rand() % (upper - lower + 1);
        score1 = score1 + dice;
        score1 = score_correction(score1,1);
        if (score1 > 100){ 
            score1 = 100;
        }
        printf("\nDice: %d \n", dice);
        dice = lower + rand() % (upper - lower + 1);
        printf("\nClick Player 2\n");
        scanf(" %c",&ch);
        score2 = score2 + dice;
        score2 = score_correction(score2,2);
        if (score2 > 100) {
            score2 = 100;
        }
        printf("\nDice: %d\n", dice);
        
        
}


int main(){
    srand(time(NULL));
    while(score1 < 100 && score2 < 100){
        
        game_logic();

    }

    if (score1 >= 100)
    printf("\n Player 1 [O] wins!\n");
    else if (score2 >= 100)
    printf("\n Player 2 [X] wins!\n");

    return 0;

}