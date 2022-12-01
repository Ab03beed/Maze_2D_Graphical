//!	Class: Main menu with a graphical interface where the user can select the level of the game or to exit
/*!
	Auther: Abdulhadi Daher and Yazan Bahem
	Date: 20 / 11 / 2022
*/
#ifndef MAINMENUE_H
#define	MAINMENUE_H

#include <SFML/Graphics.hpp>
#include "Message.h"

class MainMenu {

public:

	MainMenu();
	~MainMenu();
	void run();
	const int getUserChoice() const;
	void resetUserChoice();
	bool eventIsClosed() const;

private:
	//window and background
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::RenderWindow* window;
	//main menu variable
	const int MAX = 4;
	Message mainMenu[5];

	int userChoice;
	sf::Event event;

	void MoveUp();
	void MoveDown();
	void windowInit();
	void render();
	void update();
};
#endif 

