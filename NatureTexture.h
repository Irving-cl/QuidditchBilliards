
#ifndef _NATURETEXTURE_H_
#define _NATURETEXTURE_H_

#include "stdafx.h"

/*
    NatureTexture class. This class
  generates a natrue texture by
  applying Perlin noise algorithm.
 */

class NatureTexture
{
public:
	NatureTexture();        
	~NatureTexture();

	/// Public interfaces
	void GenerateTexture();        // Generate a nature texture

	unsigned int ID;               // ID of the texture

private:
	/// Members
	int imageWidth;                // Width of the image(default 256)
	int imageHeight;               // Height of the image(default 256)
	unsigned char * image;         // Data of the image

	/// Methods of generating a texture by perlin noise
	void GenerateNoise();
	float ** GenerateWhiteNoise();
	float ** GenerateSmoothNoise(float ** baseNoise, int octaveCount);
	float ** GeneratePerlinNoise(float ** baseNoise, int octave);
	float ** MapGradient(float ** perlinNoise);
	float Interpolate(float x0, float x1, float alpha);
};

#endif // _NATURETEXTURE_H_