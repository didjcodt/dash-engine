/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <GL/gl.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "texture.hpp"

namespace texture {
	void Texture::open() {
		std::ifstream file;
		file.open(filename.c_str());
		file >> magicNum;
		std::string dummy;
		std::getline(file,dummy);
		std::getline(file,dummy);
		file >> width >> height;
		std::getline(file,dummy);
		std::getline(file,dummy);
		size_t size = width * height * 3;
		image = new unsigned char[size];
		int tempInt;
		for(size_t i = 0; i < size; i++) {
			file >> tempInt;
			image[i] = tempInt;
		}
		file.close();
	}
}
