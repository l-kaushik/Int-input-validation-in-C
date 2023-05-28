#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int intval()
{
    char input[100];
    long result;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; //removing trailng spaces

            char *endptr = NULL;

            result = strtol(input, &endptr, 10);

            if (*endptr != '\0')
            {
                printf("Invalid input. Please try again.\n");
                // printf("%d",result);
            }
            else
            {
                printf("The number is %d", result); 
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
    int num;
    printf("Enter a number:- ");
    num = intval();
    return 0;
}