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
     map<Point<3>,int> outerContainment;
     vector<Point<3>> storage_loc;
     unsigned i, a = theTiles.size();
     MosaicCanvas* finalProduct = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     storage_loc.resize(a);

     for (i = 0; i < a; i++) {
     	storage_loc[i].set(0, theTiles[i].getAverageColor().l);
     	storage_loc[i].set(1, theTiles[i].getAverageColor().u);
     	storage_loc[i].set(2, theTiles[i].getAverageColor().v);
     	outerContainment[storage_loc[i]] = i;
     }
     KDTree<3> tree(storage_loc);
     for (int i = 0; i < theSource.getRows(); i++) {
       for (int j = 0; j < theSource.getColumns(); j++){
        Point<3> setterLocation;
       	LUVAPixel colour = theSource.getRegionColor(i, j);
       	setterLocation.set(0, colour.l);
       	setterLocation.set(1, colour.u);
       	setterLocation.set(2, colour.v);;
       	finalProduct -> setTile(i, j, &theTiles[outerContainment[tree.findNearestNeighbor(setterLocation)]]);
       }
     }
     bool is_true = theSource.getRows() >= 0 && theSource.getColumns() >= 0;
     while (is_true == true) {
       return finalProduct;
     }
     return NULL;
}
