#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main() {
    int word = 1, letters = 0, sentences = 0, grade = 0;
    float index = 0, average_S = 0, average_L = 0;
    string text = get_string("Text: ");

    for (int i = 0; i < strlen(text); i++) {
        // Checking all characters in the text and counting letters, words and sentences.

        if (isalpha(text[i])) {
            letters++;
        }
        else if (isspace(text[i])) {
            word++;
        }
        else if (text[i] == '!' || text[i] == '?' || text[i] == '.') {
            sentences++;
        }
    }

    // Calculating averages
    average_L = ((float) letters / (float) word) * 100;
    average_S = ((float) sentences / (float) word) * 100;

    // Calculating Grade
    index = (0.0588 * average_L) - (0.296 * average_S) - 15.8;

    grade = round(index);

    // Output
    if (grade >= 16) {
        printf("Grade 16+\n");
        return 0;
    }

    if (grade < 1) {
        printf("Before Grade 1\n");
        return 0;
    }

    printf("Grade %d\n", grade);
}
