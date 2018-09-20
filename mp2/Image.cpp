#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

Image::Image() {
	xCoord_ = 0;
	yCoord_ = 0;
}

void Image::lighten() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.l += 0.1;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
		}
	}
}

void Image::lighten(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.l += amount;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
		}
	}
}

void Image::darken() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.l -= 0.1;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
		}
	}
}

void Image::darken(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.l -= amount;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
		}
	}
}

void Image::saturate() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.s += 0.1;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
		}
	}
}

void Image::saturate(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.s += amount;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
		}
	}
}

void Image::desaturate() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.s -= 0.1;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
		}
	}
}

void Image::desaturate(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.s -= amount;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
		}
	}
}

void Image::grayscale() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.s = 0.0;
		}
	}
}

void Image::rotateColor(double degrees) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			cur_pixel.h += degrees;
			while (cur_pixel.h > 360.0) {
				cur_pixel.h -= 360.0;
			}
			while (cur_pixel.h < 0.0) {
				cur_pixel.h += 360.0;
			}
		}
	}
}

void Image::illinify() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			if (cur_pixel.h >= 113.5 && cur_pixel.h < 293.5) cur_pixel.h = 216;
			else cur_pixel.h = 11;
		}
	}
}

void Image::scale(double factor) {

	unsigned int newWidth = width() * factor;
	unsigned int newHeight = height() * factor;

	Image * copyImage = new Image();
	*copyImage = *this;
	resize(newWidth, newHeight);

	for (unsigned int h = 0; h < newHeight; h++) {
		for (unsigned int w = 0; w < newWidth; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			HSLAPixel & cur_copy_pixel = copyImage->getPixel(w / factor, h / factor);
			cur_pixel = cur_copy_pixel;
		}
	}
	
	delete copyImage;
}

void Image::scale(unsigned x, unsigned y) {

	Image * copyImage = new Image();
	*copyImage = *this;
	resize(x, y);

	double xFactor = x / width();
	double yFactor = y / height();

	for (unsigned int h = 0; h < y; h++) {
		for (unsigned int w = 0; w < x; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			HSLAPixel & cur_copy_pixel = copyImage->getPixel(w / xFactor, h / yFactor);
			cur_pixel = cur_copy_pixel;
		}
	}
	
	delete copyImage;
}

void Image::setCoords(unsigned x, unsigned y) {
	xCoord_ = x;
	yCoord_ = y;
}

unsigned Image::getX() {
	return xCoord_;
}

unsigned Image::getY() {
	return yCoord_;
}
