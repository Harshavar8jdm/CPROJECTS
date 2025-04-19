#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_HINT_LENGTH 50

struct word_with_hint{
    char word[MAX_WORD_LENGTH];
    char hint[MAX_HINT_LENGTH];
};

void draw_hangman(int depth){
    const char* hangmanParts[]
    = { "     _________",    "    |         |",
        "    |         O",   "    |        /|\\",
        "    |        / \\", "    |" };
    
    
    for (int i = 0; i <= depth; i++) {
        printf("%s\n", hangmanParts[i]);
    }
}

int main(){

    struct word_with_hint word_list[] = {{"elephant","mammal with a trunk"},{"cat","a cute jerk which purrs"},
                                 {"lion","King of the jungle"} };
    int rand_comp = (rand() % 3);
    char target_word[10];
    strcpy(target_word ,word_list[rand_comp].word);
    int len = strlen(target_word);
    char display_word[100];
    char guessed;
    int tries = -1;
    
    // Fill display_word with underscores
    for (int i = 0; i < len; i++) {
        display_word[i] = '_';
    }
    display_word[len] = '\0'; // end string

    while (strcmp(display_word, target_word) != 0) {


        if(tries != -1){
            printf("\nTries left:%d\n",4 - tries);
            draw_hangman(tries);
            printf("\n---------\n");
            if(tries > 4){
                printf("-----------------\n");
                printf("|----YOU LOSE----|\n");
                printf("------------------\n");
                return 0;
            }
        }
        printf("\n Hint: %s", word_list[rand_comp].hint);
        printf("\nWord: %s\n", display_word);
        printf("Enter a letter: ");
        scanf(" %c", &guessed);
        guessed = tolower(guessed);

        bool found = false;

        for (int i = 0; i < len; i++) {
            if (target_word[i] == guessed && display_word[i] == '_') {
                display_word[i] = guessed; // reveal the letter in correct position
                found = true;
            }
        }

        if (found) {
            printf("Good guess!\n");
        } else {
            printf("Try again!\n");
            tries++;
            
        }
    }

    printf("You guessed the full word: %s\n", target_word);

    return 0;
}
