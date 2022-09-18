/*
 * Example programme for using this lib
 *
 * Author: Denisovich
 * Links: denisovichdev.github.io/link-tree
 *
 */

#include "bmp.h"

int main() {
    DIBHeader DIBInfoHeader;
    unsigned char* pixelArray;

    pixelArray = loadBMP("./an_example.bmp", &DIBInfoHeader);

    int w = DIBInfoHeader.imgWidth, h = DIBInfoHeader.imgHeight;
    const unsigned int nPix = w * h;  // number of pixels
    color* colBuff[nPix];             // Buffer of color data

    getBufferArray(pixelArray, DIBInfoHeader.imageSizeBytes, nPix, colBuff);

    return 0;
}
