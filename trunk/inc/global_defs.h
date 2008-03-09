/////////////////////////////////////////////////////////////////////////////
// Global Definitions : global_defs.h
// Preprocessor Definitions common to solution
//
// Note: Do not put anything that depends on other files here
// those go in the StdAfx.h files of the individual project
/////////////////////////////////////////////////////////////////////////////

// If we are compiling to a DLL, this is how we export names
#ifdef _USRDLL
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif


// Tell code we're using Windows XP or later
#define CORE_WINDOWS_VERSION 0x0501
#ifndef WINVER
#define WINVER			CORE_WINDOWS_VERSION
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT	CORE_WINDOWS_VERSION
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS	CORE_WINDOWS_VERSION
#endif

// Exclude rarely-used stuff from Windows headers
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN	
#endif

// Null pointer
#ifndef NULL
#define NULL 0
#endif

// Some useful macros for safer deletion
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

// Tell the compiler we are not using a variable and don't give us a warning about it
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif

/////////////////////////////////////////////////////////////////////////////
// Common Types
/////////////////////////////////////////////////////////////////////////////
typedef unsigned char       uint8;
typedef signed char         int8;

typedef unsigned short      uint16;
typedef signed short        int16;

typedef unsigned int        uint32;
typedef signed int          int32;

#ifdef WIN32
typedef unsigned __int64    uint64;
#else
typedef unsigned long long  uint64;
#endif // WIN32

#ifdef WIN32
typedef signed __int64      int64;
#else
typedef signed long long    int64;
#endif // WIN32


// Disallows the copy constructor and operator= function.
// Should be used in the private: section.
#define DISALLOW_COPY_CONSTRUCTORS(TypeName)    \
    TypeName(const TypeName&);                  \
    void operator=(const TypeName&)

// Disallows the default constructor, copy constructor, and operator= function.
// Should be used in the private: section.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName)    \
    TypeName();                                     \
    DISALLOW_COPY_CONSTRUCTORS(TypeName)            \


// Some useful macros for deletion
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=0; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=0; } }
#endif