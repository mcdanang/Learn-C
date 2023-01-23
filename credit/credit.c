#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt user for number
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1);
    long m = n;

    //initiate count & sum
    int count = 0;
    int sum = 0;
    while (n > 0)
    {
        //Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together
        if ((count + 1) % 2 == 0)
        {
            int multi = n % 10 * 2;
            if (multi >= 10)
            {
                multi = multi % 10 + 1;
            }
            sum = sum + multi;
        }
        //Add the sum to the sum of the digits that weren’t multiplied by 2
        else
        {
            sum = sum + (n % 10);
        }
        n = n / 10;
        count++;
    }
    //get the first 2 digit
    long firstDigit = m;
    for (int i = 0; i < count - 2; i++)
    {
        firstDigit = firstDigit / 10;
    }

    // printf("Sum: %i\n", sum);
    // printf("Count: %i\n", count);
    // printf("firstDigit: %li\n", firstDigit);

    //If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    if (sum % 10 == 0)
    {
        if (count == 15 && (firstDigit == 34 || firstDigit == 37))
        {
            printf("AMEX\n");
        }
        else if (count == 16 && (firstDigit == 51 || firstDigit == 52 || firstDigit == 53 || firstDigit == 54 || firstDigit == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && firstDigit / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}