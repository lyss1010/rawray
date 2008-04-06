// Including stdafx makes errors with alloc calls
#ifdef _USRDLL
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

namespace rawray {

void ConfigParser(const char* filename);

} // namespace rawray
