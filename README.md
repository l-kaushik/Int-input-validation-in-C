# Input-validation-in-C
Getting numbers in input from user is a crucial task in C. As if user enter some alphabets then the program just crash.

In this repository I've tried to deal with the problem.

I am expecting you have some basic knowledge of number systems and knows about [functions](https://www.geeksforgeeks.org/c-functions/), [arguments](https://www.w3schools.com/c/c_functions_parameters.php), [string](https://www.w3schools.com/c/c_strings.php#:~:text=Unlike%20many%20other%20programming%20languages,double%20quotes%20(%20%22%22%20).) and little bit about [C streams](https://stackoverflow.com/questions/38652953/what-does-stream-mean-in-c#:~:text=of%20bytes%2C%20while-,Streams,-are%20just%20facilitators), etc.

# Description
## What causes the crashing of program?
The first question that comes in mind is why actually the program crashed whenever user input alphabets instead of numbers?

<span style="color: red;"><strong>NOTE:-</strong></span>
In some IDEs the program don't crash and gives garbage values instead of throwing an error.

Whenever you hit a key on your keyboard the input character goes to stdin(Standard input) which is one of the input [stream](https://stackoverflow.com/questions/38652953/what-does-stream-mean-in-c#:~:text=of%20bytes%2C%20while-,Streams,-are%20just%20facilitators) of C. Basically it is reponsible for handling input associated with keyboard or another input devices.

After that the [scanf()](https://www.geeksforgeeks.org/scanf-in-c/) or [sscanf()](https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm) functions try to convert it to desired format specifier
like:- 
* %d --> for decimal
* %o --> for octal
* %x or %X --> for hexadecimal


Let's say you enter 3 then stdin will get it as '3' then scanf try to convert it to decimal and the conversion rules are defined by the C standard library.

But in case where stdin gets 'a' as an input, then scanf try to convert it to decimal too but it simply stops or in some case throws error or just simply returns a garbage value.

# Exploring intval.c
The code present in the file intval.c expect an integer input from user and when it gets, it prints the output and in case of not, it simply throws an error rather than just returning a garbage value.

Let's break it down and understand 

## How it works?

```C
int main()
{
    long long num;
    printf("Enter a number:- ");
    num = intval();
    return 0;
}
```

Above is the main function of the program and it just simply calls a function named "intval()" and stores the return output into num for further use case.

```C
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
```
This is the core function of the program that do the main validation of inputed number.

### Key points to notice
* ```C
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    ```
    * The function [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer), is declared inside `stdlib.h`
    * The function [strcspn()](https://www.ibm.com/docs/en/zos/2.4.0?topic=programs-strcspn-compare-strings) is declared insdie `string.h`

* The program is in an infinite while loop and only breaks when gets a valid input or when the if condition fails.


### The if condition
```C
if (fgets(input, sizeof(input), stdin) != NULL)
```
This line looks scary but it's not that scary.

Here, I am checking if the return value of [fgets()](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-fgets-read-string-from-stream) is `NULL` or not.

<span style="color: red;"><strong>NOTE:-</strong></span> The [fgets()](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-fgets-read-string-from-stream) function returns `NULL` when its failed to read the input, basically its an sign of error. And returns pointer to the string buffer if successful.

And the function [fgets()](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-fgets-read-string-from-stream) takes 3 arguments:
* char *str  --> basically pointer to a character array, in our case its "input"
* int n --> the 2nd argument is the maximum number of characters to be read including the final null-character. Which is equivalent to length of the character array.
* FILE *stream --> stream refers to from where to read the characters, as we sending the input from keyboard so we using stdin stream

If you don't get it then, I would say its totally fine, you will get it with passage of time.

So, here I am using the [fgets()](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-fgets-read-string-from-stream) function to get input from the user, and that input is in string format. Later, in the next line 
```C
input[strcspn(input, "\n")] = '\0';
``` 
I am using [strcspn()](https://www.ibm.com/docs/en/zos/2.4.0?topic=programs-strcspn-compare-strings) function to remove the whitespaces from the begining of the string, because when you use the [fgets()](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-fgets-read-string-from-stream) function there is chance of having a whitespace.

### The strtoll() function

```C++
result = strtoll(input, &endptr, 10);
```
This is the another important line, the function [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer), basically means **string to long long**. This function takes 3 arguments:
* char *str --> which is basically the character array, in our case its "input"
* char **endptr --> this is basically address of a character pointer     
    ```C 
    char *endptr = NULL;
    ``` 
    declared here, and used as `&endptr` which means giving address of pointer "endptr" to [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer),.
    [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer), use this pointer to store the non-numeric characters, it can be a whitespaces and any other characters.
* int base --> The last argument is the base number in which the function expect the number to be.
    Its value is from 2 to 36. 
    
    In our case its 10, because we only want to verify a decimal number inputted by user, if the base is set to 16, then 0-9 and A-F or a-f all are considered as valid input characters, because base 16 is a hexadecimal number that contains a-f characters for the representation of 10-15.

**Return value:-** The [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer), function returns a long long int number. 

```C
if (*endptr != '\0')
{
    printf("Invalid input. Please try again.\n");
}
else
{
    printf("The number is %lld", result); 
    return result; 
}
```
In this condition, I am checking if the "endptr" is still `NULL` or not.
`'\0'` is a symbolic way of saying `NULL`.

### The Basic Work Flow

Getting input from the user using [fgets()](https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-fgets-read-string-from-stream), then removing the spaces from begining of the string using [strcspn()](https://www.ibm.com/docs/en/zos/2.4.0?topic=programs-strcspn-compare-strings) and using [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer), function to sorting the non numeric characters and storing them using endptr and at last sorting the number according to their base given to the function and storing it in "result".

If the endptr contains a character, then printing an error says `Invalid input. Please try again.` which means that there is some character/s inputed by user, if not then storing the final result to result variable and also returning it. 

And that's how validating an user input.

# Exploring floatval.c

If you look at floatval.c,

```C
int main()
{
    double num;
    printf("Enter a float number:- ");
    num = floatval();

    return 0;
}
```
The main function is similar as intval but the only difference is the num is of double datatype.

Here, you can use long double, which can store larger values than double datatype, but for my system both are kinda same.

```C
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
           
            result = strtod(input, &endptr);

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

```

Here is the conversion function, whose return type is also double and this functoin is totaly similar to intval() the only difference is here:

```C++
result = strtod(input, &endptr);
```

The [strtod()](https://www.ibm.com/docs/en/zos/2.4.0?topic=programs-strtod-convert-character-string-double) stands for **string to double** works in similar way as `stroll()`, but you can see there is no 3rd argument here, which is "int base" in case of [strtoll()](https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer),.

```C
printf("The number is %.15Lg", result);
```

In the print statement the precision is set to .15 and Lg is format specifier to print the long double value, now again double and long double are kinda similar for my system but can be different for your system.

Lg is used when we want the long output values in scientific notation, but you don't want then you can use Lf.

I guess we are done, here and using both of these function you can validate a user input, try to tweaks with datatypes. 

# Limitations
Although, this program looks well finished but it contains some limitations too, 

1. Values beyond datatype limit can't be stored.
2. Limited precision in float values.

I hope this will help you in some case, and if you have any query or any problem you can email me.

