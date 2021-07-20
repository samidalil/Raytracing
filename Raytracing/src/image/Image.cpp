#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../headers/image/Image.h"
#include "../../headers/image/stb_image.h"
#include "../../headers/image/stb_image_write.h"

#include <iostream>

Image::Image() :
	_loaded(false),
	_width(0),
	_height(0),
	_channels(0),
	_size(0),
	_data(NULL)
{}

// Constructeur d'image chargée par stbi
Image::Image(const std::string& fileName) : _loaded(true)
{
	if ((_data = stbi_load(fileName.c_str(), &_width, &_height, &_channels, 0)) == NULL)
		std::cout << stbi_failure_reason() << std::endl;
	_size = _width * _height * _channels;
}

// Constructeur d'image vide Edes dimensions et nombre de canaux donnés
Image::Image(int width, int height, int channels) :
	_width(width),
	_height(height),
	_channels(channels),
	_size(_width* _height* _channels)
{
	_data = new uint8_t[_size];
}

// Constructeur par copie
Image::Image(const Image& original) { copy(original); }

// Opérateur d'affection par copie
Image& Image::operator=(const Image& original)
{
	if (this != &original)
	{
		// Destruction du contenu courant et remplacement
		// par les valeurs fournies par l'image en paramètre
		destroy();
		copy(original);
	}
	return *this;
}

// Destructeur
Image::~Image() { destroy(); }

void Image::copy(const Image& original)
{
	_loaded = false;
	_width = original._width;
	_height = original._height;
	_channels = original._channels;
	_size = original._size;
	_data = new uint8_t[_size];

	for (int i = 0; i < _size; i++)
		_data[i] = original._data[i];
}

void Image::destroy()
{
	if (_loaded) stbi_image_free(_data);
	else delete[] _data;
}

Image& Image::setColor(int x, int y, const Color& c)
{
	int index = (y * this->_width + x) * this->_channels;

	this->_data[index] = c[0] * 255.f;
	this->_data[index + 1] = c[1] * 255.f;
	this->_data[index + 2] = c[2] * 255.f;

	return (*this);
}

Color Image::getColor(float u, float v) const
{
	int w = int( u * this->_width ) ;
	int h = int( v * this->_height ) ;

	int index = h + (w * this->_width) * this->_channels;

	return Color(this->_data[index], this->_data[index + 1], this->_data[index + 2]);
}

uint8_t Image::operator()(int x, int y, int c) const
{
	return _data[(y * _width + x) * _channels + c];
}

uint8_t& Image::operator()(int x, int y, int c)
{
	return _data[(y * _width + x) * _channels + c];
}

bool Image::save(const std::string& fileName)
{
	return stbi_write_jpg(fileName.c_str(), _width, _height, _channels, _data, 100) != 0;
}
