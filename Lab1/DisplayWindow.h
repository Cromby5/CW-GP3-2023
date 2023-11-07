#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>

using namespace std;

class DisplayWindow
{
public:
	DisplayWindow();
	~DisplayWindow();
	void initDisplay();
	void swapBuffer();
	void clearDisplayBuffer(float r, float g, float b, float a);

	float getScreenWidth();
	float getScreenHeight();
	SDL_Window* getWindow();

	//imgui
	void initImgui();
	void renderImgui();
	void clearImgui();
	void newFrameImgui(SDL_Event& event); // start of each loop


private:

	void returnError(std::string errorString);
	
	SDL_GLContext glContext; // global variable to hold the context
	SDL_Window* sdlWindow; // holds pointer to out window
	float screenWidth;
	float screenHeight;
};

