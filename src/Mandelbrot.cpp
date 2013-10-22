#include "Mandelbrot.h"

void Mandelbrot::gen_fractal()
{

	// Real (-2.5, 1)
	// Imaginary (-1, 1)
    
    // Iterate over each pixel and determine the corresponding complex coordinate (or several complex coordinates if you're anti-aliasing)
    
    int height = get_height(), width = get_width();
    int i, npixels = height*width;
    double dx = 3.0/width;
    double dy = 3.0/height;


    for (i = 0; i < npixels; i++)
    {
        int x = i%height;
        int y = i/height;
        
        // For each pixel, compute the corresponding complex coordinate C (or multiple sub-coordinates, for AA)

        int n_total = 0;

        for (int j = 0 ; j < 9 ; j++)
        {

            double c_r = (((double)x)/width)*3.0 - 2.25 + (dx / 3) * (j/3);
            double c_i = (((double)y)/height)*3.0 - 1.5 + (dy / 3) * (j%3);
            
            // let z_r and z_i be 0
            
            double z_r = 0;
            double z_i = 0;
            
            int n = 0;
            
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

            n_total += n;
        }

        
        // Color each pixel...
        // Constants arrived at abitrarily

        int n = n_total / 9;

        
        if (n < MAXITER) // if the point escaped to infinity
        {

            HsvColor colors;
            colors.h = (180*n - 110*(MAXITER - n))/MAXITER;
            colors.s = 170;
            colors.v = 15*n;

            RgbColor mycolors = HsvToRgb(colors);
            m_bitmap[x*m_height*4 + y*4 + 0] = mycolors.r; //3*n+10;    // R
            m_bitmap[x*m_height*4 + y*4 + 1] = mycolors.g; //0.5*n*n+5; // G
            m_bitmap[x*m_height*4 + y*4 + 2] = mycolors.b; //n*n+100; // B
            m_bitmap[x*m_height*4 + y*4 + 3] = 250;  // A
        }
        else //(n == MAXITER) // if the point remained in the set
        {
            m_bitmap[x*m_height*4 + y*4 + 0] = 0; //abs(z_i)*100;     // R
            m_bitmap[x*m_height*4 + y*4 + 1] = 0; //abs(z_r*z_i)*255; // G
            m_bitmap[x*m_height*4 + y*4 + 2] = 0; //abs(z_r)*50;     // B
            m_bitmap[x*m_height*4 + y*4 + 3] = 255;              // A
        }

    }

}


RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

