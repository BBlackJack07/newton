#include "newton.hpp"

void Color::setColor(unsigned char c, colors color)
{
    switch (color) {
        case BLUE:
            this->blue=c;
            break;
        case CYAN:
            this->blue=c;
            this->green=c;
            break;
        case GREY:
            this->red=c;
            this->blue=c;
            this->green=c;
            break;
        case MAGENTA:
            this->red=c;
            this->blue=c;
            break;
        case PURPLE:
            this->red = c/2;
            this->blue = c;
            break;
        case GREENISH:
            this->green=c;
            this->blue=c/4;
            break;
        default:
            this->red=c;
    }
}

Newton::Newton(const vector<comp> & roots_list, unsigned int size, unsigned int max_iteration, dbl eps)
    :roots(roots_list), SIZE(size), N(max_iteration), EPS(eps), SIZE_D(static_cast<dbl>(size)), fractal(size*size)
{
    //bright_exponent = 1./static_cast<dbl>(roots.size()/2+1);
    bright_exponent = 1. / 2.;
    p = Newton::polyFromRoots(roots);
    d = Newton::derive(p);
}

Newton::Newton(int n, unsigned int size, unsigned int max_iteration, dbl eps)
    :roots(Newton::nth_roots(n)), SIZE(size), N(max_iteration), EPS(eps), SIZE_D(static_cast<dbl>(size)), fractal(size*size)
{
    //bright_exponent = 1./static_cast<dbl>(roots.size()/2+1);
    bright_exponent = 1. / 2.;
    p = Newton::polyFromRoots(roots);
    d = Newton::derive(p);
}

vector<comp> Newton::polyFromRoots(const vector<comp> & roots)
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

comp Newton::horner(const vector<comp> & p, const comp & z)
{
    comp s = p[0];
    for (unsigned int i {1}; i < p.size(); i++)
    {
        s *= z;
        s += p[i];
    }
    return s;
}

vector<comp> Newton::derive(const vector<comp> & p)
{
    unsigned int n = p.size() - 1;
    vector<comp> d(n);
    for (unsigned int i {0}; i < n; i++)
        d[i] = static_cast<comp>(n-i) * p[i];
    return d;
}

dbl Newton::dist(const comp& z)
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

unsigned int Newton::min_dist_index(const comp& z)
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

comp Newton::getcomp(unsigned int x, unsigned int y, const dbl window[2][2])
{
    dbl re { window[0][0] + (window[0][1] - window[0][0] ) * static_cast<dbl>(x)/SIZE_D };
    dbl im { window[1][0] + (window[1][1] - window[1][0] ) * static_cast<dbl>(y)/SIZE_D };
    return re + 1i * im;
}

unsigned int Newton::size()
{
    return SIZE;
}

vector<comp> Newton::nth_roots(int n)
{
    vector<comp> roots;
    for (int k {0}; k < n; k++)
    {
        roots.push_back( exp( 2. * M_PI * static_cast<dbl>(k)/static_cast<dbl>(n) * 1i )  );
    }
    return roots;
}

void Newton::compute_fractal(const dbl window[2][2], unsigned int x0, unsigned int xf)
{
    dbl eps2 = EPS*EPS;
    for (unsigned int x {x0}; x < xf; x++ )
    {
        auto row {x * SIZE};
        for (unsigned int y {0}; y < SIZE; y++)
        {
            // Computation
            comp z = getcomp(x,y,window);
            unsigned int k {0};
            while (k++<N && dist(z)>eps2)
                z -= horner(p,z)/horner(d,z);
            // Determine color
            unsigned char c { static_cast<unsigned char>(400./pow(static_cast<dbl>(k+1), bright_exponent)) };
            auto i { min_dist_index(z) % roots.size() };
            auto index {row + y};
            switch (i) {
                case 0:
                    fractal[index].setColor(c,BLUE);
                    break;
                case 1:
                    fractal[index].setColor(c,CYAN);
                    break;
                case 2:
                    fractal[index].setColor(c,GREY);
                    break;
                case 3:
                    fractal[index].setColor(c,MAGENTA);
                    break;
                case 4:
                    fractal[index].setColor(c,PURPLE);
                    break;
                case 5:
                    fractal[index].setColor(c,GREENISH);
                    break;
                default:
                    fractal[index].setColor(c,DEFAULT);
            }
        }
    }
}

void Newton::generateFractal(const dbl window[2][2])
{
    const auto processor_count = std::thread::hardware_concurrency();
    if (SIZE>=2048 && processor_count >= 2) {
        thread t1(&Newton::compute_fractal,this,window,0,SIZE/2);
        compute_fractal(window, SIZE/2, SIZE);
        t1.join();
    }
    else {
        compute_fractal(window, 0, SIZE);
    }
}

void draw(std::string path)
{
    bitmap_image image(SIZE,SIZE);
    for (unsigned int x {0}; x < SIZE; x++)
    {
        auto row { x * SIZE };
        for (unsigned int y {0}; y < SIZE; y++)
        {
            image.set_pixel(x,SIZE-1-y,fractal[row + y]);
        }
    }
    image.save_image(path);
}
