#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            BYTE original_blue = pixel.rgbtBlue;
            BYTE original_green = pixel.rgbtGreen;
            BYTE original_red = pixel.rgbtRed;
            // Calculte using the sepia formula
            int new_red = round(0.393 * original_red + 0.769 * original_green + 0.189 * original_blue);
            int new_green = round(0.349 * original_red + 0.686 * original_green + 0.168 * original_blue);
            int new_blue = round(0.272 * original_red + 0.534 * original_green + 0.131 * original_blue);
            if(new_red > 255) {new_red = 255;}
            if(new_green > 255) {new_green = 255;}
            if(new_blue > 255) {new_blue = 255;}
            image[i][j].rgbtBlue = new_blue;
            image[i][j].rgbtGreen = new_green;
            image[i][j].rgbtRed = new_red; 
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
