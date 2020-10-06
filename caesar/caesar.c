#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    string plaintext = "";
    int key = 0;

    // Check if the key has more than one value or if the key is negative
    if (argc != 2 || atoi(argv[1]) < 0) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if the key is non-numeric
    for (int i = 0; i < strlen(argv[1]); i++) {
        bool isAlpha = isalpha(argv[1][i]);

        if (isAlpha) {
            printf("Erro! Key invalid");
            return 1;
        }
    }

    key = atoi(argv[1]);

    plaintext = get_string("Plaintext: ");

    printf("ciphertext: ");

    // Encrypting character and showing
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            bool isUpper = isupper(plaintext[i]);
            int ciphertext = isUpper ? ((plaintext[i] - 65 + key) % 26) +65 : ((plaintext[i] - 97 + key) % 26) +97;

            printf("%c", ciphertext);
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
