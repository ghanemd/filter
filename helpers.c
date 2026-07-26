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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < (width/2); j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Implement the algorithm
    int number_neighbors;
    int total_red;
    int total_green;
    int total_blue;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            number_neighbors = 0;
            total_red = 0;
            total_green = 0;
            total_blue = 0;

            if(i > 0){
                if(j > 0){
                    total_red += copy[i-1][j-1].rgbtRed;
                    total_green += copy[i-1][j-1].rgbtGreen;
                    total_blue += copy[i-1][j-1].rgbtBlue;
                }
                total_red += copy[i-1][j].rgbtRed;
                total_green += copy[i-1][j].rgbtGreen;
                total_blue += copy[i-1][j].rgbtBlue;
                if(j < width - 1){
                    total_red += copy[i-1][j+1].rgbtRed;
                    total_green += copy[i-1][j+1].rgbtGreen;
                    total_blue += copy[i-1][j+1].rgbtBlue;
                }
            }

            if(j > 0){
                total_red += copy[i][j-1].rgbtRed;
                total_green += copy[i][j-1].rgbtGreen;
                total_blue += copy[i][j-1].rgbtBlue;
            }
            total_red += copy[i][j].rgbtRed;
            total_green += copy[i][j].rgbtGreen;
            total_blue += copy[i][j].rgbtBlue;
            if(j < width - 1){
                total_red += copy[i][j+1].rgbtRed;
                total_green += copy[i][j+1].rgbtGreen;
                total_blue += copy[i][j+1].rgbtBlue;
            }

            if(i < height - 1){
                if(j > 0){
                    total_red += copy[i+1][j-1].rgbtRed;
                    total_green += copy[i+1][j-1].rgbtGreen;
                    total_blue += copy[i+1][j-1].rgbtBlue;
                }
                total_red += copy[i+1][j].rgbtRed;
                total_green += copy[i+1][j].rgbtGreen;
                total_blue += copy[i+1][j].rgbtBlue;
                if(j < width - 1){
                    total_red += copy[i+1][j+1].rgbtRed;
                    total_green += copy[i+1][j+1].rgbtGreen;
                    total_blue += copy[i+1][j+1].rgbtBlue;
                }
            }

            image[i][j].rgbtBlue = round(total_blue / (float) number_neighbors);
            image[i][j].rgbtGreen = round(total_green / (float) number_neighbors);
            image[i][j].rgbtRed = round(total_red / (float) number_neighbors);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Compute the Gx values
    int gx_red[height][width];
    int gx_green[height][width];
    int gx_blue[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            if(i > 0)
            {
                if(j > 0){
                    gx_red[i][j] -= image[i-1][j-1].rgbtRed;
                    gx_green[i][j] -= image[i-1][j-1].rgbtGreen;
                    gx_blue[i][j] -= image[i-1][j-1].rgbtBlue;
                }
                if(j < width - 1){
                    gx_red[i][j] += image[i-1][j+1].rgbtRed;
                    gx_green[i][j] += image[i-1][j+1].rgbtGreen;
                    gx_blue[i][j] += image[i-1][j+1].rgbtBlue;
                }
            }

            if(j > 0){
                gx_red[i][j] -= 2 * image[i][j-1].rgbtRed;
                gx_green[i][j] -= 2 * image[i][j-1].rgbtGreen;
                gx_blue[i][j] -= 2 * image[i][j-1].rgbtBlue;
            }
            if(j < width - 1){
                gx_red[i][j] += 2 * image[i][j+1].rgbtRed;
                gx_green[i][j] += 2 * image[i][j+1].rgbtGreen;
                gx_blue[i][j] += 2 * image[i][j+1].rgbtBlue;
            }

            if(i < height - 1)
            {
                if(j > 0){
                    gx_red[i][j] -= image[i+1][j-1].rgbtRed;
                    gx_green[i][j] -= image[i+1][j-1].rgbtGreen;
                    gx_blue[i][j] -= image[i+1][j-1].rgbtBlue;
                }
                if(j < width - 1){
                    gx_red[i][j] += image[i+1][j+1].rgbtRed;
                    gx_green[i][j] += image[i+1][j+1].rgbtGreen;
                    gx_blue[i][j] += image[i+1][j+1].rgbtBlue;
                }
            }

        }
    }

    // Compute the Gy values
    int gy_red[height][width];
    int gy_green[height][width];
    int gy_blue[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            if(i > 0)
            {
                if(j > 0)
                {
                    gy_red[i][j] -= image[i-1][j-1].rgbtRed;
                    gy_green[i][j] -= image[i-1][j-1].rgbtGreen;
                    gy_blue[i][j] -= image[i-1][j-1].rgbtBlue;
                }
                gy_red[i][j] -= 2 * image[i-1][j].rgbtRed;
                gy_green[i][j] -= 2 * image[i-1][j].rgbtGreen;
                gy_blue[i][j] -= 2 * image[i-1][j].rgbtBlue;
                if(j < width - 1)
                {
                    gy_red[i][j] -= image[i-1][j+1].rgbtRed;
                    gy_green[i][j] -= image[i-1][j+1].rgbtGreen;
                    gy_blue[i][j] -= image[i-1][j+1].rgbtBlue;
                }
            }

            if(i < height - 1)
            {
                if(j > 0)
                {
                    gy_red[i][j] += image[i+1][j-1].rgbtRed;
                    gy_green[i][j] += image[i+1][j-1].rgbtGreen;
                    gy_blue[i][j] += image[i+1][j-1].rgbtBlue;
                }
                gy_red[i][j] += 2 * image[i+1][j].rgbtRed;
                gy_green[i][j] += 2 * image[i+1][j].rgbtGreen;
                gy_blue[i][j] += 2 * image[i+1][j].rgbtBlue;
                if(j < width - 1)
                {
                    gy_red[i][j] += image[i+1][j+1].rgbtRed;
                    gy_green[i][j] += image[i+1][j+1].rgbtGreen;
                    gy_blue[i][j] += image[i+1][j+1].rgbtBlue;
                }
            }

        }
    }

    // Combine the Gx and Gy values and update the image array
    int g_red;
    int g_green;
    int g_blue;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            g_red = gx_red[i][j] * gx_red[i][j] + gy_red[i][j] * gy_red[i][j];
            g_green = gx_green[i][j] * gx_green[i][j] + gy_green[i][j] * gy_green[i][j];
            g_blue = gx_blue[i][j] * gx_blue[i][j] + gy_blue[i][j] * gy_blue[i][j];
            if(g_red > 255) {image[i][j].rgbtRed = 255;} else {image[i][j].rgbtRed = g_red;}
            if(g_green > 255) {image[i][j].rgbtGreen = 255;} else {image[i][j].rgbtGreen = g_green;}
            if(g_blue > 255) {image[i][j].rgbtBlue = 255;} else {image[i][j].rgbtBlue = g_blue;}
        }
    }

}
