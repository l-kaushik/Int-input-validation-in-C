#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double floatval()
{
    char input[100];
    double result;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; // removing the trailing spaces
            char *endptr;

            result = strtold(input, &endptr);

            if (*endptr != '\0')
            {
                printf("Invalid input. Please try again.\n");
            }
            else
            {
                printf("The number is %.15Lg", result);
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
       double num;
        printf("Enter a float number:- ");
        num = floatval();

    return 0;
}
