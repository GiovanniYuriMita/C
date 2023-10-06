#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// Calling functions and setting global variables 
const char* pcset(void);

void strup(char* str);

char* uschoice(void);

char* options_array[] = 
{
    "PEDRA", 
    "PAPEL", 
    "TESOURA"
};

// Determines whether the game is running or not
int game_run = 1;


int matchresult(char *a, const char *b);

// Setting win, draw and loss count
int wincount = 0;
int drawcount = 0;
int losscount = 0;

int game();

// Main func
int main(void)
{
    do
    {
    game();
    } 
    while (game_run == 1);
    
    
    return 0;
}

// Function to set PC choice
const char* pcset(void)
{

    // Getting the number of strings in the options_array
    int num_options_array = sizeof(options_array) / sizeof(options_array[0]);

    // Creating random index for the RNG
    int random_index = rand() % num_options_array;

    // Choosing the PC choice
    const char* pcchoice = options_array[random_index];

    return pcchoice;
}

// Function to capitalize any string
void strup(char* str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
}

// Function to get user choice
char* uschoice(void)
{
    // Getting the size of valid options array
    int num_options_array = sizeof(options_array) / sizeof(options_array[0]);

    // Allocating memory to user input
    char* userchoice = malloc(8);
        do
        {
            scanf("%s", userchoice);

            strup(userchoice);

            // Comparing user input with valid options
            int ValidChoice = 0;    
            for (int i = 0; i < num_options_array; i++)    
                if (strcmp(userchoice, options_array[i]) == 0) 
                {
                    ValidChoice = 1;
                    break;
                }

            if(ValidChoice)
                break;
            
            // Invalid user input; Asking again...
            else
                printf("Por favor, digite [Pedra], [Papel] ou [Tesoura]: ");
        }
        while (1);

        // Returning User Choice
        return userchoice;
}

// Function to get match results
int matchresult(char *a, const char *b)
{
    // Setting win conditions
    if(strcmp(a, "PEDRA") == 0 && strcmp(b, "TESOURA") == 0 ||
       strcmp(a, "PAPEL") == 0 && strcmp(b, "PEDRA") == 0 ||
       strcmp(a, "TESOURA") == 0 && strcmp(b, "PAPEL") == 0)
    {
        return 1; // Player Win
    }

    // If user and pc choices are equal, then it's a draw
    else if(strcmp(a, b) == 0) 
    {
        return 0; // Draw
    }

    else
    {
        return -1; // Player Loss
    }
}

// The game itself
int game()
{
    // RNG set
    srand(time(NULL));

    // Picking random_option from pcchoice
    const char* pcchoice = pcset();

    // Getting the size of the options array from pcchoice
    int num_options_array = sizeof(options_array) / sizeof(options_array[0]);

    // Print Title of the Game
    printf("--- Rock Paper Scissors ---\n");

    // Print Player Options
    printf("Escolha o que vai jogar (Pedra, Papel, Tesoura): ");
    
    // Importing userchoice function
    char* userchoice = uschoice();
    
    // Printing PC Choice on Screen
    printf("The PC choice was: %s\n", pcchoice);

    // Printing Player Choice on Screen
    printf("The player choice was: %s\n", userchoice);

    // Getting Match Result
    int result = matchresult(userchoice, pcchoice);

    // Adding wincount
    if(result == 1)
    {
        wincount++;
    }

    // Adding drawcount
    else if(result == 0)
    {
        drawcount++;
    }

    // Adding losscount
    else
    {
        losscount++;
    }

    // Freeing userchoice Memory
    free(userchoice);

    // Printing Results
    printf("Vitórias: %i\nDerrotas: %i\nEmpates: %i\n", wincount, losscount, drawcount);

    // Setting Play Again
    printf("Deseja jogar novamente?\n");
    char useryn;
    do
    {
        // Get User "Yes" or "No"
        scanf("%c", &useryn);

        // Capitalizing User Answer
        useryn = toupper(useryn);

        // If user didn't type a valid answer
        if(useryn != 'S' && useryn != 'N')
        {
            printf("Por favor, digite [S] ou [N]: ");

        }

        // Restarting game
        else if(useryn == 'S')
        {
            printf("Reiniciando o jogo...\n");
            break;
            
        }

        // Ending game
        else
        {
            printf("Encerrando o jogo...\n");
            game_run = 0;
            break;
        }
    }
    while (1);

    return 0;
}