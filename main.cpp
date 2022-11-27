#include <iostream>
#include "newton.hpp"
#include "bitmap_image.hpp"
#include <cmath>

void draw(const vector<Color> & matrix, unsigned int size, string path);

int main(void)
{
    Newton newt(5,4096,70);
    vector<Color> fract(newt.generateFractal());
    
    draw(fract,newt.size(),"masterclass.bmp");
    return 0;
}

void draw(const vector<Color> & data, unsigned int size, string path)
{
    bitmap_image image(size,size);
    for (unsigned int x {0}; x < size; x++)
    {
        for (unsigned int y {0}; y < size ; y++)
        {
            image.set_pixel(x,y,data[x*size + y]);
        }
    }
    image.save_image(path);

}
