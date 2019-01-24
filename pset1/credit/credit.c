#include <stdio.h>
#include <cs50.h>

int validateCCNumber(long num)
{
    // Set up holding variables
    int digit1 = 0;
    int digit2 = 0;
    int counter = 0;
    int sumOfEvens = 0;
    int sumOfDoubleOdds = 0;

    while (num > 0)
    {
        digit2 = digit1;
        digit1 = num % 10;

        if (counter % 2 == 0)
        {
            sumOfEvens += digit1;
        }
        else
        {
            sumOfDoubleOdds += (2 * digit1 / 10) + (2 * digit1 % 10);
        }

        num /= 10;
        counter++;
    }

    if ((sumOfEvens + sumOfDoubleOdds) % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    long num = get_long("Number: ");

    if (num - 100000000000000 < 0) // Less than 15 digits
    {
        printf("INVALID\n");
    }
    else
    {
        if (num - 1000000000000000 < 0) // Exactly 15 digits, so check if it's Amex
        {
            if (num / 10000000000000 != 34 && num / 10000000000000 != 37) // First digits aren't valid Amex digits
            {
                printf("INVALID\n");
            }
            else
            {
                // Check that number is valid
                if (validateCCNumber(num))
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        else if (num - 10000000000000000 >= 0) // More than 16 digits
        {
            printf("INVALID\n");
        }
        else // Exactly 16 digits
        {
            if (num / 1000000000000000 == 4) // Visa
            {
                // Check validity
                if (validateCCNumber(num))
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (num / 100000000000000 == 51 || num / 100000000000000 == 52 || num / 100000000000000 == 53
                     || num / 100000000000000 == 54 || num / 100000000000000 == 55) // Mastercard
            {
                // Check validity
                if (validateCCNumber(num))
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else // Not Mastercard or Visa
            {
                printf("INVALID\n");
            }
        }
    }

    return 0;
}
