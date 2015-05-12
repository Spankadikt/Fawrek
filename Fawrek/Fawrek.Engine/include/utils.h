#include "api.h"

#ifndef UTILS_H
#define	UTILS_H

#include <time.h>
#include <string>
#include <sstream>
#include <vector>

#include "types.h"

using namespace std;

#define PI_f 3.1415926535897932384626433832795f
#define ToRadian(x) ((x) * PI_f / 180.0f)
#define ToDegree(x) ((x) * 180.0f / PI_f)

#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define SNPRINTF _snprintf_s
#define ZERO_MEM(a) memset(a, 0, sizeof(a))

#ifdef WIN32
#define SNPRINTF _snprintf_s
#define RANDOM rand
#define SRANDOM srand((unsigned)time(NULL))
float FAWREK_API fmax(float a, float b);
#else
#define SNPRINTF snprintf
#define RANDOM random
#define SRANDOM srandom(getpid())
#endif

using namespace std;

bool FAWREK_API ReadFile(const char* _cFileName, string& _sOutFile);
std::vector<std::string> FAWREK_API &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> FAWREK_API split(const std::string &s, char delim);

long long FAWREK_API GetCurrentTimeMillis();

#endif //UTILS_H