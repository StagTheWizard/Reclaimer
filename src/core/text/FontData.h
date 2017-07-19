//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_FONTDATA_H
#define RECLAIMER_FONTDATA_H

#include <glad/glad.h>


struct FontData {
    float height;
    GLuint *textures;
    GLuint listBase;

    void initialise(const char *fname, unsigned int height);
    void clean();
};

#endif //RECLAIMER_FONTDATA_H
