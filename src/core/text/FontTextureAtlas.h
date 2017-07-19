//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_FONTTEXTUREATLAS_H
#define RECLAIMER_FONTTEXTUREATLAS_H


#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "FontChar.h"



class FontTextureAtlas {
public:
    GLuint uniformTextureLocation;

    int width;
    int height;

    FontChar characters[128];

    FontTextureAtlas(FT_Face face, int h);
    ~FontTextureAtlas();
protected:
private:
};


#endif //RECLAIMER_FONTTEXTUREATLAS_H
