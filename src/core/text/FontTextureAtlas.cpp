//
// Created by montgomery anderson on 18/07/17.
//

#include "FontTextureAtlas.h"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iostream>

#define MAX_WIDTH 1024


FontTextureAtlas::FontTextureAtlas(FT_Face face, int h) {
    FT_Set_Pixel_Sizes(face, 0, h);
    FT_GlyphSlot glyphSlot = face->glyph;

    int rowWidth = 0;
    int rowHeight = 0;
    width = 0;
    height = 0;

    // Preallocate the memory.
    memset(characters, 0, sizeof(FontChar));

    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
            throw std::runtime_error("FT_Load_Char failed.");

        if (rowWidth + glyphSlot->bitmap.width + 1 >= MAX_WIDTH) {
            width = std::max<int>(width, rowWidth);
            height += rowHeight;
            rowWidth = 0;
            rowHeight = 0;
        }

        rowWidth += glyphSlot->bitmap.width + 1;
        rowHeight = std::max<int>(rowHeight, glyphSlot->bitmap.rows);
    }

    width = std::max<int>(width, rowWidth);
    height += rowHeight;


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int ox = 0;
    int oy = 0;
    rowHeight = 0;

    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
            throw std::runtime_error("FT_Load_Char failed.");

        if (ox + glyphSlot->bitmap.width + 1 >= MAX_WIDTH) {
            oy += rowHeight;
            rowHeight = 0;
            ox = 0;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyphSlot->bitmap.buffer);

        characters[i].advanceX = glyphSlot->advance.x >> 6;
        characters[i].advanceY = glyphSlot->advance.y >> 6;

        characters[i].bitmapWidth = glyphSlot->bitmap.width;
        characters[i].bitmapHeight = glyphSlot->bitmap.rows;

        characters[i].height = glyphSlot->metrics.height >> 6;

        characters[i].bitmapLeft = glyphSlot->bitmap_left;
        characters[i].bitmapTop = glyphSlot->bitmap_top;

        characters[i].uvOffsetX = ox / (float)width;
        characters[i].uvOffsetY = oy / (float)height;

        rowHeight = std::max<int>(rowHeight, glyphSlot->bitmap.rows);
        ox += glyphSlot->bitmap.width + 1;


    }
    std::cout << "Generated a " << width << "x" << height << " (" << width * height / 1024 << " kb) texture atlas.\n";
}


FontTextureAtlas::~FontTextureAtlas() {
    glDeleteTextures(1, &uniformTextureLocation);
}
