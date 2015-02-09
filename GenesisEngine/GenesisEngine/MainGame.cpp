#include "MainGame.h"
#include "Errors.h"
#include "ResourceManager.h"
#include "Renderer2dComponent.h"

#include <iostream>
#include <string>

MainGame::MainGame() :
_screenWidth(1024),
_screenHeight(768),
_time(0),
_gameState(GameState::PLAY),
_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	// Prof. B: Cleanly delete all actors (maybe, just trying to get it to exit cleanly)
	while (!myActorList.empty())
	{
		(myActorList.back()).Destroy();
		myActorList.pop_back();
	}
}

void MainGame::AddActor(Actor& newActor)
{
	myActorList.push_back(newActor);
}

void MainGame::run() {

	initSystems();

	gameLoop();
}

void MainGame::initSystems() {
	_window.create("The Genesis Engine", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders\\colorShading.vert", "Shaders\\colorShading.frag");
//	_colorProgram.addAttribute("vertexPosition");
//	_colorProgram.addAttribute("vertexColor");
//	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		//Used for frame time measuring
		_fpsLimiter.begin();

		processInput();
		_time += 0.1f;

		_camera.update();

		drawGame();

		_fps = _fpsLimiter.end();

		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 100) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}


void MainGame::processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}
	if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
}

void MainGame::DrawActors()
{
	for (ActorList::iterator it = myActorList.begin(); it != myActorList.end(); ++it)
	{
		(*it).Update(1.0 / _fps);
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
//	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
//	glUniform1i(textureLocation, 0);

	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//Create object with Renderer2dComponent
	//Renderer2dComponent sprite1;

	//Call Renderer object .init(startX, startY, width, height, texturePath);
	//.init(0.0, 0.0, 100.0, 100.0, "Textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png");

	//Call Renderer object .drawGame();
	//.drawGame();

	DrawActors();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.swapBuffer();
}
