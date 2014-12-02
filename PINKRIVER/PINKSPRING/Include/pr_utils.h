#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

#include <string>

#define PI_f 3.1415926535897932384626433832795f
#define ToRadian(x) ((x) * PI_f / 180.0f)
#define ToDegree(x) ((x) * 180.0f / PI_f)

using namespace std;

PR_LIBRARY_EXPORT bool ReadFile(const char* fileName, string& outFile);