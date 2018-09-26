#include <iostream>

# include "StickerSheet.h"

namespace cs225 {
  void StickerSheet::helperCopy(const StickerSheet &other){
    //std::cout << "Helper Copy Called." << std::endl;

    max_ = other.max_;
    stickers = new Image*[max_];
    stickerLocX = new unsigned[max_];
    stickerLocY = new unsigned[max_];

    for (int i = 0; i < max_; i++) {
      stickers[i] = NULL;
      *(stickerLocX + i) = 0;
      *(stickerLocY + i) = 0;
    }

    for (int i = 0; i < max_; i++) {
      if (other.stickers[i] != NULL) {
        stickers[i] = new Image(*(other.stickers[i]));
        stickerLocX[i] = other.stickerLocX[i];
        stickerLocY[i] = other.stickerLocY[i];
      }
    }

    basePicture = new Image(*(other.basePicture));

    //std::cout << "Helper Copy Ended." << std::endl;
  }

  void StickerSheet::helperDelete() {
    //std::cout << "Helper Delete Called." << std::endl;

    delete [] stickers;
    stickers = NULL;
    delete [] stickerLocX;
    stickerLocX = NULL;
    delete [] stickerLocY;
    stickerLocY = NULL;
    delete basePicture;

    //std::cout << "Helper Delete Ended." << std::endl;
  }

  StickerSheet::StickerSheet(const Image &picture, unsigned max){
    //std::cout << "Base Picture Constructor Called." << std::endl;

    max_ = max;
    stickers = new Image*[max_];
    stickerLocX = new unsigned[max_];
    stickerLocY = new unsigned[max_];

    for (int i = 0; i < max_; i++) {
      stickers[i] = NULL;
      *(stickerLocX + i) = 0;
      *(stickerLocY + i) = 0;
    }

    this -> basePicture = new Image(picture);

    //std::cout << "Base Picture Constructor Ended." << std::endl;
  }

  StickerSheet::~StickerSheet() {
    //std::cout << "Destructor Called." << std::endl;
    helperDelete();
    //std::cout << "Destructor Ended." << std::endl;
  }

  StickerSheet::StickerSheet(const StickerSheet &other){
    //std::cout << "Copy Constructor Called." << std::endl;
    helperCopy(other);
    //std::cout << "Copy Constructor Ended." << std::endl;
  }

  const StickerSheet& StickerSheet::operator = (const StickerSheet &other){
    //std::cout << "Operator Definition Called." << std::endl;
    helperDelete();
    helperCopy(other);
    return *this;
    //std::cout << "Operator Definition Ended." << std::endl;
  }

  void StickerSheet::changeMaxStickers(unsigned max) {
    if (static_cast<unsigned int>(max_) == max) {
      return;
    }
    else {
      max_ = max;
      unsigned * copyArray1 = new unsigned[max];
      unsigned * copyArray2 = new unsigned[max];
      Image** copyArray3 = new Image *[max_];

      for (unsigned i = 0; i < max; i++) {
        if(i < numberOfStickers) {
          copyArray1[i] = stickerLocX[i];
          copyArray2[i] = stickerLocY[i];
          copyArray3[i] = new Image(*stickers[i]);
      }
        else {
          stickerLocX[i] = 0;
          stickerLocY[i] = 0;
          copyArray3[i] = NULL;
        }
      }

      stickerLocX = copyArray1;
      stickerLocY = copyArray2;
      stickers = copyArray3;
    }
  }

  int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    //std::cout << "addSticker Called." << std::endl;
    if (x < basePicture -> width() && y < basePicture -> height()) {
      for (int i = 0; i < max_; i++) {
        if (stickers[i] == NULL) {
          numberOfStickers++;
          stickers[i] = &sticker;
          *(stickerLocX + i) = x;
          *(stickerLocY + i) = y;
          return i;
          break;
        }
      }
    }
    return -1;
  }

  bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    //std::cout << "translate Called." << std::endl;

    if (stickers[index] != NULL) {
      *(stickerLocX + index) = x;
      *(stickerLocY + index) = y;
      return true;
    }
    else {
      return false;
    }
  }

  void StickerSheet::removeSticker(unsigned index){
    //std::cout << "removeSticker Called." << std::endl;
    stickers[index] = NULL;
    *(stickerLocX + index) = 0;
    *(stickerLocY + index) = 0;
    //std::cout << "removeSticker Ended." << std::endl;
  }

  Image* StickerSheet::getSticker(unsigned index)const{
    //std::cout << "getSticker Called." << std::endl;

    if (stickers[index] != NULL) {
      return stickers[index];
    }
    else {
      return NULL;
    }
  }

  Image StickerSheet::render() const{
    //std::cout << "render Called." << std::endl;

    Image * renderedFull = basePicture;

    unsigned renderSizeX = basePicture -> width();
    unsigned renderSizeY = basePicture -> height();

    //std::cout << "Old Size (X): " << renderSizeX << std::endl;
    //std::cout << "Old Size (Y): " << renderSizeY << std::endl;

    for (int i = 0; i < max_; i++) {
      if (stickers[i] != NULL) {
        //std::cout << "Iteration: " << i + 1 << std::endl;
        unsigned maxX = (*(stickerLocX + i) + stickers[i] -> width());
        unsigned maxY = (*(stickerLocY + i) + stickers[i] -> height());
        if (renderSizeX < maxX) {
          //std::cout << "Resize To (X): " << maxX << std::endl;
          renderSizeX = maxX;
        }
        if (renderSizeY < maxY) {
          //std::cout << "Resize To (Y): " << maxY << std::endl;
          renderSizeY = maxY;
        }
      }
    }

    renderedFull -> resize(renderSizeX, renderSizeY);

    for (unsigned x1 = 0; x1 < renderedFull -> width(); x1++) {
      for (unsigned y1 = 0; y1 < renderedFull -> height(); y1++) {
          HSLAPixel & pixel3 = basePicture -> getPixel(x1,y1);
          HSLAPixel & pixel4 = renderedFull -> getPixel(x1,y1);
          pixel4 = pixel3;
    }
  }

    for (int i = 0; i < max_; i++) {
      if (stickers[i] != NULL) {
        for (unsigned x = 0; x < stickers[i] -> width(); x++) {
          for (unsigned y = 0; y < stickers[i] -> height(); y++) {
            HSLAPixel & pixel1 = stickers[i] -> getPixel(x,y);
            HSLAPixel & pixel2 = renderedFull -> getPixel(x + stickerLocX[i], y + stickerLocY[i]);
            if (pixel1.a != 0) {
              pixel2.h = pixel1.h;
              pixel2.s = pixel1.s;
              pixel2.l = pixel1.l;
              pixel2.a = pixel1.a;
            }
          }
        }
      }
    }

    return *renderedFull;
  }
}
