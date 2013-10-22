#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Mandelbrot.h"
#include "Buddhabrot.h"
using namespace std;

int main(int argc, char *argv[])
{
    // Seed the random number generator
	srand(time(0));
   
    // Read command line input (if you're on windows, you might want to replace this with some I/O code)
    char *str; 
    str = (char *) malloc(sizeof(char) * 11);
    strcpy(str, "output.png");

    Fractal *my_fractal;

    if (argc == 2)
    {
        string type = argv[1];

        if (type.at(0) == 'b')
            my_fractal = new Buddhabrot(3000, 3000);
        
        else if (type.at(0) == 'm')
            my_fractal = new Mandelbrot(3000, 3000);
    }

    else
    {
        cout << "Usage is ./fractalgen type [buddhabrot or mandelbrot]" << endl;
        return 1;
    }


    // Create a fractal object
	cout << "Fractal Allocated" << endl;

    // Generate the fractal
    my_fractal->gen_fractal();
    cout << "Fractal Created" << endl;
    
    // Save the fractal to a file
	my_fractal->save_file(str);
    cout << "Fractal Saved to file" << endl;
    
    if (argc < 3)
    {
        free(str);
    }
	
    return 0;
}
