#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include "../cs225/PNG.h"
#include <string>

using namespace cs225;
using namespace std;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(string filename1) {
	png_.readFromFile(filename1);
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  	HSLAPixel cur_pix = png_.getPixel(x % png_.width(), y % png_.width());
  	if (cur_pix.l > .1) {  // If white pixel
  		cur_pix = HSLAPixel(HSLAPixel(200, 1, .5));
  	}
  	return cur_pix;
}
