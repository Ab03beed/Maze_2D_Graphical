#include "Player.h"
//! Initializing the player image and size. 
/*!
	@param 'dimensions' Is the player height and width
	@param 'path' Where the image is located in the OS
*/
void Player::playerInit(sf::Vector2f dimensions, std::string path) {

	playerShape.setSize(dimensions);
	hasKey = false;
	hasFinalKey = false;
	playerTexture.loadFromFile(path);
	playerShape.setTextureRect(sf::IntRect(0, 0, 46.75, 64));
	playerShape.setTexture(&playerTexture);
	TextureDimensions.height = 64;
	TextureDimensions.width = 46.75;
}

//! Get access to the player from other classes without being able to change player futures.
 const sf::RectangleShape& Player::getPlayer() const{ return playerShape; }

//! Giving the player a new position.
/*!
	@param 'new_pos' Is the new position which will be given to the player.
*/
 void Player::moveTo(sf::Vector2f& new_pos) {
	 playerShape.move(new_pos);
 }

 void Player::setPoss(sf::Vector2f& new_pos) {
	 playerShape.setPosition(new_pos);
 }
 
 void Player::resetTextureDimensions() {
	 TextureDimensions.left = 0;
 }

 const sf::IntRect& Player::getTextureDimensions() const{
	 return this->TextureDimensions;
 }

//!  Setting which frame of the player image will be given according to the player movement 
/*!
	@param 'picFrame' position of the frame
*/
void Player::animationUpdate() {
	playerShape.setTextureRect(TextureDimensions);
}

//! Setting key status (if the player has collected the key or not) 
/*!
	@param 'status' Will be true of false depending on whether the player has collected the key or not
*/
void Player::setkeyStatus(bool status) { hasKey = status; }

//! Getting key status (if the player has collected the key or not) 
bool Player::getKeyStatus() const{ return hasKey; }

void Player::setFinalKeyStatus(bool status) { hasFinalKey = status; }

bool Player::getFinalKeyStatus() const { return hasFinalKey; }

void Player::moveUp(sf::Vector2f& velocity, float& dt) {

	velocity.y += -movmentSpeed * dt;
	//changes the player animation.
	this->TextureDimensions.top = 3 * 64;
	if (this->animationPs.getElapsedTime().asMilliseconds() >= 150.0f) {

		if (this->TextureDimensions.left >= 93.5) { this->TextureDimensions.left = 0; }
		else { this->TextureDimensions.left += 46.75; }
		this->animationPs.restart();
	}
}

void Player::moveDown(sf::Vector2f& velocity, float& dt) {
	velocity.y += movmentSpeed * dt;
	//changes the player animation.
	this->TextureDimensions.top = 0 * 64;
	if (this->animationPs.getElapsedTime().asMilliseconds() >= 150.0f) {

		if (this->TextureDimensions.left >= 93.5) { this->TextureDimensions.left = 0; }
		else { this->TextureDimensions.left += 46.75; }
		this->animationPs.restart();
	}
}

void Player::moveLeft(sf::Vector2f& velocity, float& dt) {
	velocity.x += -movmentSpeed * dt;
	//changes the player animation.
	this->TextureDimensions.top = 1 * 64;
	if (this->animationPs.getElapsedTime().asMilliseconds() >= 150.0f) {

		if (this->TextureDimensions.left >= 93.5) { this->TextureDimensions.left = 0; }
		else { this->TextureDimensions.left += 46.75; }
		this->animationPs.restart();
	}
}

void Player::moveRight(sf::Vector2f& velocity, float& dt) {
	velocity.x += movmentSpeed * dt;
	//changes the player animation.
	this->TextureDimensions.top = 2 * 64;
	if (this->animationPs.getElapsedTime().asMilliseconds() >= 150.0f) {

		if (this->TextureDimensions.left >= 93.5) { this->TextureDimensions.left = 0; }
		else { this->TextureDimensions.left += 46.75; }
		this->animationPs.restart();
	}
}





