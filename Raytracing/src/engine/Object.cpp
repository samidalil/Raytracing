#include "../../headers/engine/Object.h"

Object::Object(Vector position, Vector rotation, float scale) : Entity(position, rotation, scale) {}

Material Object::getMaterial(const Point& impact) const {
	return Material({ 1, 1, 1 }, { 0.2, 0.2, 0.2 }, { 0.7, 0.7, 0.7 }, 0.7);
}
