#include "Image.h"

using namespace std;
//Lighten an Image by increasing the luminance of every pixel by 0.1


Image::Image() : PNG(1 ,1) {
}


Image::Image(unsigned int width, unsigned int height) : PNG(width, height){
}

void Image::lighten(){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l = pixel.l+0.1 > 1 ? 1 : pixel.l+0.1;
    }
  }
}
//Lighten an Image by increasing the luminance of every pixel by amount
void Image::lighten(double amount){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l = pixel.l+amount > 1 ? 1 : pixel.l+amount;
    }
  }
}
//Darken an Image by decreasing the luminance of every pixel by 0.1
void Image::darken(){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l = pixel.l-0.1 < 0 ? 0 : pixel.l-0.1;
    }
  }
}
//Darkens an Image by decreasing the luminance of every pixel by amount
void Image::darken(double amount){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l = pixel.l-amount < 0 ? 0 : pixel.l-amount;
    }
  }
}
//Saturates an Image by increasing the saturation of every pixel by 0.1
void Image::saturate(){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = pixel.s+0.1 > 1 ? 1 : pixel.s+0.1;
    }
  }
}
//Saturates an Image by increasing the saturation of every pixel by amount.
void Image::saturate(double amount){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = pixel.s+amount > 1 ? 1 : pixel.s+amount;
    }
  }
}
//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
void Image::desaturate(){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = pixel.s-0.1 < 0 ? 0 : pixel.s-0.1;
    }
  }
}
//Desaturates an Image by decreasing the saturation of every pixel by amount
void Image::desaturate(double amount){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = pixel.s-amount < 0 ? 0 : pixel.s-amount;
    }
  }
}
//Turns the image grayscale.
void Image::grayscale(){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      this->getPixel(x,y).s=0;
    }
  }
}
//Rotates the color wheel by degrees.
void Image::rotateColor(double degrees){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      if(this->getPixel(x,y).h + degrees > 360){
        this->getPixel(x,y).h = this->getPixel(x,y).h + degrees - 360;
      }
      else if(this->getPixel(x,y).h + degrees < 0){
        this->getPixel(x,y).h = this->getPixel(x,y).h + degrees + 360;
      }
      else{
        this->getPixel(x,y).h = this->getPixel(x,y).h + degrees;
      }
    }
  }
}
//Illinify the image
void Image::illinify(){
  for(unsigned int x = 0; x < this->width(); x++){
    for(unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.h <= 11){
        pixel.h = 11;
      }
      else if(pixel.h >=216){
        pixel.h = 371-pixel.h > pixel.h-216 ? 216 : 11;
      }
      else{
        pixel.h = pixel.h-11 > 216-pixel.h ? 216 : 11;
      }
    }
  }
}
//Scale the Image by a given factor.
void Image::scale(double factor){

  PNG oldImage = PNG(*this);

  unsigned int newWidth = this->width() * factor;
  unsigned int newHeight = this->height() * factor;

  this->resize(newWidth, newHeight);

  for (unsigned x = 0; x < newWidth; x++) {
    for (unsigned y = 0; y < newHeight; y++) {
      unsigned int oldX = x / factor;
      unsigned int oldY = y / factor;
      HSLAPixel & oldPixel = oldImage.getPixel(oldX, oldY);
      HSLAPixel & newPixel = this->getPixel(x, y);
      newPixel = oldPixel;
    }
  }
}
//Scales the image to fit within the size (w x h).
void Image::scale (unsigned w, unsigned h){

  double wFactor = double(w) / double(width());
  double hFactor = double(h) / double(height());

  double factor = min(wFactor, hFactor);

  scale(factor);
}
