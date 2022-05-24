#include "misc.h"  

GLbyte* ConvertTgaToBitmap(const char* fileName, GLint
    * width, GLint* height, GLint* components,
    GLenum* format)
{
    FILE* file;
    TGA_HEADER tgaHeader;
    unsigned long imageSize;
    short depth;
    GLbyte* bits = NULL;

    *width = 0;
    *height = 0;
    *format = GL_BGR_EXT;
    *components = GL_RGB8;

    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        return NULL;
    }

    fread(&tgaHeader, 18, 1, file);

    *width = tgaHeader.width;
    *height = tgaHeader.height;
    depth = tgaHeader.bits / 8;

    if (tgaHeader.bits != 8 && tgaHeader.bits != 24 &&
        tgaHeader.bits != 32) {
        return NULL;
    }

    imageSize = tgaHeader.width * tgaHeader.height *
        depth;

    bits = (GLbyte*)malloc(imageSize * sizeof(GLbyte));
    if (bits == NULL) { return NULL; }

    if (fread(bits, imageSize, 1, file) != 1)
    {
        free(bits);
        return NULL;
    }

    switch (depth)
    {
    case 3:
        *format = GL_BGR_EXT;
        *components = GL_RGB8;
        break;
    case 4:
        *format = GL_BGRA_EXT;
        *components = GL_RGBA8;
        break;
    case 1:
        *format = GL_LUMINANCE;
        *components = GL_LUMINANCE8;
        break;
    };


    fclose(file);

    return bits;
}

GLint WriteTga(const char* szFileName)
{
    FILE* pFile;
    TGA_HEADER tgaHeader;
    unsigned long lImageSize;
    GLbyte* pBits = NULL;
    GLint iViewport[4];
    GLenum lastBuffer;
    glGetIntegerv(GL_VIEWPORT, iViewport);
    lImageSize = iViewport[2] * 3 * iViewport[3];

    pBits = (GLbyte*)malloc(lImageSize);

    if (pBits == NULL)
        return 0;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);


    glGetIntegerv(GL_READ_BUFFER,
        (GLint*)&lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, iViewport[2], iViewport[3],
        GL_BGR_EXT, GL_UNSIGNED_BYTE, pBits);
    glReadBuffer(lastBuffer);

    tgaHeader.identSize = 0;
    tgaHeader.colorMapType = 0;
    tgaHeader.imageType = 2;
    tgaHeader.colorMapStart = 0;
    tgaHeader.colorMapLength = 0;
    tgaHeader.colorMapBits = 0;
    tgaHeader.xStart = 0;
    tgaHeader.yStart = 0;
    tgaHeader.width = iViewport[2];
    tgaHeader.height = iViewport[3];
    tgaHeader.bits = 24;
    tgaHeader.descriptor = 0;

#ifdef __APPLE__
    BYTE_SWAP(tgaHeader.colorMapStart);
    BYTE_SWAP(tgaHeader.colorMapLength);
    BYTE_SWAP(tgaHeader.xstart);
    BYTE_SWAP(tgaHeader.ystart);
    BYTE_SWAP(tgaHeader.width);
    BYTE_SWAP(tgaHeader.height);
#endif
    pFile = fopen(szFileName, "wb");
    if (pFile == NULL)
    {
        free(pBits);
        return 0;
    }

    fwrite(&tgaHeader, sizeof(TGA_HEADER), 1, pFile);
    fwrite(pBits, lImageSize, 1, pFile);

    free(pBits);
    fclose(pFile);
    return 1;
}