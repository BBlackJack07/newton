#include "newton.hpp"
#include "draw.hpp"

using namespace std;

int main(void)
{
    //Newton newt({(-1. - 1i)/sqrt(2.), (1. + 1i)/sqrt(2.), 1.5 - 1.5i},4096,50);
    Newton newt(5,4096);
    dbl window[2][2] = {{-1.,1.},
                        {-1.,1.}};
    vector<Color> fract(newt.generateFractal(window));
    draw(fract,newt.size(),"masterclass.bmp");
    return 0;
}
