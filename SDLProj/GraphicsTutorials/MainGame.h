#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/GLTexture.h>
#include <vector>
#include <GameEngine/Sprite.h>
#include <GameEngine/Window.h>
#include <GameEngine/GameEngine.h>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

private:
	void InitSystems();
	void InitShaders();
	void GameLoop();
	void ProcessInput();
	void DrawGame();
	void CalculateFPS();

	GameEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector<GameEngine::Sprite*> _sprites;
	GameEngine::Sprite _sprite;
	GameEngine::GLSLProgram _colorProgram;
	float _time;
	float _fps;
	float _deltaTime;
	float _maxFPS;
};

