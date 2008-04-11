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

void AddTrianglesOfMesh();
void SetConfigSources(Scene* scene, Camera* cam, Image* img);
bool ConfigParser(const char* filename);

} // namespace rawray
