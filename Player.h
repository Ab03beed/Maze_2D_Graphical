//!	Class: Creating a player character which has some mechanical futures as movement and specific appearance in our game.
/*!
	Auther: Abdulhadi Daher and Yazan Bahem
	Date: 20 / 11 / 2022
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
public:

	Player() = default;

	void playerInit(sf::Vector2f dimensions, std::string path);
	const sf::RectangleShape& getPlayer() const;
	void animationUpdate();
	
	//set-get key
	void setkeyStatus(bool status);
	bool getKeyStatus() const;
	void setFinalKeyStatus(bool status);
	bool getFinalKeyStatus() const;

	//movment
	void moveUp(sf::Vector2f& velocity, float& dt);
	void moveDown(sf::Vector2f& velocity, float& dt);
	void moveLeft(sf::Vector2f& velocity, float& dt);
	void moveRight(sf::Vector2f& velocity, float& dt);
	void moveTo(sf::Vector2f& new_pos);
	void setPoss(sf::Vector2f& new_pos);

	void resetTextureDimensions();
	const sf::IntRect& getTextureDimensions() const;

private:
	const float movmentSpeed = 600.f;//350.f;
	bool hasKey;
	bool hasFinalKey;
	sf::RectangleShape playerShape;
	sf::Texture playerTexture;
	sf::Clock animationPs;
	sf::IntRect TextureDimensions;
};
#endif