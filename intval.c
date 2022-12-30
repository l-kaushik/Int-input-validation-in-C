#include <stdio.h>
#include <stdlib.h>

int intval()
{
    char input[100];
    int check;
    long result;

    while (1)
    {
        check = scanf("%s", &input);
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
                return result;
            }
        }
        else
        {
            return -1;
        }
    }
}
void main()
{
    printf("%d", intval());
}