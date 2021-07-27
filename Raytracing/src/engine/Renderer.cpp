#include "../../headers/engine/Renderer.h"

#include <thread>

Renderer::Renderer(const RendererProperties& properties) : _properties(properties) {}

Renderer& Renderer::setProperties(const RendererProperties& properties) {
	this->_properties = properties;
	return (*this);
}

Image Renderer::render() const {
	Image image(this->_properties.width, this->_properties.height, 3);
	const Color background = this->_properties.scene->getBackground();
	const float floatedWidth = float(this->_properties.width);
	const float floatedHeight = float(this->_properties.height);

	const int totalSubdivisions = this->_properties.ssaaSubdivisions * this->_properties.ssaaSubdivisions;
	const float floatedSubdivision = float(this->_properties.ssaaSubdivisions);

	Point impact;
	Color color;
	std::shared_ptr<Object> closest;

	for (int y = 0; y < this->_properties.height; ++y) {
		const float floatedNormalizedY = float(y) / floatedHeight;

		for (int x = 0; x < this->_properties.width; ++x) {
			float r = 0;
			float g = 0;
			float b = 0;

			for (int subY = 0; subY < this->_properties.ssaaSubdivisions; ++subY) {
				const float floatedNormalizedSubY = floatedNormalizedY + float(subY) / floatedSubdivision / floatedHeight;

				for (int subX = 0; subX < this->_properties.ssaaSubdivisions; ++subX) {
					const Ray cameraRay = this->_properties.camera->getRay(
						float(x + float(subX) / floatedSubdivision) / floatedWidth,
						floatedNormalizedSubY
					);

					closest = this->_properties.scene->closestIntersected(cameraRay, impact);
					color = closest ? getImpactColor(cameraRay, closest, impact) : this->_properties.camera->getSkyboxColor(cameraRay);

					r += color[0];
					g += color[1];
					b += color[2];
				}
			}

			color[0] = r / totalSubdivisions;
			color[1] = g / totalSubdivisions;
			color[2] = b / totalSubdivisions;
			image.setColor(x, this->_properties.height - y - 1, color);
		}
	}

	return image;
}

Color Renderer::getImpactColor(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact) const
{
	const Material mat = obj->getMaterial(impact);
	const Vector normal = obj->getNormal(impact, ray.origin).vector;
	Color sum = mat.ka * this->_properties.scene->getAmbient();

	const auto ref = obj.get();
	static Point dummy;

	for (const auto l : this->_properties.scene->getLights()) {

		if (!this->_properties.enableShadows || this->_properties.scene->closestIntersected(l->getRayFromLight(impact), dummy).get() == ref)

			switch (this->_properties.illumination)
			{
			case Illumination::LAMBERT:
				sum += l->getIlluminationLambert(impact, normal, ray, mat); break;
			default:
				sum += l->getIlluminationPhong(impact, normal, ray, mat); break;
			}
	}

	return sum;
}
