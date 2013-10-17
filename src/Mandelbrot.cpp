#include "Mandelbrot.h"

void Mandelbrot::gen_fractal()
{
	// Real (-2.5, 1)
	// Imaginary (-1, 1)
    
    // Iterate over each pixel and determine the corresponding complex coordinate (or several complex coordinates if you're anti-aliasing)
    
    int height = get_height(), width = get_width();
    int i, npixels = height*width;
    for (i = 0; i < npixels; i++)
    {
        int x = i%height;
        int y = i/height;
        
        // For each pixel, compute the corresponding complex coordinate C (or multiple sub-coordinates, for AA)
        
        double c_r = (((double)x)/width)*3.0 - 2.25;
        double c_i = (((double)y)/height)*3.0 - 1.5;
        
        // let z_r and z_i be 0
        
        double z_r = 0;
        double z_i = 0;
        
        int n = 1;
        
        // Begin iterating... while z is not infinity and not too many iterations have passed...
        
        while ((pow(z_r, 2) + pow(z_i, 2)) < 4 && n < MAXITER)
        {
            // Z = Z^2 + C
            
            double z_temp;
            z_temp = pow(z_r, 2) - pow(z_i, 2) + c_r;
            z_i = z_r * z_i * 2 + c_i;
            z_r = z_temp;
            
            // increment an iteration counter
            
            n++;
            
        }
        
        // Color each pixel...
        
        if (n < MAXITER) // if the point escaped to infinity
        {
            m_bitmap[x*m_height*4 + y*4 + 0] = 0; // R
            m_bitmap[x*m_height*4 + y*4 + 1] = 0; // G
            m_bitmap[x*m_height*4 + y*4 + 2] = 0; // B
            m_bitmap[x*m_height*4 + y*4 + 3] = 255; // A
        }

        else if (n == MAXITER) // if the point remained in the set
        {
            m_bitmap[x*m_height*4 + y*4 + 0] = z_r*255; // R
            m_bitmap[x*m_height*4 + y*4 + 1] = z_i*255; // G
            m_bitmap[x*m_height*4 + y*4 + 2] = 255; // B
            m_bitmap[x*m_height*4 + y*4 + 3] = 255; // A
        }

    }

    cout << m_bitmap << endl;

}
