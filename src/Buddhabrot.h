#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Fractal.h"

class Buddhabrot : public Fractal
{
	public:
	Buddhabrot(int height, int width):Fractal(height, width) {}	
    Buddhabrot(double x):Fractal(x) {}
	void gen_fractal();
    int calculate_bucket(double, double);
};

