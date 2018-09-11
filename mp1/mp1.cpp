#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  PNG* toRotate = new PNG();
  toRotate->readFromFile(inputFile);
  unsigned width = toRotate->width();
  unsigned height = toRotate->height();

  
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3

  return png;
}
