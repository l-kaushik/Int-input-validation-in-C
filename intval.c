#include <stdio.h>
#include <stdlib.h>

int intval()
{
    char input[100];
    int check;
    long result;

    while (1)
    {
        check = scanf(" %[^\n]s", &input);
        if (check == 1)
        {
            char *endptr;

            result = strtol(input, &endptr, 10);

            if (*endptr != '\0')
            {
                printf("Invalid input. Please try again.\n");
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