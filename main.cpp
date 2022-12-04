#include "newton.hpp"

using namespace std;

int main(void)
{
    //Newton newt({(-1. - 1i)/sqrt(2.), (1. + 1i)/sqrt(2.), 1.5 - 1.5i},4096,50);
    Newton newt(5,2048);
    dbl window[2][2] = {{-1.,1.},
                        {-1.,1.}};
    newt.generateFractal(window);
    //draw(newt,"masterclass.bmp");
    return 0;
}
