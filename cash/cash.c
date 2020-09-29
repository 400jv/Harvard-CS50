#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    int cents = 0;
    float dollars = get_float("Change owed: ");

    while (dollars <= 0) {
        printf("Error!, Please enter a number correct!\n");
        dollars = get_float("Change owed: $");
    }

    dollars = round(dollars * 100);

    while (dollars != 0) {
        if (dollars >= 25) {
            dollars = dollars - 25;
            cents++;
        }

        else if (dollars >= 10) {
            dollars = dollars - 10;
            cents++;
        }

        else if (dollars >= 5) {
            dollars = dollars - 5;
            cents++;
        }

        else if (dollars >= 1) {
            dollars = dollars - 1;
            cents++;
        }
    }

    printf("%i\n", cents);
}

