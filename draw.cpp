#include "draw.hpp"

void draw(const std::vector<Color> & data, unsigned int size, std::string path)
{
    bitmap_image image(size,size);
    for (unsigned int x {0}; x < size; x++)
    {
        unsigned int row { x * size };
        for (unsigned int y {0}; y < size ; y++)
        {
            image.set_pixel(x,size-1-y,data[row + y]);
        }
    }
    image.save_image(path);
}
