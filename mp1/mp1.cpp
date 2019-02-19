#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <iostream>


void rotate(std::string inputFile, std::string outputFile) {
  PNG* toRotate = new PNG();
  toRotate->readFromFile(inputFile);
  unsigned width = toRotate->width();
  unsigned height = toRotate->height();
  PNG* rotated = new PNG(width, height);

  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
          HSLAPixel& after = (*rotated).getPixel(x, y);
          after = toRotate->getPixel(width - x - 1, height - y - 1);
      }
  }

  rotated->writeToFile(outputFile);
  delete toRotate;
  delete rotated;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel& modify = png.getPixel(x, y);
      modify.l = 0.5;
      modify.h = x / 3;
  }
}

  return png;
}
