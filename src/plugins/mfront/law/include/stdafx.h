// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__)
#define AFX_STDAFX_H__

#ifdef _LINUX

#include <unistd.h>
//#include <sys/io.h>
//#include <sys/direct.h>
#define cwd getcwd
#define cd chdir
#define myaccess access
#define md mkdir

#elif defined(_WIN32)

#include <io.h>
#include <direct.h>
//#pragma warning(disable:4996)
#define cwd _getcwd
#define cd _chdir
#define myaccess _access
#define md _mkdir

#endif //_WIN32

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cfloat>
#include <cmath>
#include <string>	// pour les operations sur les strings (STL)
#include <functional>	// pour les operations math�matiques (STL)
#include <numeric> // pour les manipulations sur vecteurs (STL)
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
//#include <filesystem>                   ///////////////// CHECK CHECK
#include <cstring>                        ///////////////// CHECK CHECK  FOR CENTOS 7
#include <stdexcept>                      ///////////////// CHECK CHECK  FOR CENTOS 7


#include "utils.h"
#include "hujeux.h"
//#include "druckerprager.h"         // Not needed

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

///////////////////////////
// CONSTANTES
///////////////////////////
constexpr auto MAXCAR = 500; // Nb max de caracteres sur une ligne;
constexpr auto MAXBUFFER = 257;

#endif // !defined(AFX_STDAFX_H__)
