#include "newton.hpp"

vector<comp> polyFromRoots(const vector<comp> & roots)
{
    auto n = roots.size(); 
    vector<comp> p(n+1,0.);
    p[0] = 1.;
    for (unsigned int i {0}; i < n; i++)
    {
        for (unsigned int k {i+1}; k > 0; k--)
        {
            p[k] = - roots[i]*p[k-1] + p[k];
        }
    }
    return p;
}

comp horner(const vector<comp> & p, const comp & z)
{
    comp s = p[0];
    for (unsigned int i {1}; i < p.size(); i++)
    {
        s *= z;
        s += p[i];
    }
    return s;
}

vector<comp> derive(const vector<comp> & p)
{
    unsigned int n = p.size() - 1;
    vector<comp> d(n);
    for (unsigned int i {0}; i < n; i++)
        d[i] = static_cast<comp>(n-i) * p[i];
    return d;
}

dbl dist(const comp& z, const vector<comp>& roots)
{
    dbl m { norm(z-roots[0]) };
    for (unsigned int i {1}; i < roots.size(); i++)
    {
        dbl d {norm(z-roots[i])};
        if (m>d)
            m = d;
    }
    return m;
}

unsigned int min_dist_index(const comp& z, const vector<comp>& roots)
{
    dbl m { norm(z-roots[0]) };
    unsigned int m_index {0};
    for (unsigned int i {1}; i < roots.size(); i++)
    {
        dbl d {norm(z-roots[i])};
        if (m>d) {
            m = d;
            m_index = i;
        }
    }
    return m_index;
}

comp getcomp(unsigned int x, unsigned int y)
{
    dbl re { (static_cast<dbl>(x) - SIZE_D / 2.)*4./SIZE_D };
    dbl im { (static_cast<dbl>(y) - SIZE_D / 2.)*4./SIZE_D };
    return re + 1il * im;
}

vector<Color> newton(const vector<comp> & roots)
{
    vector<Color> fractal(SIZE*SIZE);
    vector<comp> p(polyFromRoots(roots));
    vector<comp> d(derive(p));
    dbl eps2 = EPS*EPS;
    for (unsigned int x {0}; x < SIZE; x++ )
    {
        for (unsigned int y {0}; y < SIZE; y++)
        {
            // Computation
            comp z = getcomp(x,y);
            unsigned int k {0};
            while (k++<N && dist(z,roots)>eps2)
                z -= horner(p,z)/horner(d,z);
            // Determine color
            unsigned char c { static_cast<unsigned char>(255./pow(static_cast<dbl>(k+1),1./3.)) };
            auto i { min_dist_index(z,roots) % roots.size() };
            switch (i) {
                case 0:
                    fractal[x*SIZE + y].red = c;
                    break;
                case 1:
                    fractal[x*SIZE + y].green = c;
                    break;
                case 2:
                    fractal[x*SIZE + y].blue = c;
                    break;
                case 3:
                    fractal[x*SIZE + y].blue = c;
                    fractal[x*SIZE + y].red = c;
                    break;
                default:
                    fractal[x*SIZE + y].green = c;
                    fractal[x*SIZE + y].red = c;
            }
            
        }
    }
    return fractal;
}

