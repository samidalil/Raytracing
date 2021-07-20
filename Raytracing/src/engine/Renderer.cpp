#include "../../headers/engine/Renderer.h"

Renderer::Renderer(int width = 800, int height = 600) : _width(width), _height(height), _illuminationModel(Illumination::PHONG) {}

Color getImpactColorLambert(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene)
{
	const Material mat = obj.getMaterial(impact);
	const Vector n = obj.getNormal(impact, ray.origin).vector;
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

Color getImpactColorPhong(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene)
{
	Ray n = obj.getNormal(impact, ray.origin);
	Color ka = obj.getMaterial(impact).ka;
	Color kd = obj.getMaterial(impact).kd;
	Color ks = obj.getMaterial(impact).ks;
	Color ia = scene.getAmbient();
	Color lambert = obj.getMaterial(impact).ka;
	float shiny = obj.getMaterial(impact).shininess;
	Color ambiant = ka * ia;
	Color diffuse(0, 0, 0);
	Color specular(0, 0, 0);

	for (Light* l : scene.getLights())
	{
		Vector lightDir = l->getVectorToLight(impact);
		float cosTheta = Vector::dot(lightDir, n.vector);
		if (cosTheta < 0) cosTheta = 0;
		diffuse += (kd * l->id) * cosTheta;

		Vector sym = lightDir - 2 * (Vector::dot(lightDir, n.vector)) * n.vector;
		float cosBeta = (Vector::dot(sym, ray.vector));
		float specVal = pow(Vector::dot(ray.vector, sym), shiny);

		if (specVal < 0) specVal = 0;
		specular += (ks * l->is) * cosBeta * specVal;
	}




	return ambiant + diffuse + specular;
}
Color getImpactColorUnlit(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene)
{
	const Material mat = obj.getMaterial(impact);
	return mat.ka * scene.getAmbient();
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

			if (closest) image.setColor(x, inversedY, getImpactColorLambert(cameraRay, *closest, impact, scene));
			else image.setColor(x, inversedY, background);
		}
	}

	return image;
}

void Renderer::setIlluminationModel(Illumination illu)
{
	_illuminationModel = illu;
}
