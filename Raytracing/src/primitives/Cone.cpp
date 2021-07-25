#include "../../headers/primitives/Cone.h"

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

	*/

	Ray r = globalToLocal(ray).normalized();

	Vector Va = Vector(0, 1, 0).normalized();
	float alpha = 0.95f;
	float A = Vector::dot(r.vector, Va) * Vector::dot(r.vector, Va) - alpha * alpha; 
	float B = 2. * (Vector::dot(r.origin, Va) - Vector::dot(r.vector, r.origin) * alpha * alpha);
	float C = Vector::dot(r.origin, Va) * Vector::dot(r.origin, Va) - Vector::dot(r.origin, r.origin) * alpha * alpha;

	float delta = B * B - 4. * A * C;
	if (delta < 0.0001f) return false;

	float sqrtDelta = sqrt(delta);
	float t1 = (-B - sqrtDelta) / (2. * A);
	float t2 = (-B + sqrtDelta) / (2. * A);

	float t = t1;
	if (t < 0. || t2 > 0. && t2 < t) t = t2;
	if (t < 0.) return false;

	Point p = r.origin + t * r.vector;
	impact = localToGlobal(p);
	return true;
}

Ray Cone::getNormal(const Point& impact, const Point& observator) const
{
	//TODO maybe do backface? 
	return Ray(impact, this->localToGlobal(Vector(0, 0, this->globalToLocal(observator)[2] < 0 ? -1 : 1)));
}

Point Cone::getTextureCoordinates(const Point& p) const
{
	Point lp = globalToLocal(p);
	return Point(lp[0] / 2 + 0.5, lp[1] / 2 + 0.5, 0.0);
}
