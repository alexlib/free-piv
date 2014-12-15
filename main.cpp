// Includes
#include <iostream>
#include "piv.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char *argv[]){
	
	// Initialize an image.
	cv::Mat image_01;
	
	// Define the region edges
	const unsigned int sub_region_row = 600;
	const unsigned int sub_region_col = 590;
	
	// Define subregion dimensions
	const unsigned int sub_region_height = 128;
	const unsigned int sub_region_width  = 128;
	
	// Read the image.
	image_01 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	// Declare the subregion matrices.
	cv::Mat sub_region_01(sub_region_height, sub_region_width, image_01.type());
	
	// Extract the first subregion.
	extract_subregion(image_01, sub_region_01, sub_region_row, sub_region_col, sub_region_height, sub_region_width);
	
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