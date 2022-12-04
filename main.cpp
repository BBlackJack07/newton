#include <iostream>
#include "newton.hpp"

using namespace std;

void showMenu(int n);

int main(void)
{
    //Newton newt({(-1. - 1i)/sqrt(2.), (1. + 1i)/sqrt(2.), 1.5 - 1.5i},4096,50);
    dbl window[2][2] = {{-2.,2.},
                        {-2.,2.}};
    vector<comp> roots;
    unsigned int size {0};
    showMenu(0);
    int answer {1};
    cin >> answer;
    if (answer == 1) {
        showMenu(1);
        int nb_roots {0};
        cin >> nb_roots;
        for (auto i = 0; i < nb_roots; i++)
        {
            showMenu(3);
            dbl re {0.}, im {0.};
            cout << "Reel part? ";
            cin >> re;
            cout << "Imaginary part? ";
            cin >> im;
            roots.push_back(re+im*1i);
        }
    }
    else 
    {
        showMenu(2);
        int n {0};
        cin >> n;
        roots = Newton::nth_roots(n);
    }

    showMenu(4);
    char answer2 {'\0'};
    cin >> answer2;
    if (answer2 == 'y')
    {
        cout << "X-axis min? ";
        cin >> window[0][0];
        cout << "X-axis max? ";
        cin >> window[0][1];
        cout << "Y-axis min? ";
        cin >> window[1][0];
        cout << "Y-axis max? ";
        cin >> window[1][1];
        cout << endl;
    }
    showMenu(5);
    cin >> size;
    if (size == 0) size = DEF_SIZE;
    if (roots.size() > 0) {
        Newton newt(roots,size);
        newt.generateFractal(window);
        newt.draw("masterclass.bmp");
    }
    return 0;
}

void showMenu(int n)
{
    switch (n) {
        case 0:
            cout << "   ############################" << endl;
            cout << "   # Newton Fractal generator #" << endl;
            cout << "   ############################" << endl;
            cout << "What do you want ? (1 or 2)" << endl;
            cout << "  1/ Manually enter fractal roots." << endl << "  2/ Use n-th roots." << endl;
            break;
        case 1:
            cout << "Chose number of roots: " << endl;
            break;
        case 2:
            cout << "Enter n value: " << endl;
            break;
        case 3:
            cout << "Enter root value (format: re + im * 1i)" << endl;
            break;
        case 4:
            cout << "Do you want to manually enter window (else uses default [-2,2]x[-2,2])? (y/n)" << endl;
            break;
        case 5:
            cout << "Enter image size (if 0 uses default 2048x2048) ?" << endl;
            break;

    }
    cout.flush();
}
