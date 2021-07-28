#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../headers/image/Image.h"
#include "../../headers/image/stb_image.h"
#include "../../headers/image/stb_image_write.h"
#include "../../headers/math/Constants.h"

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

// Coordonnées u et v entre 0 et 1
// recalibrées par rapport à la taille de l'image
// pour obtenir la couleur du pixel
Color Image::getColor(float u, float v) const
{
	int w = u * (this->_width - 1);
	int h = v * (this->_height - 1);
	int index = (w + (h * this->_width)) * this->_channels;

	return Color(
		this->_data[index] / 255.f,
		this->_data[index + 1] / 255.f,
		this->_data[index + 2] / 255.f
	);
}

void Image::linear2sRGB()
{
	for (int j = 0; j < this->_height; j++)
	{
		for (int i = 0; i < this->_width; i++)
		{
			int index = (i + (j * this->_width)) * this->_channels;

			this->_data[index] = (uint8_t)(255.999f * pow(this->_data[index] / 255.999f, GAMMA));
			this->_data[index + 1] = (uint8_t)(255.999f * pow(this->_data[index + 1] / 255.999f, GAMMA));
			this->_data[index + 2] = (uint8_t)(255.999f * pow(this->_data[index + 2] / 255.999f, GAMMA));
		}
	}
}

void Image::sRGB2Linear()
{
	for (int j = 0; j < this->_height; j++)
	{
		for (int i = 0; i < this->_width; i++)
		{
			Color c = this->getColor(i, j);
			this->setColor(i,j,Color(pow(c[0],1.f/GAMMA),pow(c[1], 1.f / GAMMA),pow(c[2], 1.f / GAMMA)));
		}
	}
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
	this->linear2sRGB();
	return stbi_write_jpg(fileName.c_str(), _width, _height, _channels, _data, 100) != 0;
}
