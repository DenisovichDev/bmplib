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

    return 0;
}
