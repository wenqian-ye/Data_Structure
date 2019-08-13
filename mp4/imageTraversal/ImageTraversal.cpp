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
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
}
ImageTraversal::Iterator::Iterator(ImageTraversal* p){
    var = p;
}

ImageTraversal::Iterator::Iterator(Point start, PNG newPNG, double t, ImageTraversal* p){
    var = p;
    startPoint = start;
    current = startPoint;
    source = newPNG;
    tolerance = t;
    unsigned const W = source.width();
    unsigned const H = source.height();
    isVisited = new bool* [H];

    for(unsigned i = 0; i < H; i++){
        isVisited[i] = new bool [W];
        for(unsigned j = 0; j < W; j++){
            isVisited[i][j] = false;
        }
    }

    isVisited[startPoint.y][startPoint.x] = true;

    HSLAPixel a = source.getPixel(current.x, current.y);
    HSLAPixel* pixel = &a;

    int width = int(source.width());
    int height = int(source.height());

    int x = int(current.x);
    int y = int(current.y);

    if(x+1 < width && calculateDelta(*pixel, source.getPixel(x+1, y)) < tolerance){
        var->add(Point(x+1, y));
    }
    if(y+1 < height && calculateDelta(*pixel, source.getPixel(x, y+1)) < tolerance){
        var->add(Point(x, y+1));
    }
    if(x-1 >= 0 && calculateDelta(*pixel, source.getPixel(x-1, y)) < tolerance){
        var->add(Point(x-1, y));
    }
    if(y-1 >= 0 && calculateDelta(*pixel, source.getPixel(x, y-1)) < tolerance){
        var->add(Point(x, y-1));
    }


}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
    if(var->empty()){
        var = NULL;
        return *this;
    }
    //**get the next point
    Point temp = var->pop();
    //cout<<temp.x<<temp.y<<endl;
    //**if the next point has been visited, get the next again.
    while(isVisited[temp.y][temp.x]){
        //**if get to the end (no point in the stack/queue), raise a flag and return
        if(var->empty()){
            var = NULL;
            //break;
            return *this;
        }
        temp = var->pop();
    }
    isVisited[temp.y][temp.x] = true;
    current = temp;
    HSLAPixel* pixel = &(source.getPixel(startPoint.x, startPoint.y));

    int width = int(source.width());
    int height = int(source.height());

    int x = int(current.x);
    int y = int(current.y);

    if(x+1 < width && calculateDelta(*pixel, source.getPixel(x+1, y)) < tolerance){
        var->add(Point(x+1, y));
    }
    if(y+1 < height && calculateDelta(*pixel, source.getPixel(x, y+1)) < tolerance){
        //cout<<x<<y+1<<endl;
        var->add(Point(x, y+1));
    }
    if(x-1 >= 0 && calculateDelta(*pixel, source.getPixel(x-1, y)) < tolerance){
        var->add(Point(x-1, y));
    }
    if(y-1 >= 0 && calculateDelta(*pixel, source.getPixel(x, y-1)) < tolerance){
        var->add(Point(x, y-1));
    }
    if(var->empty()){
        var = NULL;
    }
    return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
    return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
    if(var != NULL)
        return true;
    return false;
}

