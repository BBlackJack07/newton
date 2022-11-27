#ifndef NEWTON_HPP
#define NEWTON_HPP

#include <vector>
#include <complex>

using namespace std;

typedef long double dbl;
typedef complex<dbl> comp;

struct Color {
    public:
        Color() :red(0),green(0),blue(0) {}
        unsigned char red,green,blue;    
};

constexpr unsigned int SIZE {8192};
constexpr dbl SIZE_D { static_cast<dbl>(SIZE) };
constexpr unsigned int N {70};
constexpr dbl EPS {1e-10};

vector<comp> polyFromRoots(const vector<comp> & roots);
comp horner(const vector<comp> & p, const comp & z);
vector<comp> derive(const vector<comp> & p);

dbl dist(const comp & z, const vector<comp> & roots);

vector<Color> newton(const vector<comp> & roots);

#endif
