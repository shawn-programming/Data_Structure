#include "StickerSheet.h"
#include <algorithm>
using namespace std;

StickerSheet::StickerSheet(){
  basePicture_ = Image();
  maxNum_ = 0;
  stickers_ = NULL;
}
StickerSheet::StickerSheet(const Image &picture, unsigned max){
  basePicture_ = picture;

  maxNum_ = max;
  stickers_ = new Image[max];
}

StickerSheet::~StickerSheet(){
  delete[] stickers_;
}

StickerSheet::StickerSheet(const StickerSheet &other){
  basePicture_ = other.basePicture_;

  maxNum_ = other.maxNum_;

  stickerCounter_ = other.stickerCounter_;

  stickers_ = new Image[maxNum_];

  for(unsigned int i=0; i<maxNum_; i++){
    stickers_[i] = other.stickers_[i];
  }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
  basePicture_ = other.basePicture_;

  maxNum_ = other.maxNum_;

  stickerCounter_ = other.stickerCounter_;

  for(unsigned int i=0; i<maxNum_; i++){
    stickers_[i] = other.stickers_[i];
  }

  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
  Image* newStickers_ = new Image[max];

  for(unsigned int i=0; i<min(max, maxNum_); i++){
    newStickers_[i] = stickers_[i];
  }

  delete[] stickers_;

  stickers_ = newStickers_;

  maxNum_ = max;
  if(maxNum_ < stickerCounter_){
    stickerCounter_ = maxNum_;
  }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  if(stickerCounter_ == maxNum_){
    return -1;
  }
  sticker.x_ = x;
  sticker.y_ = y;
  stickers_[stickerCounter_++] = sticker;
  return stickerCounter_-1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index >= stickerCounter_){
    return false;
  }

  stickers_[index].x_ = x;
  stickers_[index].y_ = y;

  return true;
}

void StickerSheet::removeSticker(unsigned index){
  unsigned int i;
  for(i = index; i<stickerCounter_-1; i++){
    stickers_[i] = stickers_[i+1];
  }

  stickerCounter_--;
}

Image* StickerSheet::getSticker(unsigned index){
  if(!(index < stickerCounter_)){
    return nullptr;
  }
  return &(stickers_[index]);
}

Image StickerSheet::render()const{
  unsigned int height=0;
  unsigned int width=0;

  for(unsigned int i=0; i < stickerCounter_; i++){
    width = max(width, stickers_[i].width()+stickers_[i].x_);
    height = max(height, stickers_[i].height()+stickers_[i].y_);
  }

  width = max(basePicture_.width(), width);
  height = max(basePicture_.height(), height);

  Image newImage = basePicture_;

  newImage.resize(width, height);


  for(unsigned int i=0; i < stickerCounter_; i++){
    Image & image = stickers_[i];
    for(unsigned int x = 0; x< image.width(); x++){
      for(unsigned int y = 0; y< image.height(); y++){
        if(image.getPixel(x ,y).a == 0){
          continue;
        }
        newImage.getPixel(x+image.x_, y+image.y_).h = image.getPixel(x, y).h;
        newImage.getPixel(x+image.x_, y+image.y_).s = image.getPixel(x, y).s;
        newImage.getPixel(x+image.x_, y+image.y_).l = image.getPixel(x, y).l;
        newImage.getPixel(x+image.x_, y+image.y_).a = image.getPixel(x, y).a;
      }
    }
  }
  return newImage;
}
