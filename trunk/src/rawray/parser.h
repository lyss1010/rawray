#ifndef RAWRAY_PARSER_H_
#define RAWRAY_PARSER_H_

// Including stdafx makes errors with alloc calls
#ifdef _USRDLL
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif


namespace rawray {

class Scene;
class Camera;
class Image;
class Material;

void AddTrianglesOfMesh();
void SetConfigSources(Scene* scene, Camera* cam, Image* img);
bool ConfigParser(const char* filename);
void DoneParsing();
void AddMaterial(Material* material);

} // namespace rawray

#endif // RAWRAY_PARSER_H_