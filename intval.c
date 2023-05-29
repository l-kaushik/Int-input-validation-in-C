#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long intval()
{
    char input[100];
    long long result;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; //removing trailng spaces

            char *endptr = NULL;

            result = strtoll(input, &endptr, 10);

            if (*endptr != '\0')
            {
                printf("Invalid input. Please try again.\n");
            }
            else
            {
                printf("The number is %lld", result); 
                return result; 
            }
        }
        else
        {
            return -1;
        }
    }
}

int main()
{
    long long num;
    printf("Enter a number:- ");
    num = intval();
    return 0;
}