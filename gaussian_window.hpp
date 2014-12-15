#include <iostream>
#include <stdlib.h>
#include <math.h>

// Define a namespace called piv. 
namespace piv{

	// This function approximates an area integral using the Trapezoidal rule.
	// The vector x must be increasing, but its values need not be evenly spaced.
	double trapz(double x[], double y[], const int num_elements){
		
		// Initialize the summed area as the first element in the y array
		float sum = 0;
		
		// Declare the step size
		double step_size = (x[num_elements - 1] - x[0]) / (num_elements - 1);
		
		// Declare the incremental area variable
		double d_area;
	
		// Loop over the elements
		for(int k = 1; k < num_elements; k++){
		
			// Differential area of a slice of the array
			// using the trapezoidal rule.
			d_area = (x[k] - x[k - 1]) * (y[k] + y[k - 1]) / 2.00; 
		
			// Add the differential area to the total area.
			sum += d_area;
		}
	
		// Return the calculated area.
		return sum;
	}

	// This function calculates the standard deviation of a Gaussian function
	// whose area approximates the area under a rectangular region of a given length
	// and a height of one.
	double find_gaussian_std(const int dimension_length_pixels, const double effective_window_length){
			
		// Initial guess of the standard deviation as half the effective window size.
		double std_dev = 50.00 * effective_window_length;
	
		// Calculate the center of the domain
		double domain_centroid = ((double) dimension_length_pixels - 1.00) / 2.00;
	
		// Declare the coordinate domain
		double x[dimension_length_pixels];
		
		// Declare gaussian
		double g[dimension_length_pixels];	
		
		// Populate the coordinate domain
		for(unsigned int k = 0; k < dimension_length_pixels; k++){
			x[k] = (double) k - domain_centroid;
			g[k] = exp(-1.00 * x[k] * x[k] / (2 * std_dev * std_dev) );
		}
	
		// Calculate the area under the Gaussian curve
		double gaussian_area = trapz(x, g, dimension_length_pixels);
	
		// Declare the error between the gaussian area and the
		// requested effective window length.
		double area_error;
	
		// Only proceed if the requested window size is smaller
		// than the initially calculated gaussian area.
		if(effective_window_length < gaussian_area){
	    
			// Calculate initial errors of Gaussian windows with respect to desired
		    // effective window resolution
			area_error = fabs(1.00 - gaussian_area) / effective_window_length;
		
			// Initialize the max and min values of the standard deviation
			// for the Gaussian window.
			double std_dev_max = 100.00 * (double)dimension_length_pixels;
			double std_dev_min = 0;
				
			// Iteratively determine the standard deviation that
			// gives the desired effective Gaussian resolution.
			while(area_error > 1E-5){
			
				if(gaussian_area < effective_window_length){
					// Increase the lower bound of the standard deviation
					std_dev_min = std_dev_min + (std_dev_max - std_dev_min) / 2;
				}
				else{
					// Increase the upper bound of the standard deviation.
					std_dev_max = std_dev_min + (std_dev_max - std_dev_min) / 2;
				}
			
				// Update the new standard deviation to lie halfway between the bounds.
				std_dev = std_dev_min + (std_dev_max - std_dev_min) / 2;
			
				// Now re-calculate the Gaussian function with the new standard deviation.
				// Populate the coordinate domain
				for(unsigned int k = 0; k < dimension_length_pixels; k++){
					g[k] = exp(-1.00 * x[k] * x[k] / (2 * std_dev * std_dev) );
				}
			
				// Re calculate the area under the Gaussian curve.
				gaussian_area = trapz(x, g, dimension_length_pixels);
			
				// Re-calculate the error under the Gaussian curve
				// compared to the desired area.
				area_error = fabs(1.00 - (double) gaussian_area / (double) effective_window_length);
			}
		}
	
		// Return the calculated standard deviation.
		return(std_dev);
	}

} // end namespace
