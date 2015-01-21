// Includes
#include <iostream>
#include "piv.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char *argv[]){
	
	// Declare matrices for the first and second images.
	cv::Mat image_01;
	cv::Mat image_02;
	
	// Define the region edges
	const unsigned int grid_point_row = 600;
	const unsigned int grid_point_col = 590;
	
	// Define subregion dimensions
	const unsigned int sub_region_height = 128;
	const unsigned int sub_region_width  = 128;
	
	// Read the first image.
	image_01 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	// Read the second image
	image_02 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	// Declare matrices to hold the interrogation regions.
	cv::Mat sub_region_01(sub_region_height, sub_region_width, image_01.type());
	cv::Mat sub_region_02(sub_region_height, sub_region_width, image_02.type());
	
	// Extract the first subregion.
	piv::extract_subregion(image_01, sub_region_01, grid_point_row, grid_point_col, sub_region_height, sub_region_width);
	
	// Window the subregion
	/* This is just a prototype!
	piv::apodize_subregion(sub_region_01, sub_region_height, \\
		sub_region_width, effective_window_height, effective_window_width); */
	
	// Extract the second subregion
	// piv::extract_subregion(image_02, sub_region_02, grid_point_row, grid_point_col, sub_region_height, sub_region_width);
	
	// Calculate the standard deviation of a Gaussian function.
	double std_x = piv::find_gaussian_std((double)64, (double)32);
	
	// Write the output to screen
	std::cout << "Standard deviation: " << std_x << '\n';
	
	// Create a window for displaying the full image.
	cv::namedWindow("full_image");

	// Create a window for displaying the subregion.
	cv::namedWindow("sub_region");

	// Display the full image.
	cv::imshow("full_image", image_01);

	// Display the subregion.
	cv::imshow("sub_region", sub_region_01);

 	// Wait for a keystroke.
	cv::waitKey(0);
		
	// GTFO
	return(0);
	
}