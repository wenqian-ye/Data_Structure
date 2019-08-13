#include "Image.h"
#include "StickerSheet.h"


using namespace std;
using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_stickers = max;
    stickers = new Image* [max];
    base = new Image();
    x = new unsigned[max];
    y = new unsigned[max];
    for(unsigned i = 0; i < max; i++){
        stickers[i] = NULL;
        x[i] = 0;
        y[i] = 0;
    }

    *base = picture;
    count = 0;
}

StickerSheet::~StickerSheet(){
    _destroy();
}

StickerSheet::StickerSheet(const StickerSheet &other){
    _copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
    if(this != &other){
        _destroy();
        _copy(other);

    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max >= max_stickers){
        Image **temp_s = new Image* [max];
        unsigned *nx = new unsigned[max];
        unsigned *ny = new unsigned[max];
        Image *tbase = new Image();
        *(tbase) = *(base);
        for(unsigned i = 0; i< max; i++){
            temp_s[i] = NULL;
            nx[i] = 0;
            ny[i] = 0;
        }
        for(unsigned i = 0; i < max_stickers; i++){
            if(stickers[i] != NULL){
                temp_s[i] = new Image();
                *(temp_s[i]) = *(stickers[i]);
                //temp_s[i] = stickers[i];
                nx[i] = x[i];
                ny[i] = y[i];
            }
        }
        _destroy();
        max_stickers = max;
        stickers = temp_s;
        base = tbase;
        x = nx;
        y = ny;
    }
    else if(max < max_stickers && max != 0){
        Image **temp_s = new Image* [max];
        unsigned *nx = new unsigned[max];
        unsigned *ny = new unsigned[max];
        Image *tbase = new Image();
        *(tbase) = *(base);
        for(unsigned i = 0; i< max; i++){
            temp_s[i] = NULL;
            nx[i] = 0;
            ny[i] = 0;
        }
        for(unsigned i = 0; i < max; i++){
            if(stickers[i] != NULL){
                temp_s[i] = new Image();
                *(temp_s[i]) = *(stickers[i]);

                nx[i] = x[i];
                ny[i] = y[i];
            }
        }
        _destroy();
        stickers = temp_s;
        max_stickers = max;
        base = tbase;
        x = nx;
        y = ny;
        count = max;

    }
    else if(max == 0){
        max_stickers = 0;
        count = 0;
        _destroy();
        return;
    }
}

int StickerSheet::addSticker(Image &sticker, unsigned p, unsigned q){
    if(count >= max_stickers){
        return -1;
    }
    else{
        for(unsigned i = 0; i < max_stickers; i++){
            if(stickers[i] == NULL){
                Image *temp = new Image();
                *temp = sticker;
                stickers[i] = temp;
                //*(stickers[i]) = sticker;
                x[i] = p;
                y[i] = q;
                count++;
                return i;
            }
        }
        return -1;

    }
}

bool StickerSheet::translate(unsigned index, unsigned p, unsigned q){
    if(index >= max_stickers || stickers[index] == NULL){
        return 0;
    }
    else{
        x[index] = p;
        y[index] = q;
        return 1;
    }
}

void StickerSheet::removeSticker(unsigned index){
    if(index >= max_stickers || stickers[index] == NULL){
        //cout<<"invalid index"<<endl;
        return;
    }
    else{
        delete stickers[index];
        stickers[index] = NULL;
        x[index] = 0;
        y[index] = 0;
        count--;
    }


}


Image *StickerSheet::getSticker(unsigned index)const{
    if(index >= max_stickers || stickers[index] == NULL){
        return NULL;
    }
    else{
        return stickers[index];
    }
}
Image StickerSheet::render()const{
    //Image *pic = new Image();
    Image pic;
    unsigned max_x = base->width();
    unsigned max_y = base->height();
    for(unsigned i = 0; i < max_stickers; i++){
        if(stickers[i] != NULL){
            if(max_x < stickers[i]->width() + x[i]){
                max_x = stickers[i]->width() + x[i];
            }
            if(max_y < stickers[i]->height() + y[i]){
                max_y = stickers[i]->height() + y[i];
            }
        }
    }
    pic.resize(max_x, max_y);
    for(unsigned i = 0; i < base->width(); i++){
        for(unsigned j = 0; j < base->height(); j++){
            pic.getPixel(i,j) = base->getPixel(i,j);
        }
    }
    for(unsigned i = 0; i < max_stickers; i++){
        if(stickers[i] == NULL){
            continue;
        }
        else{
            for(unsigned a = 0; a < stickers[i]->width(); a++){
                for(unsigned b = 0; b < stickers[i]->height(); b++){
                    if(stickers[i]->getPixel(a,b).a != 0){
                        pic.getPixel(x[i]+a, y[i]+b) = stickers[i]->getPixel(a,b);
                    }
                }
            }

        }
    }
    //return *pic;
    return pic;
}

void StickerSheet::_copy(const StickerSheet &other){
    max_stickers = other.max_stickers;
    stickers = new Image* [max_stickers];
    x = new unsigned[max_stickers];
    y = new unsigned[max_stickers];
    for(unsigned i = 0; i < other.max_stickers; i++){
        stickers[i] = NULL;
        x[i] = 0;
        y[i] = 0;
    }
    for(unsigned i = 0; i < other.max_stickers; i++){
        if(other.stickers[i] != NULL){
            stickers[i] = new Image();
            *(stickers[i]) = *(other.stickers[i]);

            x[i] = other.x[i];
            y[i] = other.y[i];
        }
    }
    base = new Image();
    *base = *(other.base);
    count = other.count;
}

void StickerSheet::_destroy(){
    for(unsigned i = 0; i < max_stickers; i++){
        delete stickers[i];
        stickers[i] = NULL;
    }
    delete[] stickers;
    stickers = NULL;
    delete base;
    base = NULL;
    delete[] x;
    x = NULL;
    delete[] y;
    y = NULL;
}