#pragma once

#include <GL/glew.h>

class FBO
{
	public:
		FBO();
		~FBO();

		void genFBO(float w, float h);
		void bindFBO();
		void unbindFBO();

		void initQuad();
		void drawQuad();


	private:
		GLuint fbo; // Frame Buffer 
		GLuint rbo; // Render Buffer 
		GLuint cbo; // Colour Buffer 
		GLuint quadVAO;
		GLuint quadVBO;
};
