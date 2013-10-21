#include "Buddhabrot.h"

void Buddhabrot::gen_fractal()
{

    srand(time(NULL));

	// Real (-2.5, 1)
	// Imaginary (-1, 1)
    
    int height = get_height(), width = get_width();
    int i, npixels = height*width;
 
    // Initialize a bucket array (one integer for each pixel) (this is the outer bucket array)
    // iterate over the following several thousand times (at least more times than # of pixels)

    // initialize bucket
    int *bucket = new int[width*height];

    // stores the points in main bucket to be incremented
    int *tmp_bucket = new int[MAXITER];

    for (i = 0; i < npixels; i++)
    {
        int x = i%height;
        int y = i/height;
        
        // For each pixel, compute the corresponding complex coordinate C (or multiple sub-coordinates, for AA)
        
        double point_r = (((double)x)/width)*3.0 - 2.25;
        double point_i = (((double)y)/height)*3.0 - 1.5;
        double dr = 3.0 / width;
        double di = 3.0 / width;
      
        // cycle through some random subpoints 
        for (int j = 0 ; j < 10 ; j++)
        {

            double c_r = point_r + dr * (rand() % 1000 / 1000.0);
            double c_i = point_i + di * (rand() % 1000 / 1000.0);
             
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

                // find the pixel which the orbital point corresponds to, and increment its counter
                x = width * (z_r + 2.25) / 3.0;
                y = height * (z_i + 1.5) / 3.0;
                tmp_bucket[n] = y*height + x;
               
                // increment an iteration counter
                
                n++;
                
            } 

            // if the point escaped, merge changes in tmp_bucket
            if ( n < MAXITER )
                for (int j = 0 ; j < n ; j++)
                    if ( tmp_bucket[j] >= 0 && tmp_bucket[j] < height*width )
                        bucket[tmp_bucket[j]] += 1;
 
        } // exiting curent point
        
     } 

     // Normalize the global bucket array by dividing each value by the maximum value

     int max = 0;
     for (int i = 0 ; i < npixels ; i++) 
        if ( max < bucket[i] )
            max = bucket[i];


     for (int i = 0 ; i < npixels ; i++) 
     {
        int x = i%height;
        int y = i/height;

        m_bitmap[x*m_height*4 + y*4 + 0] = 0;    // R
        m_bitmap[x*m_height*4 + y*4 + 1] = 200*bucket[i]/max; //3000*(pow(real_bucket[i],2) + pow(imaginary_bucket[i],2)); // G
        m_bitmap[x*m_height*4 + y*4 + 2] = 250*bucket[i]/max; // B
        m_bitmap[x*m_height*4 + y*4 + 3] = 250;  // A

     }

 
}
