/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.

 Your goal in this part of the MP is to make a StickerSheet composed of a collection of Images.
 To do so, you will create a class StickerSheet that will maintain an array of pointers to Image objects.
 Each Image in the Scene will have an index, an x-coordinate, and a y-coordinate.
 The member functions described below will support creating, modifying, and drawing
 the collection of Image stickers in the StickerSheet.

 To implement the StickerSheet class, you will write a header file that contains a declaration of the StickerSheet class (StickerSheet.h) and a source file that contains the implementation of the StickerSheet class (StickerSheet.cpp).
 */
#pragma once

#include "Image.h"


class StickerSheet {
public:
    StickerSheet();

   	StickerSheet(const Image &picture, unsigned max);

    ~StickerSheet();

    StickerSheet(const StickerSheet &other);

    const StickerSheet & operator=(const StickerSheet &other);

    void changeMaxStickers(unsigned max);

    int addSticker(Image &sticker, unsigned x, unsigned y);

    bool translate(unsigned index, unsigned x, unsigned y);

    void removeSticker(unsigned index);

    Image* getSticker(unsigned index);

    Image render()const;

    Image basePicture_;
    Image* stickers_;
    unsigned int maxNum_;
    unsigned int stickerCounter_ = 0;




};
