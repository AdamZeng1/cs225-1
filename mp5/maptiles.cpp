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
    for (auto iter = theTiles.begin(); iter != theTiles.end(); iter++) {
    	LUVAPixel pixel_ = iter->getAverageColor();
    	Point<3> point_ = convertToXYZ(pixel_);
    	all_points.push_back(point_);
    	map_[point_] = &*iter;
    }
    KDTree<3> kdt_avgcolor(all_points);
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int i = 0; i < canvas->getRows(); i++) {
    	for (int j = 0; j < canvas->getColumns(); j++) {
    		Point<3> goal_ = convertToXYZ(theSource.getRegionColor(i, j));
    		Point<3> best_ = kdt_avgcolor.findNearestNeighbor(goal_);
    		TileImage* correct_tile = map_[best_];
    		canvas->setTile(i, j, correct_tile);
    	}
    }
    return canvas;
}

