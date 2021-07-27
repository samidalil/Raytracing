#ifndef RT_SKYBOX_H
#define RT_SKYBOX_H

#include "../primitives/Sphere.h"
#include "../texture/Material.h"

class Skybox : public Sphere {
protected:
	std::string type() const override;
public:
	Skybox() = default;
	Skybox(const Vector& position, float scale, const std::shared_ptr<Material>& material);
};

#endif
