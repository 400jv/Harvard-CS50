#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool isJpg(BYTE buffer[]);

int main(int argc, char *argv[]) {
    FILE* card = fopen(argv[1], "r");
    FILE* image = NULL;
    int imageCount = 0;
    char* filename = malloc(8);
    BYTE buffer[512];

    if (!card) {
        printf("Usage: ./recover image\n");
        free(filename);
        return 1;
    }

    while (fread(buffer, sizeof(BYTE), 512, card) || feof(card) == 0) {
        if (isJpg(buffer)) {
            if (image) fclose(image);

            sprintf(filename, "%03i.jpg", imageCount);
            image = fopen(filename, "w");
            imageCount++;
        }

        if (image) {
            fwrite(buffer, sizeof(buffer), 1, image);
        }
    }

    if (!card) fclose(card);
    if (!image) fclose(image);
    free(filename);
}

bool isJpg(BYTE buffer[]) {
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}