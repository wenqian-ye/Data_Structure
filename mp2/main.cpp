#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
    Image hello;
    hello.readFromFile("hello.png");
    Image white;
    white.readFromFile("white.png")
;


    // Image white,,i3;
    // i1.readFromFile("tests/i.png");
    // i2.readFromFile("tests/i2.png");
    // i3.readFromFile("tests/i3.png");
    //
    // StickerSheet sheet(hello, 5);
    // sheet.addSticker(i1, 20, 200);
    // sheet.addSticker(i2,50,60);
    // sheet.addSticker(i3,900,50);
    //
    // Image expected;
    // expected.readFromFile("tests/expected.png");
    // sheet.render().writeToFile("myImage.png");

  return 0;
}
