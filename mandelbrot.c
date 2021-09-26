/* mandelbrot.c
This program produces an image of the Mandelbrot set */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_ITERATIONS 65535 /* Will be 65535 in final version */
#define WIDTH 160            /* Image width in pixels */
#define HEIGHT 40            /* Image height in pixels */
#define XMIN -2              /* Real axis boundaries */
#define XMAX 1
#define YMIN -1 /* Imaginary axis boundaries */
#define YMAX 1
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define BYTES_PER_PIXEL 4 /* 3 bytes for RGB, extra byte because number of pixels per row must be of form 2^n for faster processing */

/*  This function implements the escape time algorithm.
    Calculates the iteration z_k+1 = (z_k)^2 + c
    u and v are Re(z_k) and Im(z_k) respectively
    x and y are Re(c) and Im(c) respectively */
int mandelbrot(double u, double v, double x, double y)
{
    double z2_re;
    double z2_im;
    double fz_re;
    double fz_im;
    double mag = 0; /* Magnitude squared of z_k+1 */
    int i = 0;

    while (mag <= 4 && i < MAX_ITERATIONS)
    {
        z2_re = u * u - v * v; /* Calculate Re((z_k)^2) and Im((z_k)^2) */
        z2_im = 2 * u * v;
        fz_re = z2_re + x; /* Calculate Re(z_k+1) and Im(z_k+1) */
        fz_im = z2_im + y;
        mag = fz_re + fz_im;

        u = fz_re;
        v = fz_im;
        i++;
    }

    return i;
}

/* Generate BMP image of Mandelbrot Set.
   Creates an array of pixels. Each pixel has 3 integer values in range 0-255 
   corresponding to RED, GREEN and BLUE colour contributions. 
   N.B. Pitch/stride is not user specified in this implementation.
   Function then writes to file <name>.bmp */
void mandelbrotBitmap()
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (WIDTH * BYTES_PER_PIXEL * HEIGHT);
    unsigned char pixelArray[WIDTH][HEIGHT][BYTES_PER_PIXEL];
    char *mandelbrotBMP = (char *)"mandelbrot.bmp";
    FILE *bmpFile = fopen(mandelbrotBMP, "wb");

    /* Write bitmap file header */
    unsigned char fileHeader[] = {0, /* signature */
                                  0,
                                  0, /* size of BMP file in bytes */
                                  0,
                                  0,
                                  0,
                                  0, /* application dependent */
                                  0,
                                  0, /* application dependent */
                                  0,
                                  0, /* starting address of pixel array */
                                  0,
                                  0,
                                  0};

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    fwrite(fileHeader, 1, FILE_HEADER_SIZE, bmpFile);

    /* Write bitmap information header - using BITMAPINFOHEADER format */
    unsigned char infoHeader[] = {0, /* Header size in bytes */
                                  0,
                                  0,
                                  0,
                                  0, /* bitmap width in pixels */
                                  0,
                                  0,
                                  0,
                                  0, /* bitmap height in pixels */
                                  0,
                                  0,
                                  0,
                                  0, /* number of colour planes */
                                  0,
                                  0, /* number of bits per pixel i.e., colour depth */
                                  0,
                                  0, /* compression method used */
                                  0,
                                  0,
                                  0,
                                  0, /* image size */
                                  0,
                                  0,
                                  0,
                                  0, /* horizontal resolution */
                                  0,
                                  0,
                                  0,
                                  0, /* vertical resolution */
                                  0,
                                  0,
                                  0,
                                  0, /* number of colours in colour palette */
                                  0,
                                  0,
                                  0,
                                  0, /* number of important colours used */
                                  0,
                                  0,
                                  0};

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(WIDTH);
    infoHeader[5] = (unsigned char)(WIDTH >> 8);
    infoHeader[6] = (unsigned char)(WIDTH >> 16);
    infoHeader[7] = (unsigned char)(WIDTH >> 24);
    infoHeader[8] = (unsigned char)(HEIGHT);
    infoHeader[9] = (unsigned char)(HEIGHT >> 8);
    infoHeader[10] = (unsigned char)(HEIGHT >> 16);
    infoHeader[11] = (unsigned char)(HEIGHT >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

    fwrite(infoHeader, 1, INFO_HEADER_SIZE, bmpFile);

    /* Initialise pixel array. Monochromatic to begin with. */
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            pixelArray[i][j][0] = 0; /* Red */
            pixelArray[i][j][1] = 0; /* Green */
            pixelArray[i][j][2] = 0; /* Blue */
            pixelArray[i][j][3] = 0; /* More */
        }
        /* Write the pixel array to .bmp file line by line. 
        (j * WIDTH * BYTES_PER_PIXEL) = 1 line in bytes */
        fwrite(pixelArray + (j * WIDTH * BYTES_PER_PIXEL), BYTES_PER_PIXEL, WIDTH, bmpFile);
    }

    /* [optional] Write ICC colour profile */
}

int main(int argc, char *argv[])
{
    double i, j;
    for (j = YMIN; j <= YMAX; j += 0.0125)
    {
        for (i = XMIN; i <= XMAX; i += 0.0125)
        {
            if (mandelbrot(0, 0, i, j) == MAX_ITERATIONS)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}