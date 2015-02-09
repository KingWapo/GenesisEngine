#include "Errors.h"

#include <cstdlib>

#include <iostream>
#include <SDL\SDL.h>

void nonFatalError(std::string errorString) {
	std::cout << "Warning: " << errorString << std::endl;
}

void fatalError(std::string errorString) {
	std::cout << "FATAL ERROR: " << errorString << std::endl;
	std::cout << "Press enter to exit...";
	char tmp = std::cin.get();

	SDL_Quit();
	exit(1);
}