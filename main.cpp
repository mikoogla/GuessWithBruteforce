#include <iostream>
#include <string.h>

#define MAX_LENGTH 10
#define MIN_LENGTH 10

bool isAllEnd(char character, char *string, int stop)
{
    for (int i = 0; i < stop; i++)
    {
        if (*(string + i) != character)
        {
            return false;
        }
    }
    return true;
}
int returnAlphaIndex(char c, char *alpha)
{
    for (int i = 0; i < sizeof(alpha) - 1; i++)
    {
        if (*(alpha + i) == c)
        {
            return i;
        }
    }
    return -1;
}
int incrementLeft(char *alpha, char *guess, int *index)
{

    for (int i = *index; i >= 0; i--)
    {
        if (guess[i] != alpha[strlen(alpha) - 1])
        {
            int alphaindex = returnAlphaIndex(guess[i], alpha);
            *(guess + i) = alpha[alphaindex + 1];
            for (int j = i + 1; j <= *index; j++)
            {
                guess[j] = alpha[0];
            }
            return 0;
        }
    }
}

int brute(char *pass, char *alpha, char *guess, int *index)
{
    int danger = 0;
    int alphaindex = 0;
    // printf("pass: %s, alpha: %s, guess: %s\n initial index: %d\n", pass, alpha, guess, *index);
    while (true)
    {
        while (*(guess + *index) != alpha[strlen(alpha) - 1])
        {

            if (strcmp(pass, guess) == 0)
            {
                printf("password is %s\n", guess);
                return 0;
            }
            alphaindex++;
            *(guess + *index) = alpha[alphaindex];
        }

        if (strcmp(pass, guess) == 0)
        {
            printf("password is %s\n", guess);
            return 0;
        }
        alphaindex = 0;

        if (isAllEnd(alpha[strlen(alpha) - 1], guess, strlen(guess)))
        {
            puts("out of combinations");
            return 1;
        }
        incrementLeft(alpha, guess, index);
    }
    return 0;
}
int main()
{
    char guess[MAX_LENGTH + 10] = {};

    printf("-%s-\n", guess);

    char pass[] = "ewewwewewe";
    char alpha[] = "we";

    for (int i = MIN_LENGTH; i <= MAX_LENGTH; i++)
    {
        for (int j = 0; j < i; j++)
        {
            guess[j] = alpha[0];
        }
        int index = strlen(guess) - 1;
        printf("guessing %d length\n", i);
        if (brute(pass, alpha, guess, &index) == 0)
        {
            return 0;
        }
        memset(guess, '\0', MAX_LENGTH + 10);
    }
    return 0;
}
