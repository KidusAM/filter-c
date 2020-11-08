#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int pos[] = {-1,0,1};
    RGBTRIPLE old_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            old_image[i][j] = image[i][j];
    }



    for(int i = 1; i < height-1; i ++)
    {
        for(int j = 1; j < width -1; j++)
        {
            //build the neighbors
            RGBTRIPLE old = old_image[i][j];
            RGBTRIPLE neighbors[9];
            int neigh_count = 0;
            for(int l = 0; l < 3; l++)
            {
                for(int m = 0; m<3; m++)
                {
                    neighbors[neigh_count++] = image[i+pos[l]][j+pos[m]];
                }
            }
            //take the average
            int bavg = 0;
            int gavg = 0;
            int ravg = 0;
            for(int l = 0; l < 9; l++)
            {
                    bavg = bavg + neighbors[l].rgbtBlue;
                    gavg = gavg + neighbors[l].rgbtGreen;
                    ravg = ravg + neighbors[l].rgbtRed;
            }


            bavg = bavg / 9;
            gavg = gavg / 9;
            ravg = ravg / 9;
            image[i][j].rgbtBlue = bavg;
            image[i][j].rgbtGreen = gavg;
            image[i][j].rgbtRed = ravg;



            // old_image[i][j] = old;


        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

int pos[] = {-1,0,1};
    int kernelx[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    int kernely[3][3] = {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };
    RGBTRIPLE old_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            old_image[i][j] = image[i][j];
    }



    for(int i = 1; i < height-1; i ++)
    {
        for(int j = 1; j < width -1; j++)
        {
            //build the neighbors
            RGBTRIPLE old = old_image[i][j];
            RGBTRIPLE neighbors[3][3];
            for(int l = 0; l < 3; l++)
            {
                for(int m = 0; m<3; m++)
                {
                    neighbors[l][m] = old_image[i+pos[l]][j+pos[m]];
                }
            }


            int gxr = 0;
            int gxg = 0;
            int gxb = 0;
            int gyr = 0;
            int gyg = 0;
            int gyb = 0;

            for(int l = 0; l < 3; l++)
            {
                for(int m = 0; m<3; m++)
                {
                    gxr = gxr + neighbors[l][m].rgbtRed*kernelx[l][m];
                    gxg = gxg + neighbors[l][m].rgbtGreen*kernelx[l][m];
                    gxb = gxb + neighbors[l][m].rgbtBlue*kernelx[l][m];

                    gyr = gyr + neighbors[l][m].rgbtRed*kernely[l][m];
                    gyg = gyg + neighbors[l][m].rgbtGreen*kernely[l][m];
                    gyb = gyb + neighbors[l][m].rgbtBlue*kernely[l][m];
                }
            }

            image[i][j].rgbtRed = ((int) sqrt( (gxr*gxr) + (gyr*gyr) )) % 255;
            image[i][j].rgbtGreen = ((int) sqrt( (gxg*gxg) + (gyg*gyg) )) % 255;
            image[i][j].rgbtBlue = ((int) sqrt( (gxb*gxb) + (gyb*gyb) )) % 255;







        }
    }


    return;

}
