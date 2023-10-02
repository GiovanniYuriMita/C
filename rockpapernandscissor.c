#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

const char* pcset(void);

void strup(char* str);

char* uschoice(void);

char* options_array[] = 
{
    "PEDRA", 
    "PAPEL", 
    "TESOURA"
};

int matchresult(char *a, const char *b);

int main(void)
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
    
    char* userchoice = uschoice();
    
    // Printing PC Choice on Screen
    printf("The PC choice was: %s\n", pcchoice);

    // Printing Player Choice on Screen
    printf("The player choice was: %s\n", userchoice);

    int wincount = 0;
    int drawcount = 0;
    int losscount = 0;

    int result = matchresult(userchoice, pcchoice);

    if(result == 1)
    {
        wincount++;
    }

    else if(result == 0)
    {
        drawcount++;
    }

    else
    {
        losscount++;
    }

    // Freeing userchoice Memory
    free(userchoice);

    printf("Win count: %i\n Loss count: %i\n Draw count: %i\n", wincount, losscount, drawcount);

    return (0);
}

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

void strup(char* str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
}

char* uschoice(void)
{
    int num_options_array = sizeof(options_array) / sizeof(options_array[0]);

    char* userchoice = malloc(10);
        do
        {
            scanf("%s", userchoice);

            strup(userchoice);

            int ValidChoice = 0;    
            for (int i = 0; i < num_options_array; i++)    
                if (strcmp(userchoice, options_array[i]) == 0) 
                {
                    ValidChoice = 1;
                    break;
                }

            if(ValidChoice)
                break;

            else
                printf("Por favor, digite [Pedra], [Papel] ou [Tesoura]: ");
        }
        while (1);

        return userchoice;
}

int matchresult(char *a, const char *b)
{

    if(strcmp(a, "PEDRA") == 0 && strcmp(b, "TESOURA") == 0 ||
       strcmp(a, "PAPEL") == 0 && strcmp(b, "PEDRA") == 0 ||
       strcmp(a, "TESOURA") == 0 && strcmp(b, "PAPEL") == 0)
    {
        return 1; // Player Win
    }

    else if(strcmp(a, b) == 0)
    {
        return 0; // Draw
    }

    else
    {
        return -1; // Player Loss
    }
}