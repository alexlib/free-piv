#include <iostream>
#include <math.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "gaussian_window.hpp"
#include "fftw3.h"

// Define a namespace called piv.
namespace piv{

	/* This function extracts a subregion from an image. If the height or width of the interrogation are determined to lie outside
	of the original image, then the interrogation region is padded with zeros where it extends beyond the image.
	
	SYNTAX: void extract_subregion(cv::Mat input_mat, cv::Mat output_mat, int grid_point_row, int grid_point_col, int 		sub_region_height, int sub_region_width)

	INPUTS:
		cv::Mat input_mat : Input image from which the interrogation region will be extracted. Can be color or grayscale.

		cv::Mat output_mat : This is the output matrix to which the interrogation region will be assigned.
							This matrix should be of the same type as the variable input_mat.

		int grid_point_row : This is the row position within the input image of the center of the interrogation region.

		int grid_point_col : This is the column position within the input image of the center of the interrogation region.

		int sub_region_height : This is the number of rows (i.e. the height in pixels) of the interrogation region.

		int sub_region_width : This is the number of columns (i.e. the width in pixels) of the interrogation region.

	OUTPUTS: 
		None (void) */
	
	void extract_subregion(cv::Mat input_mat, cv::Mat output_mat, int grid_point_row, int grid_point_col, int sub_region_height, int sub_region_width){
			
		// Measure the size of the input image
		int image_rows = input_mat.rows;
		int image_cols = input_mat.cols;
	
		// Force the grid point to lie within the image.
		// This if-statement forces the specified row of the grid point 
		// to lie within the image.
		if(grid_point_row < 0){
			grid_point_row = 0;
		}
		else if(grid_point_row > image_rows){
			grid_point_row = image_rows;
		}
	
		// This if-statement forces the specified column of the grid point 
		// to lie within the image.
		if(grid_point_col < 0){
			grid_point_col = 0;
		}
		else if(grid_point_col > image_cols){
			grid_point_col = image_cols;
		}
			
		// Create a rectangle structure.
		cv::Rect sub_region_props;
		
		// Determine the left-most column of the subregion
		// within the larger image.
		int left_edge = grid_point_col - ceil(sub_region_width / 2) + 1;
	
		// Determine the top-most row of the subregion
		// within the larger image.
		int top_edge  = grid_point_row - ceil(sub_region_height / 2) + 1;
	
		// Determine the right-most column of the subregion
		// within the larger image
		int right_edge = left_edge + sub_region_width;
	
		// Determine the bottom-most row of the subregion
		// within the larger image
		int bottom_edge = top_edge + sub_region_height;
			
		// This condition checks whether the left edge
		// of the subregion extends beyond the left edge
		// of the image.	 
		if(left_edge < 0){
			sub_region_props.x = 0;
			sub_region_props.width = sub_region_width + left_edge;
		}
		// This condition checks whether the right edge
		// of the subregion extends beyond the right edge
		// of the image.
		else if(right_edge > image_cols){
			sub_region_props.x = left_edge;
			sub_region_props.width = sub_region_width - (right_edge - image_cols);
		}
		// If neither of the above conditions is true, then
		// the columns of the subregion lie entirely within the
		// original image.
		else{
			sub_region_props.x = left_edge;
			sub_region_props.width = sub_region_width;
		}
	
		// This condition checks whether the top edge
		// of the subregion extends beyond the top edge
		// of the image.
		if(top_edge < 0){
			sub_region_props.y = 0;	
			sub_region_props.height = sub_region_height + top_edge;
		}
		// This condition checks whether the bottom edge
		// of the subregion extends beyond the bottom edge
		// of the image.
		else if(bottom_edge > image_rows){
			sub_region_props.y = top_edge;
			sub_region_props.height = sub_region_height - (bottom_edge - image_rows);
		}
		// If neither of the above conditions is true, then
		// the rows of the subregion lie entirely within the
		// original image.
		else{
			sub_region_props.y = top_edge;
			sub_region_props.height = sub_region_height;
		}
	
		// Create a matrix to hold the un-padded subregion.
		cv::Mat sub_region_temp = input_mat(sub_region_props);
	
		// Determine the number of columns with which to pad the
		// left side of the subregion.
		int pad_size_left   = -1 * std::min(0, left_edge);
	
		// Determine the number of columns with which to pad the
		// right side of the subregion.
		int pad_size_right  = -1 * std::min(0, image_cols - right_edge);
	
		// Determine the number of rows with which to pad the
		// top of the subregion.
		int pad_size_top    = -1 * std::min(0, top_edge);
	
		// Determine the number of rows with which to pad the
		// bottom of the subregion.
		int pad_size_bottom = -1 * std::min(0, image_rows - bottom_edge);
		
		// Pad the subregion with zeros and copy to the returned variable.
		cv::copyMakeBorder(sub_region_temp, output_mat, pad_size_top, pad_size_bottom, pad_size_left, pad_size_right, cv::BORDER_CONSTANT, 0);
				
	} //end extract_subregion
	
	//void rpc_cpu(cv::Mat &correlation_plane, cv::Mat sub_region_01, cv::Mat sub_region_02, cv::Mat spectral_filter, int region_height, int region_width)
	
	void rpc_cpu(const int region_height, const int region_width){
		// This function performs the RPC correlation on CPU. 
		// Should write another version or adpt this for GPU.
		
		// Size of the data
	
		// Declare the input and output arrays
		/* Problem: Compiler throwing warnings about forbidding variable size arrays
			when I do "fftwf_complex fft_out[region_height][region_width]"
			In any case, the FFTW plan creation won't end up inside of this function, 
			but this problem will still need to be addressed. */ 
		fftwf_complex fft_out[128][128];
	
		// Declare data
		float input_array[128][128];
	
		// Declare the fftw plan
		fftwf_plan plan;
	
		// Create the FFT plan
		plan = fftwf_plan_dft_r2c_2d(region_width, region_height, &input_array[0][0], &fft_out[0][0], FFTW_PATIENT);
	
		// This destroys the FFTW plan.
		fftwf_destroy_plan(plan);
			
	}
	
	
} // End namespace










