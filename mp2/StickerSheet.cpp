#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	Images = new Image *[other.max_];
	for (unsigned i = 0; i < other.max_; i++) {
		Images[i] = new Image();
		*(Images[i]) = *(other.getSticker(i));
	}
	max_ = other.max_;
}

void StickerSheet::clear_() {
	for (unsigned i = 0; i < max_; i++) {
		delete Images[i];
	}
	delete[] Images;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	Images = new Image *[max];
	Images[0] = new Image();
	*(Images[0]) = picture;
	max_ = max;
}

StickerSheet::~StickerSheet() {
	clear_();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		clear_();
		copy_(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	Image ** new_images = new Image *[max];  // Create new image double pointer
	if (max < max_) {
		for (unsigned i = 0; i < max; i++) {
			new_images[i] = Images[i];
		}
	}
	else {
		for (unsigned i = 0; i < max_; i++) {
			new_images[i] = Images[i];
		}
	}
	for (unsigned i = 0; i < max_; i++) {
		delete Images[i];  // This will create a mem leak i think
	}
	delete[] Images;
	Images = new_images;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < max_; i++) {
		if (Images[i] != NULL) {
			sticker.setCoords(x, y);
			Images[i] = &sticker;
			return i;
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (Images[index] == NULL) return false;
	Images[index]->setCoords(x, y);
	return true;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		Images[i] = Images[i + 1];
	}
}

Image * StickerSheet::getSticker(unsigned index) const {
	return Images[index];
}

Image StickerSheet::render() const {
	Image * result = new Image();
	*result = *(Images[0]);
	Image * cur_image;
	for (unsigned cur_image_index = 1; cur_image_index < max_; cur_image_index++) {
		cur_image = Images[cur_image_index];
		unsigned curx = cur_image->getX();
		unsigned cury = cur_image->getY();
		unsigned curw = cur_image->width();
		unsigned curh = cur_image->height();
		// if new pic goes off side
		unsigned horizSpace = (curx + curw);
		if (result->width() < horizSpace) {
			result->resize(horizSpace, result->height());
		}
		// if new pic goes off below
		unsigned vertiSpace = (cury + curh);
		if (result->height() < vertiSpace) {
			result->resize(result->width(), vertiSpace);
		}
		for (unsigned h = cury; h < (cury + curh); h++) {
			for (unsigned w = curx; w < (curx + curw); w++) {
				HSLAPixel & cur_result_pixel = result->getPixel(w, h);
				HSLAPixel & cur_sticker_pixel = cur_image->getPixel(w - curx, h - cury);
				if (cur_sticker_pixel.a != 0) {cur_result_pixel = cur_sticker_pixel;}
			}
		}
	}
	return *result;
}

unsigned StickerSheet::getMax() {
	return max_;
}
