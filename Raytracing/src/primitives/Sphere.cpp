#include "../../headers/primitives/Sphere.h"
#include "../../headers/math/Constants.h"
#include <xmmintrin.h>

std::string Sphere::type() const
{
	return "\"Sphere\"";
}

Sphere::Sphere(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

Sphere::Sphere(const Matrix & m) : Object(m)
{}

__m128 _mm_hadd_ps(const __m128 value)
{
	const __m128 inversedValue = _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 1, 2, 3));
	const __m128 firstAdditionCouple = _mm_add_ps(value, inversedValue);

	const __m128 inversedSecondCouple =
		_mm_shuffle_ps(firstAdditionCouple, firstAdditionCouple, _MM_SHUFFLE(2, 3, 0, 1));
	return _mm_add_ps(firstAdditionCouple, inversedSecondCouple);
}


bool Sphere::intersect(const Ray& ray, Point& impact) const {
	const Ray localRay = this->globalToLocal(ray);
	const __m128 origin = { localRay.origin[0],localRay.origin[1], localRay.origin[2], 0 };
	const __m128 vector = { localRay.vector[0],localRay.vector[1], localRay.vector[2], 0 };

	const __m128 negativeOne = _mm_set_ss(-1);
	const __m128 zero = _mm_setzero_ps();

	__m128 c = _mm_hadd_ps(_mm_mul_ps(origin, origin));
	
	c = _mm_add_ss(c, negativeOne);



	const float cEqual0Condition = _mm_cvtss_f32(_mm_cmpeq_ss(c, zero));
	if (cEqual0Condition != 0) //maybe remove condition to not get out of simd
	{
		impact = ray.origin;
		return true;
	}

	const __m128 a = _mm_hadd_ps(_mm_mul_ps(vector,vector));
	
	__m128 b = _mm_hadd_ps(_mm_mul_ps(vector, origin));
	
	__m128 times2 = _mm_set_ss(2);

	b = _mm_mul_ss(b, times2);
	__m128 four = _mm_set_ss(4);
	__m128 delta1 = _mm_mul_ss(b, b);
	__m128 delta2 = _mm_mul_ss(a, c);
	delta2 = _mm_mul_ss(delta2, four);
	
	const __m128 delta = _mm_sub_ss(delta1, delta2);

	const float deltaSmallerThan0Condition = _mm_cvtss_f32(_mm_cmplt_ss(delta, zero));
	if (deltaSmallerThan0Condition != 0)
	{
		return false;
	}

	__m128 t;
	const __m128 minusB = _mm_mul_ss(b, negativeOne);
	const __m128 sqrtDelta = _mm_sqrt_ss(delta);
	__m128 twoA = _mm_set_ss(2);
	twoA = _mm_mul_ss(a, twoA);

	const float deltaGreaterThan0Condition = _mm_cvtss_f32(_mm_cmpgt_ss(delta, zero));
	if (deltaGreaterThan0Condition != 0)
	{

		t = _mm_sub_ss(minusB, sqrtDelta);
		t = _mm_div_ss(t, twoA);
		const float tLowerThan0Condition = _mm_cvtss_f32(_mm_cmple_ss(t, zero));
		if (tLowerThan0Condition != 0)
		{
			t = _mm_add_ss(minusB, sqrtDelta);
			t = _mm_div_ss(t, twoA);
			const float tLowerThan0Condition2 = _mm_cvtss_f32(_mm_cmple_ss(t, zero));
			if (tLowerThan0Condition2 != 0)
			{
				return false;
			}
		}
	}
	else
	{
		t = _mm_div_ss(minusB, twoA);
	}

	__m128 impactM128 = _mm_shuffle_ps(t, t, _MM_SHUFFLE(0, 0, 0, 0)); 
	impactM128 = _mm_mul_ps(vector, impactM128);
	impactM128 = _mm_add_ps(origin, impactM128);
	float* impactFloat = new float[4];
	_mm_store_ps(impactFloat,impactM128); //((float*)(&t));

	impact[0] = impactFloat[0];// localRay.origin[0] + localRay.vector[0] * tFloat;
	impact[1] = impactFloat[1];// localRay.origin[1] + localRay.vector[1] * tFloat;
	impact[2] = impactFloat[2];// localRay.origin[2] + localRay.vector[2] * tFloat;
	
	impact = this->localToGlobal(impact);

	return true;

}

Ray Sphere::getNormal(const Point& impact, const Point& observator) const
{
	const Point i = this->globalToLocal(impact);
	const Point p = this->globalToLocal(observator);
	const float distance = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];

	return Ray(impact, (distance < 1 ? -1 : 1) * Vector(i).normalized());
}

Point Sphere::getTextureCoordinates(const Point& p) const
{
	Point coord = globalToLocal(p);
	Point lp = globalToLocal(p);
	float rho = std::sqrt(Point::dot(lp, lp));
	float theta = std::atan2(lp[1], lp[0]);
	float sigma = std::acos(lp[2] / rho);
	float x = -theta / (2 * PI) + 0.5;
	float y = sigma / PI;
	return Point(x, y, 0);

}
