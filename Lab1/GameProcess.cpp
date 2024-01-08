#include "GameProcess.h"
#include <iostream>
#include <string>


GameProcess::GameProcess()
{
	_gameState = GameState::PLAY;
}

GameProcess::~GameProcess()
{
}

void GameProcess::run()
{
	initSystems(); 
	gameProcessLoop();
}

void GameProcess::initSystems()
{
	_gameDisplay.initDisplay();
	sky.initSkyBox();
	objectHandler.initObjects();
	gameAudio.initAudio();

	_gameDisplay.initImgui();

	fbo.initQuad();
	fbo.genFBO(_gameDisplay.getScreenWidth(), _gameDisplay.getScreenHeight());
	fbo2.genFBO(_gameDisplay.getScreenWidth(), _gameDisplay.getScreenHeight());
	fbo.GenGBuffer(_gameDisplay.getScreenWidth(), _gameDisplay.getScreenHeight());
	
	myCamera.initWorldCamera(glm::vec3(0, 0, 5), 70.0f, (float)_gameDisplay.getScreenWidth()/_gameDisplay.getScreenHeight(), 0.01f, 1000.0f);
	myTopDownCamera.initWorldCamera(glm::vec3(0, 20, 5), 70.0f, (float)_gameDisplay.getScreenWidth() / _gameDisplay.getScreenHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

}

void GameProcess::gameProcessLoop()
{
	while (_gameState != GameState::EXIT)
	{
		deltaTime.Update();
		gameAudio.playBackMusic();
		Input();
		_gameDisplay.newFrameImgui();
		drawGame();
		objectHandler.collision(deltaTime.GetDeltaTime(), gameAudio);
	}
}

void GameProcess::Input()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) // Get and process events using the SDL event system 
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				while (deltaTime.GetDeltaTime() > 0) // Key presses will still be registered from the keydown event, however they will only be processed if the deltatime is positive
				{
					case SDLK_SPACE:
						// Shoot Missiles

						break;
					case SDLK_ESCAPE:
						_gameState = GameState::EXIT;
						break;
					case SDLK_TAB:
						// Open / close imgui window
						_gameDisplay.ToggleImGuiWindow();
						break;
				}
			}
			break;
		case SDL_MOUSEMOTION:
			if (_gameDisplay.getImGuiStatus())
				// If the mouse is over an imgui window, do not rotate the camera
				SDL_SetRelativeMouseMode(SDL_FALSE); // Unlock mouse from window and show it on screen
			else
			{
				SDL_SetRelativeMouseMode(SDL_TRUE); // Lock mouse to window and hide it from view 
				myCamera.RotateX((-event.motion.xrel / 1000.0f)); // Rotate camera on X axis (Remove the - on the xrel to invert the rotation)
				myCamera.RotateY((-event.motion.yrel / 1000.0f)); // Rotate camera on Y axis (Remove the - on the yrel to invert the rotation)
			}
		break;
		}
		_gameDisplay.imguiProcessEvent(event); // Start the Dear ImGui frame
	}
	// GET KEYBOARD STATE, for continuous movement as keydown events are only registered once or something that makes it so that the camera only moves once per tick when a key is pressed
	// Still not as smooth as I would like, but it works for actual gameplay and is more responsive than the keydown events
	SDL_PumpEvents();
	keystate = SDL_GetKeyboardState(NULL);
	float mspeed = speed * deltaTime.GetDeltaTime();
	if (keystate[SDL_SCANCODE_A]) {
		myCamera.MoveRight(-mspeed);
	}
	if (keystate[SDL_SCANCODE_D]) {
		myCamera.MoveRight(mspeed);
	}
	if (keystate[SDL_SCANCODE_W]) {
		myCamera.MoveForward(mspeed);
	}
	if (keystate[SDL_SCANCODE_S]) {
		myCamera.MoveForward(-mspeed);
	}
}
	

void GameProcess::drawGame()
{
	_gameDisplay.clearDisplayBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	//myCamera.SetLook(glm::vec3(0, 0, 0));
	myTopDownCamera.SetLook(glm::vec3(0, 0, 0));

	fbo.bindFBO(); // Draw to FBO
		sky.drawSkyBox(myTopDownCamera);
		objectHandler.drawObjects(myTopDownCamera,counter,newCount);
	fbo.unbindFBO();

	fbo.drawQuad(); // draw fbo to screen
	glEnable(GL_DEPTH_TEST);
	sky.drawSkyBox(myCamera);
	objectHandler.drawObjects(myCamera, counter, newCount);

	_gameDisplay.renderImgui(); // Render imgui
	counter += deltaTime.GetDeltaTime() * 1.0f;
	
	newCount += 0.1f; // I believe I broke deltatime / or I am blind to a very obvious issu, so this is a really bad temporary fix to display GP CW without taking up more time

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();
	_gameDisplay.swapBuffer();
} 