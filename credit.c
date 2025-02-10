#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void AmericanExpress(long num);
void Visa(long num);
bool Master(long num);
void VisaOrMasterCard(long num);
bool CheckSecretCode(long num);

int main(void)
{
    long num;
    char str[20];

    printf("check whether it is (MasterCard or AmericanExpress or Visa) \n ");
again:
    do
    {
        printf("Number (13 degits to 16 digits):");

        scanf("%s", &str);

    } while (!(sscanf(str, "%li", &num)));

    // know how many degits entered by user
    int degits = 0;
    long copy_num = num;
    while (copy_num != 0)
    {
        copy_num /= 10;
        ++degits;
    }

    // knowing which card it is
    switch (degits)
    {
    case 15:
        AmericanExpress(num);
        break;
    case 16:
        VisaOrMasterCard(num);
        break;
    case 13:
        Visa(num);
        break;
    default:
        printf("It is not above mention cards numbers \"TRY AGAIN!\"\n\n");
        goto again;
    }

    return 0;
}

void AmericanExpress(long num)
{
    if ((num < 380000000000000 && num >= 370000000000000) ||
        (num < 350000000000000 && num >= 340000000000000))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
        printf("It's Fake Number!");
    }
}

void Visa(long num)
{
    // for 13 degits
    if (num >= 4000000000000 && num < 5000000000000)
    {
        if (CheckSecretCode(num))
        {
            printf("INVALID\n");
            printf("It's Fake Number");
            return;
        }
        printf("VISA\n");
    }
    // for 16 degits
    else if ((num >= 4000000000000000 && num < 5000000000000000))
    {
        if (CheckSecretCode(num))
        {
            printf("INVALID\n");
            printf("It's Fake Number");
            return;
        }
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
        printf("It's Fake Number!");
    }
}

bool Master(long num)
{
    if (5100000000000000 <= num && 5600000000000000 > num)
    {
        return true;
    }

    return false;
}

void VisaOrMasterCard(long num)
{
    if (Master(num))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        Visa(num);
    }
}

bool CheckSecretCode(long num)
{

    int degits_place = 0;
    long copy_num = num;
    int sum = 0;
    int rem;

    // step 1 multiply  by 2 with alternate numbers in reverse order
    while (copy_num != 0)
    {
        degits_place++;
        rem = copy_num % 10;
        if (degits_place % 2 == 0)
        {
            int doubled = (rem * 2);

            if (doubled > 9)
            {
                sum += (doubled % 10) + (doubled / 10);
            }
            else
            {
                sum += doubled;
            }
        }
        else
        {
            sum += rem; // Add undoubled digits
        }

        copy_num /= 10;
    }

    return (sum % 10) ? true : false;
}
