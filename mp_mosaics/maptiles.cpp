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
  /**
     * @todo Implement this function!
     */
    
  MosaicCanvas* res = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

  map<Point<3>, TileImage*> HT;
  vector<Point<3>> points;

  for(unsigned i=0; i<theTiles.size(); i++){
    Point<3> point = convertToXYZ(theTiles[i].getAverageColor());
    HT[point] = &theTiles[i];
    points.push_back(point);
  }

  KDTree<3> kdTree = KDTree<3>(points);

  for(int i=0; i<theSource.getRows(); i++){
    for(int j=0; j<theSource.getColumns(); j++){
      Point<3> thePoint = convertToXYZ(theSource.getRegionColor(i, j));
      Point<3> nearest = kdTree.findNearestNeighbor(thePoint);
      res->setTile(i, j, HT[nearest]);
    }
  }

  return res;
}
