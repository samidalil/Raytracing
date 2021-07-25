#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include <chrono>
#include <iostream>
#include <memory>

#include "../image/Image.h"

class Texture {
private:
	void copy(const Texture& t);
public:
	std::chrono::milliseconds id;
	std::shared_ptr<Image> texture;
	std::string path;

	Texture();
	Texture(const std::string& path);
	Texture& operator=(const Texture& t);

	friend std::ostream& operator<<(std::ostream& os, const Texture& t);
};
#endif
