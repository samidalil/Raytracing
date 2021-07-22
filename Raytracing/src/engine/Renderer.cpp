#include "../../headers/engine/Renderer.h"

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
			Ray cameraRay = this->_properties.camera->getRay(float(x) / floatedWidth, floatedNormalizedY);
			closest = this->_properties.scene->closestIntersected(cameraRay, impact);

			if (closest) {
				color = getImpactColorPhong(cameraRay, closest, impact);
				float r = color[0];
				float g = color[1];
				float b = color[2];

				for (int subY = 0; subY < this->_properties.ssaaSubdivisions; ++subY) {
					const float floatedNormalizedSubY = floatedNormalizedY + float(subY) / floatedSubdivision / floatedHeight;

					for (int subX = 0; subX < this->_properties.ssaaSubdivisions; ++subX) {
						if (subX == 0 && subY == 0) continue;

						cameraRay = this->_properties.camera->getRay(
							float(x + float(subX) / floatedSubdivision) / floatedWidth,
							floatedNormalizedSubY
						);
						closest = this->_properties.scene->closestIntersected(cameraRay, impact);

						if (closest) {
							color = getImpactColorPhong(cameraRay, closest, impact);
							r += color[0];
							g += color[1];
							b += color[2];
						}
					}
				}

				color[0] = r / totalSubdivisions;
				color[1] = g / totalSubdivisions;
				color[2] = b / totalSubdivisions;
				image.setColor(x, this->_properties.height - y - 1, color);
			}
			else image.setColor(x, this->_properties.height - y - 1, background);
		}
	}

	return image;
}

Color Renderer::getImpactColorUnlit(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact) const {
	return obj->getMaterial(impact).ka * this->_properties.scene->getAmbient();
}

Color Renderer::getImpactColorLambert(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact) const {
	const Material mat = obj->getMaterial(impact);
	const Vector normal = obj->getNormal(impact, ray.origin).vector;
	Color sum = mat.ka * this->_properties.scene->getAmbient();

	// TD : remplacer par un std::for_each ou autre
	for (const auto l : this->_properties.scene->getLights())
		sum += l->getIlluminationLambert(impact, normal, ray, mat);
	return sum;
}

Color Renderer::getImpactColorPhong(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact) const {
	const Material mat = obj->getMaterial(impact);
	const Vector normal = obj->getNormal(impact, ray.origin).vector;
	Color sum = mat.ka * this->_properties.scene->getAmbient();
	auto ref = obj.get();
	static Point dummy;

	// TD : remplacer par un std::for_each ou autre
	for (const auto l : this->_properties.scene->getLights()) {
		const Ray r = l->getRayToLight(impact);
		bool illuminated = true;

		for (const auto o : this->_properties.scene->getObjects())
			if (o.get() != ref && o->intersect(r, dummy)) {
				illuminated = false;
				break;
			}

		if (illuminated)
			sum += l->getIlluminationPhong(impact, normal, ray, mat);
	}
	return sum;
}
