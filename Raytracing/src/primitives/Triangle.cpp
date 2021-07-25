#include "../../headers/primitives/Triangle.h"
#include "../../headers/math/Constants.h" 

Triangle::Triangle(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material) {
}

const Point Triangle::A(-1, -1, 0);
const Point Triangle::B(0, 1, 0);
const Point Triangle::C(1, -1, 0);
const Point Triangle::AB = B - A;
const Point Triangle::AC = C - A;
const Point Triangle::BC = C - B;

// MOLLER TRUMBORE 
bool Triangle::intersect(const Ray& r, Point& impact) const
{
	const Ray ray = this->globalToLocal(r);

	// Coordonnées barycentrique :
	// 
	// Soit un triangle ABC, centré en (0,0,0) dans son repère locale. Chaque point appartenant à ce triangle peuvent
	// être exprimé en coordonnées barycentrique tel que p(u,v) = u*A + v*B + (1-u-v)*C
	// 
	// Equations :
	// 
	// Un point peut également être exprimer par rapport à un rayon de centre O et de vecteur directeur D tel que :
	// p(t) = O + D*t
	// On a donc l'équation uA + vB + (1-u-v)C = O + Dt
	// Comme on cherche u v et t en fonction de ABC, on a l'équation [t,u,v] = O-A / [-D, B-A, C-A]
	// qui peut se réécrire comme le système matriciel suiant :
	// 	   [t,u,v] = | O-A, B-A, C-A | * 1 /  [-D, B-A, C-A]
	//				 | -D , O-A, C-A |	
	//				 | -D , B-A, O-A |
	// 
	// Cela peut se résoudre par la méthode de Cramer qui donne l'équation suivante :
	// 	   [t,u,v] = | det([O-A, B-A, C-A]) | * 1 /  det([-D, B-A, C-A])
	//				 | det([-D , O-A, C-A]) |	
	//				 | det([-D , B-A, O-A]) |
	// 	
	// 
	// Et on utilise le racourcis mathématique stipulant que le determinant d'une matrice à trois composants
	// est égale au produit scalaire de son premier élément et du produit en vectoriel de ses deux autres.

	const Vector p = Vector::cross(ray.vector, AC);
	const float det = Vector::dot(AB, p);

	if (det > -EPSILON && det < EPSILON) return false; // parallel

	const float invDet = 1.0 / det;
	const Vector OA = ray.origin - A;
	const float u = invDet * (Vector::dot(OA, p));

	if (u < 0.0 || u > 1.0)	return false;

	const Vector q = Vector::cross(OA, AB);
	const float v = invDet * Vector::dot(ray.vector, q);

	if (v < 0.0 || u + v > 1.0)	return false;

	const float t = invDet * Vector::dot(AC, q); // impact at t * ray.vector

	if (t > EPSILON) // front face
	{
		impact = localToGlobal(ray.origin + ray.vector * t);
		return true;
	}
	return false; // back face
}

Ray Triangle::getNormal(const Point& impact, const Point& observator) const
{
	return Ray(this->localToGlobal(Point()), this->localToGlobal(Vector::cross(AB, BC))).normalized();
}

Point Triangle::getTextureCoordinates(const Point& p) const
{
	return Point();
}
