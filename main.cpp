// Includes
#include <iostream>
#include "piv.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char *argv[]){
	
	// Declare matrices for the first and second images.
	cv::Mat image_01;
	cv::Mat image_02;
	
	// Define the region edges
	const int grid_point_row = 400;
	const int grid_point_col = 590;
	
	// Define subregion dimensions
	const int sub_region_height = 128;
	const int sub_region_width  = 128;
	
	// Define subregion effective resolution
	const int sub_region_effective_rows = 64;
	const int sub_region_effective_cols = 64;
	
	// Read the first image.
	image_01 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	// Read the second image
	image_02 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	// Convert the images to doubles
	image_01.convertTo(image_01, CV_64FC1);
	image_02.convertTo(image_02, CV_64FC1);
	
	// Declare matrices to hold the interrogation regions.
	cv::Mat sub_region_01(sub_region_height, sub_region_width, image_01.type());
	cv::Mat sub_region_02(sub_region_height, sub_region_width, image_02.type());
	
	// Extract the first subregion.
	piv::extract_subregion(image_01, sub_region_01, grid_point_row, grid_point_col, sub_region_height, sub_region_width);
	
	// Allocate matrix for the Gaussian window.
	cv::Mat gaussian_window(sub_region_height, sub_region_width, sub_region_01.type());
	
	// Create the Gaussian filter
	piv::make_gaussian_filter_2D(gaussian_window, sub_region_effective_rows, sub_region_effective_cols);
	
	// Convert the subregion to the correct type
	sub_region_01.convertTo(sub_region_01, gaussian_window.type());
	
	// Filter the subregion
	cv::Mat filtered_region(sub_region_height, sub_region_width, sub_region_01.type());	
	
	// Multiply the filter by the subregion
	filtered_region = sub_region_01.mul(gaussian_window);
	
	// Convert to 8 bit integer for displaying
	filtered_region.convertTo(filtered_region, CV_8UC1);
	
	// Create a display window and display the windowed subregion.
	cv::namedWindow("Filtered");
	cv::imshow("Filtered", filtered_region);
	
 	// Wait for a keystroke.
	cv::waitKey(0);
	
	// Destroy the window!
	cv::destroyWindow("Gaussian filter");
		
	// GTFO
	return(0);
	
}