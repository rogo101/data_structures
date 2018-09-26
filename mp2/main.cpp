#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image basePicture;
  Image sticker1;
  Image sticker2;
  Image sticker3;

  basePicture.readFromFile("basePicture.png");
  sticker1.readFromFile("sticker1.png");
  sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker3.png");

  StickerSheet yee(basePicture, 3);

  yee.addSticker(sticker1, 200, 100);
  yee.addSticker(sticker2, 300, 200);
  yee.addSticker(sticker3, 100, 300);

  Image done = yee.render();
  done.writeToFile("myImage.png");

  return 0;
}
