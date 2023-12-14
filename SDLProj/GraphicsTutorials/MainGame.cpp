#include "MainGame.h"
#include <GameEngine/Errors.h>
#include <iostream>



MainGame::MainGame() : _time(0)
{
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
	_maxFPS = 360;
}

MainGame::~MainGame()
{
}

void MainGame::InitSystems()
{
	GameEngine::init();

	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);

	InitShaders();
}

void MainGame::InitShaders()
{
	_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.AddAttribute("vertexColor");
	_colorProgram.AddAttribute("vertexUV");
	_colorProgram.LinkShaders();
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT) 
	{
		// used for frame time measurement
		float startTicks = SDL_GetTicks();

		ProcessInput();
		_time += 0.01f;
		DrawGame();
		CalculateFPS();

		//TODO
		static int frameCounter = 0;
		if (frameCounter++ == 100) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
			
		// limit fps
		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type) 
		{
			case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

			case SDL_MOUSEMOTION:
				//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}	
}

void MainGame::DrawGame()
{	
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	_colorProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	
	GLint textureLocation = _colorProgram.GetUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	GLuint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, _time);

	for (int i = 0; i < _sprites.size(); i++)
		_sprites[i]->Draw();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.UnUse();	

	_window.SwapBuffer();
}

void MainGame::Run()
{
	InitSystems();
	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump_Update 1.2/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump_Update 1.2/PNG/CharacterRight_Standing.png");	

	//_playerTexture = ImageLoader::LoadPNG("Textures/JimmyJump_Update 1.2/PNG/CharacterRight_Standing.png");

	GameLoop();
}

void MainGame::CalculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrameSample = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_deltaTime = currentTicks - prevTicks;
	frameTimes[currentFrameSample % NUM_SAMPLES] = _deltaTime; // does circular thru array. 1 % 10 = 1 2 % 10 = 2... 10 % 10 is 0

	prevTicks = currentTicks;

	int count;
	currentFrameSample++;
	if (currentFrameSample < NUM_SAMPLES)
		count = currentFrameSample;
	else
		count = NUM_SAMPLES;

	float frameTimeAvg = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAvg += frameTimes[i];
	}

	frameTimeAvg /= count;

	if (frameTimeAvg > 0.0f)
		_fps = 1000.0f / frameTimeAvg;
	else
		_fps = 0.0f;

	
}
