//!	Class: Application class that is used to create a game through the menu.
/*!
	Auther: Abdulhadi Daher and Yazan Bahem
	Date: 20 / 11 / 2022
*/
#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Game.h"

class Application {
public:

	Application() = default;
	void run();

private:
	MainMenu menu;

};
#endif