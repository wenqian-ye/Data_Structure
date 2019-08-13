
#ifndef FLOODFILLEDIMAGE_H
#define FLOODFILLEDIMAGE_H

#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

#include <queue>

using namespace cs225;

class FloodFilledImage {
public:
    FloodFilledImage(const PNG & png);
    void addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker);
    Animation animate(unsigned frameInterval) const;

private:
    PNG myPNG;
    std::vector<ImageTraversal *> myTraversal;
    std::vector<ColorPicker *> myColor;

};

#endif