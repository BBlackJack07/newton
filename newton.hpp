/*
 *****************************************************************************
 *                                                                           *
 *                    Newton Fractal Generator                               *
 *                                                                           *
 * Author: Bastien Brunel - 2022                                             *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Newton Fractal Generator                                  *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * https://www.opensource.org/licenses/MIT                                   *
 *                                                                           *
 *****************************************************************************
*/

#ifndef NEWTON_HPP
#define NEWTON_HPP

#include <vector>
#include <complex>
#include <thread>
#include "bitmap_image.hpp"

using namespace std;

typedef double dbl;
typedef complex<dbl> comp;

enum colors {BLUE,CYAN,GREY,PURPLE,GREENISH,MAGENTA,DEFAULT};

constexpr unsigned int DEF_SIZE { 2048 };
constexpr unsigned int DEF_MAX_IT { 50 };
constexpr dbl DEF_WINDOW[2][2] = {{-2,2},{-2,2}};
constexpr dbl DEF_EPS {1e-8};


struct Color {
    public:
        Color() :red(0),green(0),blue(0) {}
        void setColor(unsigned char c, colors color);
        unsigned char red,green,blue;    
};

class Newton
{

    public:
        Newton(const vector<comp> & roots, unsigned int size = DEF_SIZE, unsigned int max_iteration = DEF_MAX_IT, dbl eps = DEF_EPS);
        Newton(int n, unsigned int size = DEF_SIZE, unsigned int max_iteration = DEF_MAX_IT, dbl eps = DEF_EPS);
        dbl dist(const comp & z);
        unsigned int min_dist_index(const comp& z);
        comp getcomp(unsigned int x, unsigned int y, const dbl window[2][2]);
        void generateFractal(const dbl window[2][2] = DEF_WINDOW);
        void compute_fractal(const dbl window[2][2], unsigned int , unsigned int);
        static vector<comp> polyFromRoots(const vector<comp> & roots);
        static vector<comp> nth_roots(int n);
        static vector<comp> derive(const vector<comp> & p);
        static comp horner(const vector<comp> & p, const comp & z); 
        unsigned int size();
        void draw(string path);

    private:
        const unsigned int SIZE;
        const dbl SIZE_D;
        const unsigned int N;
        const dbl EPS;
        dbl bright_exponent;
        vector<comp> roots,p,d;
        vector<Color> fractal;
};




#endif
