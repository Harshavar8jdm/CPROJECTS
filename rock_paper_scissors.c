#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<windows.h>

int score_comp = 0;
int score_user = 0;
int choice = -1;
int rand_comp = -1;
int main_choice = -1;

void game_logic(int *);

void show_title() {
    printf("====================================\n");
    printf("     ROCK || PAPER || SCISSORS \n");
    printf("====================================\n");
    printf("        Made by [HARSHA]         \n");
    printf("        Mini Project - C Lang      \n");
    printf("====================================\n\n");
    printf("1. PLAY \n");
    printf("2. EXIT \t");
    scanf("%d",&main_choice);
}

void main_menu(){
    show_title();
    
}



int main(){
    
    main_menu();
    bool exe = true;

    int upper_bound = 3;
    int lower_bound = 1;

    
    while(exe){
        

        rand_comp = (rand() % upper_bound) + 1 ;
        printf("%d", rand_comp);
        
        if(main_choice == 1){
        printf("\n------------------------\n");
        printf("|1.ROCK|\n");
        printf("|*************************|\n");
        printf("|2. PAPER|\n");
        printf("|*************************|\n");
        printf("|3. SCISSOR|\n");
        printf("|*************************|\n");
        printf("|4.EXIT|\n");
        printf("|-------------------------|\n");
        printf("|ENTER YOUR CHOICE: \t|");
        

        scanf("%d",&choice);
        if(choice == 4){
            printf("\n------------------------\n");
            printf("|Thanks For Playing|\n");
            printf("|----------------------|\n");
            printf("PRESS CTRL+C TO QUIT");
            break;
        }
        game_logic(&choice);

    return 0;

        }
    
    else if(main_choice == 2){

            printf("\n------------------------\n");
            printf("|Thanks For Playing|\n");
            printf("|----------------------|\n");
            printf("PRESS CTRL+C TO QUIT");
            break;
            return 0;
        }
    }
}

void game_logic(int *choice){
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if(*choice == 1){
        if(rand_comp == 1){
            printf("\nDraw!");
            printf("\n------------------------\n");
            printf("| You: ROCK  | Computer: ROCK |\n");
            printf("\n------------------------\n");
            printf("|   Scoreboard         |\n");
            printf("|----------------------|\n");
            printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
            printf("------------------------\n");

        }
        else if(rand_comp == 2){
            printf("\nYou Lose!");
            score_comp++;
            printf("\n------------------------\n");
            printf("| You: ROCK  | Computer: PAPER |\n");
            printf("\n------------------------\n");
            printf("|   Scoreboard         |\n");
            printf("|----------------------|\n");
            printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
            printf("------------------------\n");
            
        }

        else if(rand_comp == 3){
            printf("\nYou Win!");
            score_user++;
            printf("\n------------------------\n");
            printf("| You: ROCK  | Computer: SCISSOR |\n");
            printf("\n------------------------\n");
            printf("|   Scoreboard         |\n");
            printf("|----------------------|\n");
            printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
            printf("------------------------\n");
        }

        else{
            printf("Unresolved Conflict Errno 1");
        }
    }
    else if( *choice == 2){
        if(rand_comp == 1){
            printf("\nYou Win!");
            score_user++;
            printf("\n------------------------\n");
            printf("| You: PAPER  | Computer: ROCK |\n");
            printf("\n------------------------\n");
            printf("|   Scoreboard         |\n");
            printf("|----------------------|\n");
            printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
            printf("------------------------\n");
            }
        else if(rand_comp == 2){
                printf("\nDraw");
                printf("\n------------------------\n");
                printf("| You: PAPER  | Computer: PAPER |\n");
                printf("\n------------------------\n");
                printf("|   Scoreboard         |\n");
                printf("|----------------------|\n");
                printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
                printf("------------------------\n");
            }

        else if(rand_comp == 3){
                printf("\nYou Lose!");
                score_comp++;
                printf("\n------------------------\n");
                printf("| You: PAPER  | Computer: SCISSOR |\n");
                printf("\n------------------------\n");
                printf("|   Scoreboard         |\n");
                printf("|----------------------|\n");
                printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
                printf("------------------------\n");
            }

        else{
                printf("Unresolved Conflict Errno:1\n");
            }
    }
    else {
            if(rand_comp == 1){
                printf("\nYou Lose!");
                score_comp++;
                printf("\n------------------------\n");
                printf("| You: SCISSOR | Computer: ROCK |\n");
                printf("\n------------------------\n");
                printf("|   Scoreboard         |\n");
                printf("|----------------------|\n");
                printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
                printf("------------------------\n");
            }
            else if(rand_comp == 2){
                printf("\nYou Win!");
                score_user++;
                printf("\n------------------------\n");
                printf("| You: SCISSOR | Computer: PAPER |\n");
                printf("\n------------------------\n");
                printf("|   Scoreboard         |\n");
                printf("|----------------------|\n");
                printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
                printf("------------------------\n");
            }
        
            else if(rand_comp == 3){
                printf("\nDraw!");
                printf("\n------------------------\n");
                printf("| You: SCISSOR | Computer: SCISSOR |\n");
                printf("\n------------------------\n");
                printf("|   Scoreboard         |\n");
                printf("|----------------------|\n");
                printf("| You: %d   | Computer: %d |\n", score_user, score_comp);
                printf("------------------------\n");
            }
        
            else{
                printf("Unresolved Conflict Errno:1");
                }   
    }
}
