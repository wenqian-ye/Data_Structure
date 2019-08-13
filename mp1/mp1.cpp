#include <cstdlib>
#include <cmath>
#include <iostream>
#include "mp1.h"

using namespace cs225;
using namespace std;

PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

void rotate(std::string inputFile, std::string outputFile) {

    PNG* original = new PNG();
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();

    PNG* output = new PNG();

    output = setupOutput(width, height);

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {

            HSLAPixel* point_curr = original->getPixel(x,y);

            HSLAPixel* point_out  = output->getPixel(width-x-1,height-y-1);

            *point_out = *point_curr;
        }
    }

    output->writeToFile(outputFile);

    delete output;
    delete original;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG* png = new PNG(width, height);
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
          HSLAPixel* point = png->getPixel(x,y);
          point->h = 360*rand();
          point->l = 0.5;
          point->a = 0.5;
          point->s = 0.2;




        }
    }
  // Part 3

  return *png;
}
