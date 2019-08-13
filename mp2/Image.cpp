#include "Image.h"
#include "cs225/PNG.h"
using namespace std;
using namespace cs225;
void Image::lighten(){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(getPixel(j,i).l <= 0.9)
                this->getPixel(j,i).l = this->getPixel(j,i).l + 0.1;
            else
                this-> getPixel(j,i).l = 1;
        }
    }
}

void Image::lighten(double amount){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            this->getPixel(j,i).l = this->getPixel(j,i).l + amount;
            if(getPixel(j,i).l > 1)
                this->getPixel(j,i).l = 1;
            if(getPixel(j,i).l < 0)
                this->getPixel(j,i).l = 0;
        }
    }
}

void Image::darken(){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(getPixel(j,i).l >= 0.1)
                getPixel(j,i).l = getPixel(j,i).l - 0.1;
            else
                getPixel(j,i).l = 0;
        }
    }
}

void Image::darken(double amount){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            getPixel(j,i).l = getPixel(j,i).l - amount;
            if(getPixel(j,i).l < 0)
                getPixel(j,i).l =0;
            if(getPixel(j,i).l > 1)
                getPixel(j,i).l = 1;
        }
    }
}

void Image::saturate(){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(getPixel(j,i).s <= 0.9)
                getPixel(j,i).s = getPixel(j,i).s + 0.1;
            else
                getPixel(j,i).s = 1;
        }
    }
}

void Image::saturate(double amount){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            this->getPixel(j,i).s = this->getPixel(j,i).s + amount;
            if(this->getPixel(j,i).s > 1)
                this->getPixel(j,i).s = 1;
            if(this->getPixel(j,i).s <0)
                this->getPixel(j,i).s = 0;
        }
    }
}

void Image::desaturate(){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(this->getPixel(j,i).s >= 0.1)
                this->getPixel(j,i).s = this->getPixel(j,i).s - 0.1;
            else
                this->getPixel(j,i).s = 0;
        }
    }
}

void Image::desaturate(double amount){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            this->getPixel(j,i).s = this->getPixel(j,i).s - amount;
            if(this->getPixel(j,i).s < 0)
                this->getPixel(j,i).s =0;
            if(this->getPixel(j,i).s > 1)
                this->getPixel(j,i).s =1;
        }
    }
}

void Image::grayscale(){
    unsigned width =(*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            this->getPixel(j,i).s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            this->getPixel(j,i).h = this->getPixel(j,i).h + degrees;
            if(this->getPixel(j,i).h > 360)
                this->getPixel(j,i).h = this->getPixel(j,i).h - 360;
            if(this->getPixel(j,i).h <0)
                this->getPixel(j,i).h = this->getPixel(j,i).h + 360;
        }
    }
}

void Image::illinify(){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            HSLAPixel pixel = this->getPixel(j,i);
            double h = pixel.h;
            if ( h > 11 && h < 216 )
            {
                if ( h-11 > 216 - h )
                    pixel.h = 216;
                else pixel.h = 11;
            }
            else if ( h < 11 )
            {
                if ( 11 - h < 360 + h - 216 )
                    pixel.h = 11;
                else pixel.h = 216;
            }
            else if ( h > 216 )
            {
                if ( h - 216 > 360 + 11 - h )
                    pixel.h = 11;
                else pixel.h = 216;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned width = (*this).width();
    unsigned height = (*this).height();
    unsigned int newWidth = width * factor;
    unsigned int newHeight = height * factor;
    double m = width / (double)(newWidth);
    Image* temp = new Image();
    temp->resize(newWidth,newHeight);
    for(unsigned int i = 0; i < newWidth; i++){
        for(unsigned int j = 0; j < newHeight; j++){
            unsigned int newPixelW = (int)(m * i);
            unsigned int newPixelH = (int)(m * j);
            temp->getPixel(i,j) = this->getPixel(newPixelW,newPixelH);
        }
    }
    this->resize(newWidth, newHeight);
    for(unsigned int i = 0; i <newWidth; i++){
        for(unsigned int j = 0; j < newHeight; j++){
            this->getPixel(i,j) = temp->getPixel(i,j);
        }
    }
    delete temp;
}

void Image::scale(unsigned w, unsigned h){
    unsigned width = (*this).width();
    unsigned height =(*this).height();
    double mW = width / (double)(w);
    double mH = height / (double)(h);
    Image* temp = new Image();
    temp->resize(w,h);
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            unsigned int newPixelW = (int)(mW * i);
            unsigned int newPixelH = (int)(mH * j);
            temp->getPixel(i,j) = this->getPixel(newPixelW,newPixelH);
        }
    }
    this->resize(w, h);
    for(unsigned int i = 0; i < w; i++){
        for(unsigned int j = 0; j < h; j++){
            this->getPixel(i,j) = temp->getPixel(i,j);
        }
    }
    delete temp;
}