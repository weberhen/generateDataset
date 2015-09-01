#include "Utils.h"
#include <windows.h>

string verticesFloatingPoint_str = "\\verticesFloatingPoint";
string colorMap_str = "\\colorMap";
string confidenceMap_str = "\\confidenceMap";
string uvMap_str = "\\uvMap";

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

string createDirs(void)
{
	string root_data_dir = "data";
	
	//create data directory
	CreateDirectoryW(s2ws(root_data_dir).c_str(), NULL);

	string test_name;
	cout << "Type the test name: ";
	cin >> test_name;
	cout << "press `s` to start recording. " << endl;

	string verticesFloatingPoint_str_ext;
	string colorMap_str_ext;
	string confidenceMap_str_ext;
	string uvMap_str_ext;

	verticesFloatingPoint_str_ext = "data\\" + test_name + verticesFloatingPoint_str;
	colorMap_str_ext = "data\\" + test_name + colorMap_str;
	confidenceMap_str_ext = "data\\" + test_name + confidenceMap_str;
	uvMap_str_ext = "data\\" + test_name + uvMap_str;

	CreateDirectoryW(s2ws(test_name).c_str(), NULL);
	CreateDirectoryW(s2ws(verticesFloatingPoint_str_ext).c_str(), NULL);
	CreateDirectoryW(s2ws(colorMap_str_ext).c_str(), NULL);
	CreateDirectoryW(s2ws(confidenceMap_str_ext).c_str(), NULL);
	CreateDirectoryW(s2ws(uvMap_str_ext).c_str(), NULL);

	return test_name;
}
