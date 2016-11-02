/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <GL/gl.h>
#include <string>
#include <vector>
#include <iostream>

namespace texture {
	class Texture {
		public:
			Texture(std::string filename) {
				this->filename = filename;
				open();
			}

			void setId(GLuint id) {this->id = id; }
			unsigned char* getImage() { return image; };
			GLuint getId()  { return id;    };
			int getWidth()   { return width; };
			int getHeight()  { return height;};

		protected:
			void open();

		private:
			GLuint id;
			std::string magicNum;
			std::string filename;
			int width, height;
			unsigned char *image;
	};
}
