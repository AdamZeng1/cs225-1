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
ImageTraversal::Iterator::Iterator() : finished_flag(true) {
  // Nothing
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start) 
	:traversal(&traversal), start(start), finished_flag(false) {
	current = traversal.peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {

  	Point curtop = traversal->pop();
  	traversal->setVisit(curtop.x, curtop.y);
  	
  	Point right(curtop.x + 1, curtop.y);
  	Point below(curtop.x, curtop.y + 1);
  	Point lefft(curtop.x - 1, curtop.y);
  	Point above(curtop.x, curtop.y - 1);
  	HSLAPixel & startingPixel = traversal->passPng()->getPixel(start.x, start.y);

  	// Right case
  	if (right.x >= 0 && right.y >= 0 && right.x < traversal->passPng()->width() && right.y < traversal->passPng()->height() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(right.x, right.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(right);
  		}
  	}
  	// Below case
  	if (below.x >= 0 && below.y >= 0 && below.x < traversal->passPng()->width() && below.y < traversal->passPng()->height() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(below.x, below.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(below);
  		}
  	}
  	// Left case
  	if (lefft.x >= 0 && lefft.y >= 0 && lefft.x < traversal->passPng()->width() && lefft.y < traversal->passPng()->height() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(lefft.x, lefft.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(lefft);
  		}
  	}
  	// Above case
  	if (above.x >= 0 && above.y >= 0 && above.x < traversal->passPng()->width() && above.y < traversal->passPng()->height() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(above.x, above.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(above);
  		}
  	}
  	while ( !(traversal->empty()) && (traversal->getVisited(traversal->peek().x, traversal->peek().y))) {
  		traversal->pop();
  	}
  	if (traversal->empty()) {
  		finished_flag = true;
  		return *this;
  	}
  	current = traversal->peek();
  	return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  	return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  	/*
  	bool thisEmpty = false;
  	bool otherEmpty = false;

  	if (traversal == NULL) {thisEmpty = true;}
  	if (other.traversal == NULL) {otherEmpty = true;}

  	if (!thisEmpty) {thisEmpty = traversal->empty();}
  	if (!otherEmpty) {otherEmpty = other.traversal->empty();}

  	if (thisEmpty && otherEmpty) {return true;}
  	else if ((!thisEmpty) && (!otherEmpty)) {return traversal != other.traversal;}
  	else return true;
  	*/
  	return !(finished_flag && other.finished_flag);
}

