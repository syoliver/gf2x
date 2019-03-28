#include "gf2x.h"
#include "gf2x/gf2x-small.h"
#include "gf2x/gf2x-fft.h"

int main()
{
    unsigned long a[5], b[5], c[10];
    gf2x_mul5(c, a, b);

}
