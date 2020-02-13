#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG inFile, outFile;

  // reads files to the corresponding PNGs
  inFile.readFromFile(inputFile);
  outFile.readFromFile(inputFile);

  // save inputFile's width and height
  int width = inFile.width();
  int height = inFile.height();

  // save inputFile's pixel located at (x,y)
  // at the location of (width-1-x, height-1-y) in outFile (rotate 180 deg)
  for(int x = 0; x < width; x++){
    for(int y = 0; y < height; y++){
      outFile.getPixel(width-1-x, height-1-y) = inFile.getPixel(x, y);
    }
  }

  outFile.writeToFile(outputFile);
}


double sinc(double x);

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      double signedX = (double(x)-400)/20;
      double signedY = -(double(y)-400);
      double dist = abs(signedY - 370*sinc(signedX));
      png.getPixel(x,y).h = 350 - std::sqrt(dist)*6;
      png.getPixel(x,y).s = .5;
      png.getPixel(x,y).a = .5;

      if(dist < 10){
        png.getPixel(x,y).l = 1;
      }
      else if(dist < 80){
        png.getPixel(x,y).l = 1 - dist*.01;
      }
      else{
        png.getPixel(x,y).l = 0.2;
      }
    }
  }

  return png;
}


double sinc(double x){
  return !x ? 1 : std::sin(x)/x;
}
