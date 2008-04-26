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

#define SSE
#define ALIGN16 __declspec(align(16))

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

// Do not use windows min/max macros 
#define NOMINMAX 1

// For memory leak detection
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
//#define VERBOSE_NEW
#endif

// Null pointer
#ifndef NULL
#define NULL 0
#endif

// Some useful macros for safer deletion
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       delete (p); (p)=NULL
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) delete[] (p); (p)=NULL
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      if(p) (p)->Release(); (p)=NULL
#endif

// Tell the compiler we are not using a variable and don't give us a warning about it
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif

// For easy masking of individual bits
#define BIT_00      0x00000001
#define BIT_01      0x00000002
#define BIT_02      0x00000004
#define BIT_03      0x00000008
#define BIT_04      0x00000010
#define BIT_05      0x00000020
#define BIT_06      0x00000040
#define BIT_07      0x00000080
#define BIT_08      0x00000100
#define BIT_09      0x00000200
#define BIT_10      0x00000400
#define BIT_11      0x00000800
#define BIT_12      0x00001000
#define BIT_13      0x00002000
#define BIT_14      0x00004000
#define BIT_15      0x00008000
#define BIT_16      0x00010000
#define BIT_17      0x00020000
#define BIT_18      0x00040000
#define BIT_19      0x00080000
#define BIT_20      0x00100000
#define BIT_21      0x00200000
#define BIT_22      0x00400000
#define BIT_23      0x00800000
#define BIT_24      0x01000000
#define BIT_25      0x02000000
#define BIT_26      0x04000000
#define BIT_27      0x08000000
#define BIT_28      0x10000000
#define BIT_29      0x20000000
#define BIT_30      0x40000000
#define BIT_31      0x80000000


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
    DISALLOW_COPY_CONSTRUCTORS(TypeName)
