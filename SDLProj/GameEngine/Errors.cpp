#include "Errors.h"
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

namespace GameEngine {
	void fatalError(std::string errorStr)
	{
		std::cout << errorStr << std::endl;
		std::cout << "Enter any key to quit" << std::endl;
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(1);
	}
}
