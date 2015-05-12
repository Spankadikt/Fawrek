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



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
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