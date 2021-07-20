#ifndef RT_IMAGE_H
#define RT_IMAGE_H

#include <stdint.h>
#include <string>
#include "../texture/Color.h"

class Image {
private:
	// Cette variable indique qu'il faut lib�rer
	// la m�moire de l'image du c�t� de la lib stbi
	bool _loaded = false;

	// Longueur, hauteur et nombre de canaux de l'image
	int _width;
	int _height;
	int _channels;

	// Taille totale de l'image, utilis�e pour v�rifier que les index
	// d'acc�s au tableau de donn�es ne d�passent pas de sa taille
	size_t _size;

	// Tableau des donn�es de l'image
	// Pour acc�der au canal n du pixel de coordonn�es (x, y),
	// on acc�de � la case (y * _width + x) * _channels + c
	uint8_t* _data = NULL;

	void copy(const Image& original);
	void destroy();
public:
	Image();
	Image(const std::string& fileName);
	Image(int width, int height, int channels);
	Image(const Image& original);
	Image& operator=(const Image& original);
	~Image();

	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
	inline int getChannels() const { return _channels; }
	inline size_t getSize() const { return _size; }

	Image& setColor(int x, int y, const Color& c);

	uint8_t operator()(int x, int y, int c) const;
	uint8_t& operator()(int x, int y, int c);

	bool save(const std::string& fileName);
};

#endif
