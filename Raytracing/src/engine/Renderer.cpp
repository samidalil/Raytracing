#include "../../headers/engine/Renderer.h"

Renderer::Renderer(int width = 800, int height = 600) : _width(width), _height(height) {}

Color getImpactColor(const Ray& ray, const Object* obj, const Point& impact, const Scene& scene)
{
	const Material mat = obj->getMaterial(impact);
	const Vector n = obj->getNormal(impact, ray.origin).vector;
	Color sum = mat.ka * scene.getAmbient();

	for (Light* l : scene.getLights())
	{
		const Vector r = l->getVectorToLight(impact);
		const float nToRAngle = Vector::dot(n, r);
		const float rToNAngle = Vector::dot(ray.vector, Vector::reflect(r, n));
		
		if (nToRAngle >= 0) sum += mat.kd * l->id * nToRAngle;
		if (rToNAngle >= 0) sum += mat.ks * l->is * pow(rToNAngle, mat.shininess);
	}

	return sum;
}

Image Renderer::render(Scene scene, Camera camera) const {
	Image image(this->_width, this->_height, 3);
	const Color& background = scene.getBackground();

	const float floatedWidth = float(this->_width);
	const float floatedHeight = float(this->_height);

	for (int y = 0; y < this->_height; ++y) {
		const int inversedY = this->_height - y - 1;
		const float floatedY = float(y);

		for (int x = 0; x < this->_width; ++x) {
			const Ray cameraRay = camera.getRay(float(x) / floatedWidth, floatedY / floatedHeight);
			Point impact;
			Object* closest = scene.closestIntersected(cameraRay, impact);

			if (closest) image.setColor(x, inversedY, getImpactColor(cameraRay, closest, impact, scene));
			else image.setColor(x, inversedY, background);
		}
	}

	return image;
}
