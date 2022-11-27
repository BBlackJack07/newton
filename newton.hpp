#ifndef NEWTON_HPP
#define NEWTON_HPP

#include <vector>
#include <complex>

using namespace std;

typedef double dbl;
typedef complex<dbl> comp;

enum colors {BLUE,CYAN,GREY,PURPLE,GREENISH,MAGENTA,DEFAULT};

struct Color {
    public:
        Color() :red(0),green(0),blue(0) {}
        void setColor(unsigned char c, colors color);
        unsigned char red,green,blue;    
};

class Newton
{

    public:
        Newton(const vector<comp> & roots);
        Newton(const vector<comp> & roots, unsigned int size, unsigned int max_iteration);
        Newton(int n, unsigned int size, unsigned int max_iteration);
        dbl dist(const comp & z);
        unsigned int min_dist_index(const comp& z);
        comp getcomp(unsigned int x, unsigned int y);
        vector<Color> generateFractal();
        vector<comp> polyFromRoots();
        static vector<comp> nth_roots(int n);
        static vector<comp> derive(const vector<comp> & p);
        static comp horner(const vector<comp> & p, const comp & z); 
        unsigned int size();

    private:
        unsigned int SIZE;
        dbl SIZE_D;
        unsigned int N;
        dbl EPS;
        vector<comp> roots;
};




#endif
