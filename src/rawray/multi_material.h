/////////////////////////////////////////////////////////////////////////////
// Class : multi_material.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_MULTI_MATERIAL_H
#define RAWRAY_RAWRAY_MULTI_MATERIAL_H
#include "stdafx.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"
#include "material.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport MultiMaterial : public Material
{
public:
	MultiMaterial(const Vector3& ambient = Vector3(0.0f)) : ambient_(ambient) { }
	virtual ~MultiMaterial();

	virtual void PreCalc() {}
    virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const;
	virtual Vector3 BaseColor() const;

	void AddMaterial(Material* material) { materials_.push_back( material ); }
	void SetAmbient(const Vector3& ambient) { ambient_ = ambient; }
	const Vector3& GetAmbient() const { return ambient_; }

private:
	std::vector<Material*> materials_;
	Vector3 ambient_;

	DISALLOW_COPY_CONSTRUCTORS(MultiMaterial);

}; // class MultiMaterial


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_MULTI_MATERIAL_H
