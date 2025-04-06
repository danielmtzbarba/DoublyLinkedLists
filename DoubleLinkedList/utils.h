#pragma once

#include <iostream>
#include <fstream>   // <-- Required for std::ofstream and std::ifstream
#include <string>

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