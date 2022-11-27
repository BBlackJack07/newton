#include "newton.hpp"
#include "bitmap_image.hpp"

void draw(const vector<Color> & matrix, unsigned int size, string path);

int main(void)
{
    //Newton newt({(-1. - 1i)/sqrt(2.), (1. + 1i)/sqrt(2.), 1.5 - 1.5i},4096,50);


    Newton newt(4);
    dbl window[2][2] = {{-1.,1.},
                        {-1.,1.}};
    vector<Color> fract(newt.generateFractal(window));
    
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
            image.set_pixel(x,size-1-y,data[x*size + y]);
        }
    }
    image.save_image(path);

}
