#ifdef TESTFUNCDLL_EXPORT
#define TESTFUNCDLL_API __declspec(dllexport) 
#else
#define TESTFUNCDLL_API __declspec(dllimport) 
#endif

extern "C" {

	TESTFUNCDLL_API float GetTest(float);

    class TESTFUNCDLL_API CUnmanagedTestClass
    {
    public:
        CUnmanagedTestClass(float);
		~CUnmanagedTestClass();
        float CUnmanagedTestClassFunction();

         // TODO: add your methods here.
    private:
        float n;
    };
}