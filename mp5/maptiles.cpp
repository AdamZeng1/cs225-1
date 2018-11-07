/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    vector<Point<3>> all_points;
    map<Point<3>, TileImage*> map_;
    // Iterate through all tilse, mapping their average pixel in a new array to them
    for (auto iter = theTiles.begin(); iter != theTiles.end(); iter++) {
    	LUVAPixel pixel_ = iter->getAverageColor(); // Get average pixel in Point form
    	Point<3> point_ = convertToXYZ(pixel_);
    	all_points.push_back(point_);  // Push average pixel to back of all_points
    	map_[point_] = &*iter;  // Map that average pixel to its tile
    }
    KDTree<3> kdt_avgcolor(all_points);  // Make a kd tree of all average points
    // Make a new canvas to be returned
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    // Itreate through canvas, choosing a best tile based on the average color of each region
    for (int i = 0; i < canvas->getRows(); i++) {
    	for (int j = 0; j < canvas->getColumns(); j++) {
    		Point<3> goal_ = convertToXYZ(theSource.getRegionColor(i, j));  // Average color of region
    		Point<3> best_ = kdt_avgcolor.findNearestNeighbor(goal_);  // Find NN of average color of region
    		TileImage* correct_tile = map_[best_];  // Get the tile that is mapped to by best point
    		canvas->setTile(i, j, correct_tile);  // Set that tile on the canvas
    	}
    }
    return canvas;
}

