#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Open file and insert PPM header format
  std::ofstream f;
  f.open(filename);
  
  // First line: PPM format
  if (num_channels == 1)  // P2 for grayscale images
    f << "P2" << std::endl;
  else  // P3 for color RGB images
    f << "P3" << std::endl;
  // Second line: filename (optional)
  f << "#" << filename << std::endl;
  // Third line: width and height
  f << width << " " << height << std::endl;
  // Fourth line: max pixel value
  f << "255" << std::endl;
  
  // Insert content (pixel values) into PPM file
  unsigned int loc = 0; // pixel location
  for (unsigned int i = 0; i < height; i ++){
    for (unsigned int j = 0; j < width; j ++){
      loc = i * width + j;
      for (unsigned int k = 0; k < num_channels; k++){
        f << (unsigned int) data[loc*num_channels+k] << " ";
      }
    }
  }

  // Close file and return
  f.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
