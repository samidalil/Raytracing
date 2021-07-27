#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Entity.h"
#include "Ray.h"
#include "../math/Vector.h"
#include "../texture/Material.h"
#include "../../headers/primitives/Sphere.h"

class Camera : public Entity {
private:
	float _focal;
	std::shared_ptr<Sphere> _skybox;
	void copy(const Camera& c);
protected:
	std::string type() const override;
public:
	Camera();
	Camera(float focal);
	Camera(Vector position, Vector rotation);
	Camera(float focal, Vector position, Vector rotation);
	Camera(const Camera& c);
	Camera& operator=(const Camera& c);

	Ray getRay(float x, float y) const;
	void setSkybox(const std::shared_ptr<Material>& material);
	Color getSkyboxColor(const Ray& ray);
};

#endif
