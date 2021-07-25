#include "..\..\headers\helpers\IdGenerator.h"

int IdGenerator::getId()
{
	return ++this->_count;
}
