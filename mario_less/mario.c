#include <cs50.h>
#include <stdio.h>

// Prompt user for height correct
int get_height(void);

int main(void) {
    int height = get_height();

    for (int i = 0; i < height; i++) {
        for (int l = 0; l < height - i; l++) {
            printf(" ");
        }

        for (int j = 0; j <= i; j++) {
            printf("#");
        }

        printf("\n");
    }
}

int get_height(void) {
    int height = get_int("Height: ");

    // loop for handling error
    while (height <= 0 || height > 8) {
        printf("Error!, Please enter a number between 1 and 8!\n");
        height = get_int("Height: ");
    }

    return height;
}
