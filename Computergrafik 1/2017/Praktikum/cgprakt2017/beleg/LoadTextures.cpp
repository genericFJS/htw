#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glew.h>
#include <FreeImage.h>

GLuint loadTextures(const char* filename, GLenum minification_filter, GLenum magnification_filter) {
	GLuint textureID;
	/* Format des Bildes */
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

	if (format == -1) {
		std::cout << "Failed to open file: " << filename << std::endl;
		exit(-1);
	}

	if (format == FIF_UNKNOWN) {
		std::cout << "File format not recognized!" << std::endl;

		format = FreeImage_GetFIFFromFilename(filename);

		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "Image could not be read!" << std::endl;
			exit(-1);
		}
	}

	//Bild in bitmap laden
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		std::cout << "Image has " << bitsPerPixel << " Bit per pixel. Skipping conversion." << std::endl;
		bitmap32 = bitmap;
	} else {
		std::cout << "Image has " << bitsPerPixel << " Bit per pixel. Converting to 32-Bit." << std::endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	//Bild Bereite und Höhe
	GLint bitmap_width = FreeImage_GetWidth(bitmap32);
	GLint bitmap_height = FreeImage_GetHeight(bitmap32);

	GLubyte* texture_data = FreeImage_GetBits(bitmap32);

	//Generiren einer Texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Erstellen der Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap_width, bitmap_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, texture_data);

	//Anpassen der Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minification_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnification_filter);

	FreeImage_Unload(bitmap32);

	if (bitsPerPixel != 32) {
		FreeImage_Unload(bitmap);
	}

	return textureID;
}