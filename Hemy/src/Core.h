#pragma once

#ifndef HEMY_API
#ifdef HEMY_BUILD_DLL
#define HEMY_API __declspec(dllexport)
#elif HEMY_IMPORT_DLL
#define HEMY_API __declspec(dllimport)
#else
#define HEMY_API
#endif
#endif