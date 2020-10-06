#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    string plaintext = "";
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alphabetKey[26];

    // Check if the key has more than one value
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key has number or if it has duplicate value
    for (int i = 0; i < strlen(argv[1]); i++) {
        bool isNumber = !isalpha(argv[1][i]);

        if (isNumber) {
            printf("Key must only contain alphabetic characteres.\n");
            return 1;
        }
        alphabetKey[i] = argv[1][i];

        for (int j = 0; j < i; j++) {
            if (alphabetKey[j] == argv[1][i]) {
                printf("%c = %c ", alphabetKey[i], argv[1][i]);
                printf("Key must not contain repeated characteres.\n");
                return 1;
            }
        }
    }

    if (strlen(argv[1]) < 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++) {

        // if it is space, special character or a number just shows
        if (ispunct(plaintext[i]) || isspace(plaintext[i]) || isdigit(plaintext[i])) {
            printf("%c", plaintext[i]);
        } else {
            // output ciphertext followed by the plaintext’s corresponding ciphertext
            for (int j = 0; j < 26; j++) {
                if (toupper(plaintext[i]) == toupper(alphabet[j])) {
                    if (isupper(plaintext[i])) {
                        printf("%c", toupper(alphabetKey[j]));
                    } else {
                        printf("%c", tolower(alphabetKey[j]));
                    }
                }
            }
        }
    }
    printf("\n");
}
