#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp.h"

unsigned char* loadBMP(char *filename, DIBHeader *DIBitmapHeader) {
    FILE *filePtr;  
    BMPFileHeader bitmapFileHeader; 
    unsigned char* bitmapImage; 

    // Open the file in read bin mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL) {
        return NULL;
	}

    // Read the BMP header into the struct
    fread(&bitmapFileHeader, sizeof(BMPFileHeader), 1, filePtr);

    // Check if this is a BMP file with the signature
    if (bitmapFileHeader.signature !=0x4D42) {
        fclose(filePtr);
        return NULL;
    }

    // Read the DIB header into the struct
    fread(DIBitmapHeader, sizeof(DIBHeader), 1, filePtr);

	if (DIBitmapHeader->imageSizeBytes == 0) { 
		DIBitmapHeader->imageSizeBytes = 
			((DIBitmapHeader->imgHeight * DIBitmapHeader->imgWidth) * DIBitmapHeader->bitsPerPixel) / 8;
	}

    // This shifts the the file position pointer (similar to say, a cursor pointer)
	// to the beginning of the bitmap data. The bitmap data is located after the header
	// (containing all the metadata), which is of 54 bytes. However, this offset is also
	// in the bitmap header, in this case, the defined offset property.
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    // Allocate memory to save pixel array
    bitmapImage = (unsigned char*) malloc(DIBitmapHeader->imageSizeBytes);

    // Check malloc
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, DIBitmapHeader->imageSizeBytes, 1, filePtr);

    // Check if it worked
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }
	
    // BGR -> RGB
    unsigned char tempRGB;  //our swap variable
	int increment = DIBitmapHeader->bitsPerPixel / 8;
    for (int imageIdx = 0; imageIdx < DIBitmapHeader->imageSizeBytes; imageIdx += increment) {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    fclose(filePtr);
    return bitmapImage;
}

void getBufferArray(unsigned char* imageData, uint32_t size, const unsigned int bSize, color* buffer[bSize]) {
	int counter = 0;
	for (int i = 0; i < size; i += 4) {
		int r = imageData[i    ];
		int g = imageData[i + 1];
		int b = imageData[i + 2];
		int greyVal = ((float)r + (float)g + (float)b) / 3;

		color* col = (color*) malloc(sizeof(color));
		col->r = r; col->g = g; col->b = b; col->grey = greyVal;
		buffer[counter] = col;

		counter++;
	}
}
