#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image cs_illinois;
  cs_illinois.readFromFile("CS_illinois.png");
  cs_illinois.scale(1.1);

  StickerSheet finalImage(cs_illinois, 5);

  Image myImage;
  Image coffee;
  Image segFault;
  Image noSleep;
  coffee.readFromFile("coffee.png");
  segFault.readFromFile("segfault.png");
  noSleep.readFromFile("no_sleep.png");

  coffee.scale(140, 160);
  segFault.scale(140, 160);
  noSleep.scale(140, 160);

  finalImage.addSticker(coffee, 0, 110);
  finalImage.addSticker(segFault, 160, 110);
  finalImage.addSticker(noSleep, 320, 110);
  myImage = finalImage.render();

  myImage.writeToFile("myImage.png");




  return 0;
}
