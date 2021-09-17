/* mandelbrot.c
This program produces an image of the Mandelbrot set */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_ITERATIONS 65535 /* Will be 65535 in final version */
#define WIDTH 160            /* Image width in pixels */
#define HEIGHT 40            /* Image height in pixels */
#define XMIN -2
#define XMAX 1
#define YMIN -1
#define YMAX 1

/*  This function is implements the escape time algorithm.
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

void mandelbrotBitmap()
{
    /* Generate BMP image of Mandelbrot Set */
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