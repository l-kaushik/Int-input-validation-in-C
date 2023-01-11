#include <stdio.h>
#include <stdlib.h>

float floatval()
{
    char input[100];
    int check;
    double result;

    while (1)
    {
        check = scanf(" %[^\n]s", &input); 
        if (check == 1)
        {
            char *endptr;

            result = strtof(input, &endptr);

            if (*endptr != '\0')
            {
                printf("Invalid input. Please try again.\n");
            }
            else
            {
                printf("The number is %f",result);
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
    float num;
    printf("Enter a float number:- ");
    num = floatval();

    return 0;
}
