//#ifndef MyColorPicker_H
//#define MyColorPicker_H
//
//#include "ColorPicker.h"
//#include "../cs225/HSLAPixel.h"
//#include "../Point.h"
//
//using namespace cs225;
//
///**
// * A color picker class using your own color picking algorithm
// */
//class MyColorPicker : public ColorPicker {
//public:
//  HSLAPixel getColor(unsigned x, unsigned y);
//
//private:
//
//};
//
//#endif
#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

class MyColorPicker : public ColorPicker {
public:
    HSLAPixel getColor(unsigned x, unsigned y);

private:
    int t;
    int h [2] = {0,100};
};

#endif