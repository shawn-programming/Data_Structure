#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  double tolerance_ = 0;
}

ImageTraversal::Iterator::Iterator(bool isEnd) {
  /** @todo [Part 1] */
  this->isEnd = isEnd;
}

ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, ImageTraversal* traversal){
  for(unsigned int i=0; i< png.width() * png.height(); i++){
    visited_.push_back(false);
  }
  png_ = PNG(png);
  start_ = Point(start.x, start.y);
  curr_ = Point(start.x, start.y);
  tolerance_ = tolerance;
  traversal_ = traversal;
  visited_[start.x + (start.y)*png_.width()] = true;
}

bool ImageTraversal::Iterator::available(const Point point){
  unsigned int x = point.x;
  unsigned int y = point.y;

  if(x >= png_.width() ||
    y >= png_.height() ||
    visited_[x + y * png_.width()]){
      return false;
    }

  HSLAPixel startPixel = png_.getPixel(start_.x, start_.y);
  HSLAPixel currPixel = png_.getPixel(point.x, point.y);
  if(calculateDelta(startPixel, currPixel) > tolerance_){
    return false;
  }

  return true;
}

void ImageTraversal::Iterator::visit(const Point point){
  visited_[png_.width() * point.y + point.x] = true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point p1 = Point(curr_.x+1, curr_.y);
  Point p2 = Point(curr_.x, curr_.y+1);
  Point p3 = Point(curr_.x-1, curr_.y);
  Point p4 = Point(curr_.x, curr_.y-1);

  if(available(p1)){traversal_->add(p1);}
  if(available(p2)){traversal_->add(p2);}
  if(available(p3)){traversal_->add(p3);}
  if(available(p4)){traversal_->add(p4);}

  while(visited_[traversal_->peek().y * png_.width() + traversal_->peek().x]==true){
    traversal_->pop();
    if(traversal_->empty()){
      break;
    }
  }
  if(traversal_->empty()){
    isEnd = true;

  }
  else{
    curr_ = Point(traversal_->peek().x, traversal_->peek().y);
    visit(curr_);
  }


  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return isEnd != other.isEnd;
}
