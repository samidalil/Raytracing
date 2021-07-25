#include "../../headers/primitives/Cone.h"
#include "../../headers/math/Constants.h"

std::string Cone::type() const
{
	return "\"Cone\"";
}

Cone::Cone(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

bool Cone::intersect(const Ray& ray, Point& impact) const
{
	/* Cone Infini :

		 v_a = ligne verticale (normalisé) passant par l'apex

		\ | / alpha = demi angle ( angle entre v_a et l'un des côtés du cone
		 \|/
		 / \ apex = sommet du milieu
		/   \

	  Un point p(x,y,z) appartient au cone ssi :
	  cos²(alpha) * (p - apex -(v_a, p-apex)v_a²)²-sin²(alpha)(v_a, p-apex)² = 0  , où v_a et la ligne vertical passant par l'apex

	  Sur le rayon on caractérise le point cherché par p(t) = O - D*t

	  d'où on a :
	  cos²(alpha) * (D*t + O - apex -(v_a, D*t + O-apex)v_a²)²-sin²(alpha)(v_a, D*t+O-apex)² = 0

	  Ensuite resolvation de l'équation du second degré de la même manière que la sphere.

	  Ici, nous calculons pour un cone inifi d'apex centré en (0,0,0) et de alpha = 0.90

	*/

	const Ray r = this->globalToLocal(ray);

	const Vector Va(0, 1, 0);
	static const float cos2Alpha = cos(0.9f) * cos(0.9f);
	float A = Vector::dot(r.vector, Va) * Vector::dot(r.vector, Va) - cos2Alpha;
	float B = 2 * (Vector::dot(r.vector, Va) * Vector::dot(r.origin, Va) - Vector::dot(r.vector, r.origin) * cos2Alpha);
	float C = Vector::dot(r.origin, Va) * Vector::dot(r.origin, Va) - Vector::dot(r.origin, r.origin) * cos2Alpha;

	const float delta = B * B - 4. * A * C;
	if (delta < 0) return false;

	float t;
	const float sqrtDelta = sqrt(delta);
	if (delta < FLT_EPSILON) {
		t = -B / (2 * A);
	}
	else {
		t = (-B - sqrtDelta) / (2. * A);
		if (t < 0) t = (-B + sqrtDelta) / (2. * A);
	}
	if (t < 0)return false;


	Point p = r.origin + t * r.vector;

	impact = localToGlobal(p);
	return true;
}

Ray Cone::getNormal(const Point& impact, const Point& observator) const
{
	Point imp = globalToLocal(impact);
	Point obs = globalToLocal(observator);

	float distance = sqrt(pow(obs[0], 2) + pow(obs[2], 2));

	Vector dir(imp[0], 0, imp[2]);

	if (distance < 1) dir = -1 * dir;

	Ray res(impact, localToGlobal(dir));
	return res;
}

Point Cone::getTextureCoordinates(const Point& p) const
{
	Point coord = globalToLocal(p);
	return Point(1 - (atan2(coord[0], coord[2]) / (2 * PI) + 0.5), std::fmod(coord[1], 1), 0);
}
