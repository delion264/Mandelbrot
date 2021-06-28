/* mandelbrot.c
This program produces an image of the Mandelbrot set */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAX_ITERATIONS 128 /* Will be 65535 in final version */

int main(int argc, char *argv[])
{

    double x, y; /* Complex coordinates of z_0 */
    double u, v; /* Complex coordinates of z_k */
    int k;       /* Iteration counter */

    for (k = 0; k < MAX_ITERATIONS; k++)
    {
        double z2_re = u * u - v * v;
        double z2_im = 2 * u * v;
        double mag = sqrt(pow(z2_re, 2) + pow(z2_im, 2));

        u = z2_re;
        v = z2_im;
    }

    if (mag < 2)
    {
        printf("*");
    }
}