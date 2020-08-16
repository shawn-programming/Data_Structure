#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(int hue, int saturation, int luminance){
  hue_ = hue;
  saturation_ = saturation;
  luminance_ = luminance;
}


HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double hue = double(int(x/hue_) % 360);
  double saturation = double(int(y%360)) / 360;
  double luminance = double(int(y%360)) / 360;

  HSLAPixel pixel(hue, saturation, luminance);
  return pixel;
}
