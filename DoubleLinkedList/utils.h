#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>   // <-- Required for std::ofstream and std::ifstream
#include <string>

#define IDC_LISTBOX_PATIENTS 101
#define IDC_EDIT_NAME        102
#define IDC_EDIT_EMAIL       103
#define IDC_EDIT_GENDER      104
#define IDC_EDIT_PHONE       105
#define IDC_EDIT_NUMBER      106
#define IDC_EDIT_AGE         107

#define IDC_BTN_EDIT         108
#define IDC_BTN_ADD          109
#define IDC_BTN_SEARCH_EMAIL 110
#define IDC_BTN_SAVE         111
#define IDC_BTN_CANCEL       112
#define IDC_BTN_DELETE       113
#define IDC_BTN_SEARCH_NAME  114

inline void writeString(std::ofstream& out, const std::string& str) {
	size_t length = str.size();
	out.write(reinterpret_cast<const char*>(&length), sizeof(length));
	out.write(str.c_str(), length);
}

inline std::string readString(std::ifstream& in) {
	size_t length;
	in.read(reinterpret_cast<char*>(&length), sizeof(length));
	std::string str(length, '\0');
	in.read(&str[0], length);
	return str;
}