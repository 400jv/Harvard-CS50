#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed +1) / 3;


            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255) sepiaRed = 255;
            else if (sepiaRed < 0) sepiaRed = 0;

            if (sepiaGreen > 255) sepiaGreen = 255;
            else if (sepiaGreen < 0) sepiaGreen = 0;

            if (sepiaBlue > 255) sepiaBlue = 255;
            else if (sepiaBlue < 0) sepiaBlue = 0;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width /2; j++)
        {
            RGBTRIPLE* pixel = &image[i][j];
            RGBTRIPLE* pixelReverse =  &image[i][(width -1) -j];
            RGBTRIPLE tmp = *pixel;

            *pixel = *pixelReverse;
            *pixelReverse = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumBlue = 0, sumGreen = 0, contPlus = 0;

            for (int l = -1; l <= 1; l++)
            {
                for (int c = -1; c <= 1; c++)
                {

                    int pixelL = i + l;
                    int pixelC = j + c;

                    if (pixelL < 0 || pixelL > height -1 || pixelC < 0 || pixelC > width -1) continue;

                    sumRed += image[pixelL][pixelC].rgbtRed;
                    sumBlue += image[pixelL][pixelC].rgbtBlue;
                    sumGreen += image[pixelL][pixelC].rgbtGreen;
                    contPlus++;
                }
            }

            temp_image[i][j].rgbtRed = round((float) sumRed / contPlus);
            temp_image[i][j].rgbtBlue = round((float) sumBlue / contPlus);
            temp_image[i][j].rgbtGreen = round((float) sumGreen / contPlus);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j< width; j++)
        {
            image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
        }
    }

    return;
}
