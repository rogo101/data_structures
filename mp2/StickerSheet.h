/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once

# include "cs225/HSLAPixel.h"
# include "cs225/PNG.h"
# include "Image.h"

namespace cs225 {

  class StickerSheet {
    private:
      int max_;
      Image* basePicture;
      Image** stickers;
      unsigned * stickerLocX;
      unsigned * stickerLocY;
      unsigned numberOfStickers;
    public:
      void helperCopy(const StickerSheet &other);
      void helperDelete();
      StickerSheet(const Image &picture, unsigned max);
      ~StickerSheet();
      StickerSheet(const StickerSheet &other);
      const StickerSheet & operator = (const StickerSheet &other);
      void changeMaxStickers(unsigned max);
      int addSticker(Image &sticker, unsigned x, unsigned y);
      bool translate(unsigned index, unsigned x, unsigned y);
      void removeSticker(unsigned index);
      Image* getSticker(unsigned index)const;
      Image render()const;
  };

}
