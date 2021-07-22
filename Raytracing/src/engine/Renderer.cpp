#include "../../headers/engine/Renderer.h"

Renderer::Renderer(int width = 800, int height = 600) : _width(width), _height(height), _illumination(Illumination::PHONG) {}

Color getImpactColorPhong(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact, const Scene& scene)
{
	const Material mat = obj->getMaterial(impact);
	const Vector normal = obj->getNormal(impact, ray.origin).vector;
	Color sum = mat.ka * scene.getAmbient();

	// TD : remplacer par un std::for_each ou autre
	for (auto l : scene.getLights()) sum += l->getIlluminationPhong(impact, normal, ray, mat);
	return sum;
}

Color getImpactColorLambert(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact, const Scene& scene)
{
	const Material mat = obj->getMaterial(impact);
	const Vector normal = obj->getNormal(impact, ray.origin).vector;
	Color sum = mat.ka * scene.getAmbient();

	// TD : remplacer par un std::for_each ou autre
	for (auto l : scene.getLights()) sum += l->getIlluminationLambert(impact, normal, ray, mat);
	return sum;
}

Color getImpactColorUnlit(const Ray& ray, const std::shared_ptr<Object>& obj, const Point& impact, const Scene& scene)
{
	return obj->getMaterial(impact).ka * scene.getAmbient();
}


Image Renderer::render(const Scene& scene, const Camera& camera) const {
	Image image(this->_width, this->_height, 3);
	const Color background = scene.getBackground();

	const float floatedWidth = float(this->_width);
	const float floatedHeight = float(this->_height);

	const int subPixelNb = 8;
	const int subPixelCount = subPixelNb * subPixelNb;
	const float floatedSubPixelNb = float(subPixelNb);

	Point impact;
	Color color;

	for (int y = 0; y < this->_height; ++y) {
		const int inversedY = this->_height - y - 1;
		const float floatedNormalizedY = float(y) / floatedHeight;

		for (int x = 0; x < this->_width; ++x) {
			Ray cameraRay = camera.getRay(float(x) / floatedWidth, floatedNormalizedY);
			auto closest = scene.closestIntersected(cameraRay, impact);

			if (closest) {
				color = getImpactColorPhong(cameraRay, closest, impact, scene);
				float r = color[0];
				float g = color[1];
				float b = color[2];

				for (int subY = 0; subY < subPixelNb; ++subY) {
					const float floatedNormalizedSubY = floatedNormalizedY + float(subY) / floatedSubPixelNb / floatedHeight;

					for (int subX = 0; subX < subPixelNb; ++subX) {
						if (subX == 0 && subY == 0) continue;

						cameraRay = camera.getRay(
							float(x + float(subX) / floatedSubPixelNb) / floatedWidth,
							floatedNormalizedSubY
						);
						closest = scene.closestIntersected(cameraRay, impact);

						if (closest) {
							color = getImpactColorPhong(cameraRay, closest, impact, scene);
							r += color[0];
							g += color[1];
							b += color[2];
						}
					}
				}

				color[0] = r / subPixelCount;
				color[1] = g / subPixelCount;
				color[2] = b / subPixelCount;
				image.setColor(x, inversedY, color);
			}
			else image.setColor(x, inversedY, background);
		}
	}

	return image;
}

Renderer& Renderer::setIlluminationModel(const Illumination& illumination)
{
	this->_illumination = illumination;
	return (*this);
}
