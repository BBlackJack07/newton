#include <iostream>
#include "newton.hpp"
#include "bitmap_image.hpp"

int main(void)
{
    bitmap_image image(SIZE,SIZE);
    //comp j = -0.5 + 1i*(sqrt(3.)/2.);
    vector<comp> roots({ 1i, -1i, -1., 1. });
    //vector<comp> roots({ j, pow(j,2), 1 });
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
