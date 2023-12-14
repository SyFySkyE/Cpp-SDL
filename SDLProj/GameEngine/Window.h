#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace GameEngine {
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void SwapBuffer();

		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth;
		int _screenHeight;
	};


}

