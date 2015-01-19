#pragma once

#include <string>
#include <iostream>	
#include <Dependecies\SDL2-2.0.3\include\SDL.h>

namespace YuEngine {




	void YuFatalError(std::string errorMsg) {

		std::cout << errorMsg << std::endl;
		std::cout << "Enter any key to leave ... ";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(69);

	};



}