#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

//#ifndef UTILS_H
//#define UTILS_H

#include <string>

using namespace std;

PR_LIBRARY_EXPORT bool ReadFile(const char* fileName, string& outFile);


//#endif //UTILS_H