#include <iostream>
#include <fstream>
#include "newton.hpp"

int main(void)
{
    ofstream file("newt.txt");
    comp j = -0.5 + 1i*(sqrt(3.)/2.);
    vector<comp> roots({ 1i, -1i, -1., 1. });
    //vector<comp> roots({ j, pow(j,2), 1 });
    vector<Color> fract(newton(roots));
    file << SIZE << endl;
    for (auto it = fract.begin(); it != fract.end(); it++)
    {
        file << (unsigned int)(it->red) << "," << (unsigned int)(it->green) << "," << (unsigned int)(it->blue) << endl;
    }
    file.close();
    return 0;
}
