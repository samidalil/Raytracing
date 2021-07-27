#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Entity.h"
#include "Ray.h"
#include "../math/Vector.h"
#include "../engine/Skybox.h"
#include "../texture/Material.h"

class Camera : public Entity {
private:
	float _focal;
	Skybox* _skybox;
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
	void setSkybox(std::shared_ptr<Material> material);
};

#endif
