#include <iostream>
#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image pug;
  pug.readFromFile("pug.png");

  Image me;
  me.readFromFile("metext.png");
  Image valgrind;
  valgrind.readFromFile("valgrind.png");
  Image csicon;
  csicon.readFromFile("cs225.png");

  StickerSheet meme(pug, 3);
  meme.addSticker(me, 700, 350);
  meme.addSticker(valgrind, 25, 350);
  meme.addSticker(csicon, 25, 25);

  Image pic = meme.render();
  pic.writeToFile("myImage.png");

  return 0;
}
