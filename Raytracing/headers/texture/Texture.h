#ifndef RT_TEXTURE_H
#define RT_TEXTURE_H

#include <chrono>
#include <iostream>
#include <memory>

#include "../image/Image.h"
#include "../helpers/IdGenerator.h"
class Texture {
private:
	void copy(const Texture& t);
	static IdGenerator idGenerator;
public:
	int id;
	std::shared_ptr<Image> image;
	std::string path;

	Texture() = delete;
	Texture(const std::string& path);
	Texture(const std::string& path, int id);
	Texture& operator=(const Texture& t);

	friend std::ostream& operator<<(std::ostream& os, const Texture& t);
};
#endif
