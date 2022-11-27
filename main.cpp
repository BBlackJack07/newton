#include <iostream>
#include "newton.hpp"
#include "bitmap_image.hpp"
#include <cmath>

int main(void)
{
    bitmap_image image(SIZE,SIZE);
    int n {3};
    vector<comp> roots;
    for (int k {0}; k < n; k++)
    {
        roots.push_back( exp( 2.l * M_PI * static_cast<dbl>(k)/static_cast<dbl>(n) * 1il )  );
    }
    vector<Color> fract(newton(roots));
    for (unsigned int x {0}; x < SIZE; x++)
    {
        for (unsigned int y {0}; y < SIZE; y++)
        {
            image.set_pixel(x,y,fract[x*SIZE + y]);
        }
    }
    image.save_image("masterclass.bmp");
    return 0;
}
