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
	MultiMaterial(const Vector4& ambient = Vector4(0)) : ambient_(ambient) { }
	virtual ~MultiMaterial();

	virtual void PreCalc() {}
    virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const;
	virtual float GetTranslucency() const;

	void AddMaterial(Material* material) { materials_.push_back( material ); }
	void SetAmbient(const Vector4& ambient) { ambient_ = ambient; }
	const Vector4& GetAmbient() const { return ambient_; }
	

private:
	std::vector<Material*> materials_;
	Vector4 ambient_;

	DISALLOW_COPY_CONSTRUCTORS(MultiMaterial);

}; // class MultiMaterial


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_MULTI_MATERIAL_H
