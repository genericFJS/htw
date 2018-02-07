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
		std::cout << "Konnte Datei nicht finden: " << filename << " -Beende." << std::endl;
		exit(-1);
	}

	if (format == FIF_UNKNOWN) {
		std::cout << "Dateiformat konnte nicht erkannt werden" << std::endl;

		format = FreeImage_GetFIFFromFilename(filename);

		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "Gefundenes Bild kann nicht gelesen werden" << std::endl;
			exit(-1);
		}
	}

	//Bild in bitmap laden
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		std::cout << "Quell-Bild hat" << bitsPerPixel << "Bit pro Pixel. Überspringe Konvertierung." << std::endl;
		bitmap32 = bitmap;
	} else {
		std::cout << "Quell-Bild hat" << bitsPerPixel << "Bit pro Pixel. Konvertierung in 32-Bit Farbe" << std::endl;
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