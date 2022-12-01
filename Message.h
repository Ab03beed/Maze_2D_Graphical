//!	Class: Creating a player character which has some mechanical futures as movement and a specific appearance in our game
/*!
	Auther: Abdulhadi Daher and Yazan Bahem
	Date: 20 / 11 / 2022
*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Message {
public:

	void messageInit();
	void setMessage(std::string new_message);
	bool is_empty() const;
	const sf::Text getMessage() const;
	void setMessagePos(int x_axie, int y_axie);
	void setMessageColor(sf::Color);

private:
	sf::Text message;
	sf::Font font;
};
#endif