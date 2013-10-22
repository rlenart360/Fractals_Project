#include <cmath>
#include <cstdlib>
#include "Fractal.h"

class Mandelbrot : public Fractal
{
	public:
	Mandelbrot(int height, int width):Fractal(height, width) {}
    Mandelbrot(double x):Fractal(x) {}
	void gen_fractal();
};

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv);
