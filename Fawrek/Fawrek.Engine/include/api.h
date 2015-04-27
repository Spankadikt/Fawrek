#ifndef FAWREK_API_INCLUDED
#define FAWREK_API_INCLUDED

#ifdef FAWREK_EXPORT
#define FAWREK_API __declspec(dllexport)
#else
#define FAWREK_API __declspec(dllimport)
#endif

#endif 