#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <math.h> /* sin */


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
	PNG image;
	image.readFromFile(inputFile);
	unsigned int width = image.width();
	unsigned int height = image.height();
	PNG output(width, height);
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			HSLAPixel & inPixel = image.getPixel(x, y);
			HSLAPixel & outPixel  = output.getPixel(width - x - 1, height - y - 1);
			outPixel = inPixel;
		}
	}
	output.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	double DOT_SIZE = .1; /* bigger means smaller dots */
	PNG png(width, height);
  	// TODO: Part 3
	for (unsigned x = 0; x < png.width(); x++) {
		for (unsigned y = 0; y < png.height(); y++) {
			HSLAPixel & curPixel = png.getPixel(x, y);
			double intensity = sin(DOT_SIZE * x) * sin(DOT_SIZE * y);
			curPixel.h = intensity * 45 + 270.0 * (double(x) / double(width)) + 45;
			curPixel.s = 1.0;
			curPixel.l = 0.5;
			curPixel.a = 1.0;
		}
	}
	return png;
}