/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
using namespace cs225;

class StickerSheet{
public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    StickerSheet const & operator= (const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image *getSticker(unsigned index) const;
    Image render() const;
    unsigned getMax();
    unsigned setMax(unsigned Max);
private:
    unsigned max_stickers;
    Image **stickers;
    Image *base;
    void _copy(const StickerSheet &other);
    void _destroy();
    unsigned count;
    unsigned* x;
    unsigned* y;
    unsigned max_x;
    unsigned max_y;



};



#endif
 