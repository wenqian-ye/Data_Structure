/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */


#ifndef IMAGE_H_
#define IMAGE_H_
#include "cs225/PNG.h"
using namespace std;
using namespace cs225;
//A subclass of PNG with more member functions for modifying the image.
class Image: public PNG{
public:

    /**
     *
     * Lighten an Image by increasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1]
     */
    void lighten ();
    /**
     * Lighten an Image by increasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     * @param amount 
     */
    void lighten (double amount);
    /**
     *  Darken an Image by decreasing the luminance of every pixel by 0.1.
     *  This function ensures that the luminance remains in the range [0, 1].

     */
    void darken ();
    void darken (double amount);
    void saturate ();
    void saturate (double amount);
    void desaturate ();
    void desaturate (double amount);
    void grayscale ();
    void rotateColor (double degrees);
    void illinify ();
    void scale (double factor);
    void scale (unsigned w, unsigned h);



private:


};

#endif
 