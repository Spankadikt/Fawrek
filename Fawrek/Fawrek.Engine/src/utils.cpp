#include <fstream>

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include "utils.h"

bool ReadFile(const char* _pcFileName, string& _sOutFile)
{
    ifstream f(_pcFileName);
    
    bool ret = false;
    
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            _sOutFile.append(line);
            _sOutFile.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
    else {
        printf("error in : %s",_pcFileName);
    }
    
    return ret;
}

long long GetCurrentTimeMillis()
{
#ifdef WIN32    
    return GetTickCount();
#else
    timeval t;
    gettimeofday(&t, NULL);

    long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
    return ret;
#endif    
}

#ifdef WIN32
float fmax(float a, float b)
{
    if (a > b)
        return a;
    else
        return b;
}
#endif