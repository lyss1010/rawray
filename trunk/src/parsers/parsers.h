// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PARSERS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PARSERS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PARSERS_EXPORTS
#define PARSERS_API __declspec(dllexport)
#else
#define PARSERS_API __declspec(dllimport)
#endif

// This class is exported from the parsers.dll
class PARSERS_API Cparsers {
public:
	Cparsers(void);
	// TODO: add your methods here.
};

extern PARSERS_API int nparsers;

PARSERS_API int fnparsers(void);
