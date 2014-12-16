#include <string>

#define PI_f 3.1415926535897932384626433832795f
#define ToRadian(x) ((x) * PI_f / 180.0f)
#define ToDegree(x) ((x) * 180.0f / PI_f)

#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

using namespace std;

bool ReadFile(const char* fileName, string& outFile);