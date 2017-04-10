#ifndef OutputManager_hpp
#define OutputManager_hpp

#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

inline void WriteLine(string line)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) 
	line += "\r\n";
	wstring stemp = wstring(line.begin(), line.end());
	LPCWSTR sw = stemp.c_str();
	OutputDebugString(sw);
#else
	cout << line << endl;
#endif
}

#endif /* OutputManager_hpp */
