#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"
#include <string>

using namespace cs225;
using namespace std;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {  // Painter that uses another image
public:
	MyColorPicker(string filename1);
  	HSLAPixel getColor(unsigned x, unsigned y);

private:
	PNG png_;
};
