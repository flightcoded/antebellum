
#include "texture.h"

#include <GL/glew.h>

#include "stb_image/stb_image.h"

#include <iostream>

unsigned int texture::usedslots = 0;

texture::texture(const char* path){

	stbi_set_flip_vertically_on_load(true);

	slot = usedslots;
	int w, h, channelcount;
	unsigned char* image = stbi_load(path, &w, &h, &channelcount, 0);

	//glActiveTexture(GL_TEXTURE0 + slot);

	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		stbi_image_free(image);

	usedslots++;
}

texture::~texture(){

	glDeleteTextures(1, &ID);
}

void texture::bind(){

	//glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void texture::unbind(){

	glBindTexture(GL_TEXTURE_2D, 0);
}
