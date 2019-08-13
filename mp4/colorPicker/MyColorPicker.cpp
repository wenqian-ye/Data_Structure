//#include "../cs225/HSLAPixel.h"
//#include "../Point.h"
//
//#include "ColorPicker.h"
//#include "MyColorPicker.h"
//
//using namespace cs225;
//
///**
// * Picks the color for pixel (x, y).
// * Using your own algorithm
// */
//HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
//  /* @todo [Part 3] */
//
//  return HSLAPixel();
//}


#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <time.h>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
    /* @todo [Part 3] */
    //srand(time(t));
    srand(t);
    t++;
    int hue;
    hue = h[rand() % 2];
    hue = double(hue);
    if(hue < 0)
        hue = -hue;
    HSLAPixel pixel(hue, 1, 0.5);
    return pixel;
}