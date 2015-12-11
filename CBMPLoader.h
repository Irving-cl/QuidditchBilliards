
#ifndef _CBMPLOADER_H_
#define _CBMPLOADER_H_

#include "stdafx.h"

#define BITMAP_ID 0x4D42

/*
    CBMPLoader class, which loads
  bmp file to make textures.
 */

class CBMPLoader
{
public:
	CBMPLoader();
	~CBMPLoader();

	bool LoadBitmap(const char *filename);
	void FreeImage();
	bool Load(const char* fileName);

	unsigned int ID;
	int imageWidth;
	int imageHeight;
	unsigned char *image;
};

#endif // _CBMPLOADER_H_