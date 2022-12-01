//!	Class: Combining the map and player classes together. 
/*!
    Auther: Abdulhadi Daher and Yazan Bahem
    Date: 20 / 11 / 2022
*/
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Message.h"

class Game {

public:
    //Constructors
    Game() = default;
    Game(sf::Vector2i game_dimensions);
    ~Game();

    void run();

private:
    //Variables
    sf::Vector2i gameDimensions;
    bool gameFinished;

    sf::RenderWindow* window; 
    sf::View view;
    //background
    sf::RectangleShape background;
    sf::Texture backgroundTextrue;  
    //circle view
    sf::Texture circleViewTexture;
    sf::Sprite circleViewSprite;

    float dt;
    sf::Clock dt_clock;

    //map and player object 
    Player player;
    Map map;

    //Message objects
    Message collectkey;
    Message needkey;
    Message victory;

    void windowIniti();
    void collisionDetec(sf::Vector2f& velocity);
    void displayMessages();
    void update();
    void render();

};
#endif 