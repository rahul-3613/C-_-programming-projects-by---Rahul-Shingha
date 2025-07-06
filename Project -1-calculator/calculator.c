/*
 * Simple Calculator in C
 * Developed by Rahul Shingha
 */

#include <stdio.h>
#include <math.h>

double division(double, double);
double modulus(int, int);
void print_menu();

int main()
{
    int choice;
    double first, second, result;

    while (1)
    {
        print_menu();
        scanf("%d", &choice);

        if (choice == 7)
        {
            printf("\nThank you for using the calculator.\n");
            break;
        }

        if (choice < 1 || choice > 7)
        {
            fprintf(stderr, "Invalid Menu Choice.\n");
            continue;
        }

        printf("\nPlease enter the first number: ");
        scanf("%lf", &first);
        printf("Now, enter the second number: ");
        scanf("%lf", &second);

        switch (choice)
        {
        case 1: // Add
            result = first + second;
            break;
        case 2: // Subtract
            result = first - second;
            break;
        case 3: // Multiply
            result = first * second;
            break;
        case 4: // Divide
            result = division(first, second);
            break;
        case 5: // Modulus
            result = modulus((int)first, (int)second);
            break;
        case 6: // Power
            result = pow(first, second);
            break;
        }

        if (!isnan(result))
        {
            printf("\nResult of operation is: %.2f\n", result);
        }
    }

    return 0;
}

double division(double a, double b)
{
    if (b == 0)
    {
        fprintf(stderr, "Invalid Argument for Division\n");
        return NAN;
    }
    else
    {
        return a / b;
    }
}

double modulus(int a, int b)
{
    if (b == 0)
    {
        fprintf(stderr, "Invalid Argument for Modulus\n");
        return NAN;
    }
    else
    {
        return a % b;
    }
}

void print_menu()
{
    printf("\n\n---------------------------------\n");
    printf("Welcome to Simple Calculator\n");
    printf("Developed by Rahul Shingha\n");
    printf("\nChoose one of the following options:");
    printf("\n1. Add");
    printf("\n2. Subtract");
    printf("\n3. Multiply");
    printf("\n4. Divide");
    printf("\n5. Modulus");
    printf("\n6. Power");
    printf("\n7. Exit");
    printf("\nNow, enter your choice: ");
}
