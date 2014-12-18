#include <fstream>

#include "utils.h"

bool ReadFile(const char *_pFileName, string &_outFile)
{
    ifstream f(_pFileName);
    
    bool ret = false;
    
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            _outFile.append(line);
            _outFile.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
    else {
        printf("error in : %s",_pFileName);
    }
    
    return ret;
}