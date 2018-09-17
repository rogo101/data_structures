#include <iostream>

#include "Image.h"

void Image::lighten() {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.l + 0.1 <= 1 && pixel.l + 0.1 >= 0) {
        pixel.l = pixel.l + 0.1;
      }
      else {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::lighten(double amount) {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.l + amount <= 1 && pixel.l + amount >= 0) {
        pixel.l = pixel.l + amount;
      }
      else if (amount < 0){
        pixel.l = 0;
      }
      else {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::darken() {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.l - 0.1 <= 1 && pixel.l - 0.1 >= 0) {
        pixel.l = pixel.l - 0.1;
      }
      else {
        pixel.l = 0;
      }
    }
  }
}

void Image::darken(double amount) {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.l - amount <= 1 && pixel.l - amount >= 0) {
        pixel.l = pixel.l - amount;
      }
      else if (amount < 0){
        pixel.l = 1.0;
      }
      else {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate() {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.s + 0.1 <= 1 && pixel.s + 0.1 >= 0) {
        pixel.s = pixel.s + 0.1;
      }
      else {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::saturate(double amount) {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.s + amount <= 1 && pixel.s + amount >= 0) {
        pixel.s = pixel.s + amount;
      }
      else if (amount < 0){
        pixel.s = 0;
      }
      else {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::desaturate() {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.s - 0.1 <= 1 && pixel.s - 0.1 >= 0) {
        pixel.s = pixel.s - 0.1;
      }
      else {
        pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.s - amount <= 1 && pixel.s - amount >= 0) {
        pixel.s = pixel.s - amount;
      }
      else if (amount < 0){
        pixel.s = 1.0;
      }
      else {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.h + degrees <= 360 && pixel.h + degrees >= 0) {
        pixel.h = pixel.h + degrees;
      }
      else if (pixel.h + degrees > 360){
        while (pixel.h + degrees > 360) {
          degrees = degrees - 360;
        }
        pixel.h = pixel.h + degrees;
      }
      else if (pixel.h + degrees < 0){
        while (pixel.h + degrees < 0) {
          degrees = degrees + 360;
        }
        pixel.h = pixel.h + degrees;
      }
    }
  }
}

void Image::illinify() {
  for (unsigned x = 0; x < this -> width(); x++) {
    for (unsigned y = 0; y < this -> height(); y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(x, y);
      if (pixel.h < 102.5 || pixel.h > 282.5) {
        pixel.h = 11;
      }
      else {
        pixel.h = 216;
      }
    }
  }
}

void Image::scale(double factor) {
  if (factor >= 0) {
    double newWidth = this -> width() * factor;
    double newHeight = this -> height() * factor;
    unsigned int intnewWidth = static_cast<unsigned int>(newWidth);
    unsigned int intnewHeight = static_cast<unsigned int>(newHeight);
    PNG* toScale = new PNG(intnewWidth, intnewHeight);

    for (unsigned int x = 0; x < intnewWidth; x++) {
      for (unsigned int y = 0; y < intnewHeight; y++) {
        cs225::HSLAPixel & pixel = this -> getPixel(static_cast<unsigned int>(x*(1/factor)), static_cast<unsigned int>(y*(1/factor)));
        cs225::HSLAPixel & toReplace = (*toScale).getPixel(x, y);
        toReplace = pixel;
      }
    }

    this -> resize(intnewWidth,intnewHeight);

    for (unsigned int x = 0; x < intnewWidth; x++) {
      for (unsigned int y = 0; y < intnewHeight; y++) {
        cs225::HSLAPixel & pixel1 = this -> getPixel(x, y);
        cs225::HSLAPixel & pixel2 = toScale -> getPixel(x, y);
        pixel1 = pixel2;
      }
    }

    delete toScale;
  }

}

void Image::scale(unsigned w, unsigned h) {
  PNG* toScale = new PNG(w, h);
  double factorX = static_cast<double>(w) / static_cast<double>(this -> width());
  double factorY = static_cast<double>(h) / static_cast<double>(this -> height());

  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      cs225::HSLAPixel & pixel = this -> getPixel(static_cast<unsigned int>(x*(1/factorX)), static_cast<unsigned int>(y*(1/factorY)));
      cs225::HSLAPixel & toReplace = (*toScale).getPixel(x, y);
      toReplace = pixel;
    }
  }

  this -> resize(w,h);

  for (unsigned int x = 0; x < w; x++) {
    for (unsigned int y = 0; y < h; y++) {
      cs225::HSLAPixel & pixel1 = this -> getPixel(x, y);
      cs225::HSLAPixel & pixel2 = toScale -> getPixel(x, y);
      pixel1 = pixel2;
    }
  }

  delete toScale;
}
