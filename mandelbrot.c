/* mandelbrot.c
This program produces an image of the Mandelbrot set */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_ITERATIONS 128 /* Will be 65535 in final version */
#define WIDTH 600          /* Image width in pixels */
#define HEIGHT 400         /* Image height in pixels */
#define XMIN -1
#define XMAX 1
#define YMIN -1.5
#define YMAX 1.5

int main(int argc, char *argv[])
{
    int i, j;    /* Iterate over pixels */
    double a, b; /* Complex coordinates that correspond to pixel divisions */
    double xInterval = (XMAX - XMIN) / WIDTH;
    double yInterval = (YMAX - YMIN) / HEIGHT;

    for (i = 0; i < WIDTH / xInterval; i++)
    {
        for (j = 0; j < HEIGHT / yInterval; j++)
        {
            int s = mandelbrot(XMIN + i * xInterval, YMIN + j * yInterval);
            if (s = MAX_ITERATIONS)
            {
                printf("*");
            }
        }
    }

    return EXIT_SUCCESS;
}

/* Escape time algorithm */
int mandelbrot(double x, double y)
{
    double u = x; /* Complex coordinates of z_k */
    double v = y;
    double z2_re;
    double z2_im;
    double mag = 0; /* Magnitude of vector in complex space */
    int k = 0;      /* Iteration counter */

    while (k < MAX_ITERATIONS && mag < 2)
    {
        z2_re = u * u - v * v;
        z2_im = 2 * u * v;
        mag = sqrt(pow(z2_re, 2) + pow(z2_im, 2));

        if (z2_re == x && z2_im == y)
        {
            break;
        }
        u = z2_re;
        v = z2_im;
        k++;
    }
    return k;
}