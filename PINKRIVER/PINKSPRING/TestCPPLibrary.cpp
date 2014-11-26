#include "TestCPPLibrary.h"


extern "C" {

	float GetTest(float val)
	{
		CUnmanagedTestClass testClass = CUnmanagedTestClass::CUnmanagedTestClass(val);
		

		return testClass.CUnmanagedTestClassFunction();
	}

    CUnmanagedTestClass::CUnmanagedTestClass(float val)
    {
        n = val;
    }

	CUnmanagedTestClass::~CUnmanagedTestClass()
    {
    }


    float CUnmanagedTestClass::CUnmanagedTestClassFunction()
    {
        return n * 2;
    }

}