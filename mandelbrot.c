/* mandelbrot.c
This program produces an image of the Mandelbrot set */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_ITERATIONS 32 /* Will be 65535 in final version */
#define WIDTH 160         /* Image width in pixels */
#define HEIGHT 40         /* Image height in pixels */
#define XMIN -1
#define XMAX 1
#define YMIN -1.5
#define YMAX 1.5

/*  Escape time algorithm
    Carries out the iteration z_k+1 = (z_k)^2 + c
    u and v are Re(z_k) and Im(z_k) respectively
    x and y are Re(c) and Im(c) respectively */
int mandelbrot(double u, double v, double x, double y, int k)
{
    double z2_re = u * u - v * v; /* Calculate Re((z_k)^2) and Im((z_k)^2) */
    double z2_im = 2 * u * v;
    double fz_re = z2_re + x; /* Calculate Re(z_k+1) and Im(z_k+1) */
    double fz_im = z2_im + y;
    double mag = fz_re + fz_im; /* Magnitude squared of z_k+1 */
    int i = 0;

    while (mag <= 2)
    {
        u = z2_re;
        v = z2_im;
        z2_re = u * u - v * v;
        z2_im = 2 * u * v;
        fz_re = z2_re + x;
        fz_im = z2_im + y;
        mag = fz_re + fz_im;

        i++;
    }

    return i;
}

int main(int argc, char *argv[])
{
    //int i, j;

    return EXIT_SUCCESS;
}