#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image alma;
  alma.readFromFile("alma.png");

  Image eye;
  eye.readFromFile("i.png");

  StickerSheet final(alma,2);
  final.addSticker(eye, 50, 50);

  Image pic = final.render();
  pic.writeToFile("wow.png");

  return 0;
}
