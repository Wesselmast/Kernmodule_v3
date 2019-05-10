#pragma once
#include "ErrorHandling.h"
#include <string>

class Texture {
private:
	std::string filePath;
	unsigned int rendererID;
	unsigned char* localBuffer;
	int width, height, bpp;
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWith() const { return width; }
	inline int getHeight() const { return height; }
};