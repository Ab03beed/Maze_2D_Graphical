//!	Class: Generating a graphical interface using SFML library based on the generated maze
/*!
    Auther: Abdulhadi Daher and Yazan Bahem
    Date: 20 / 11 / 2022
*/
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "maze.h"

class Map {

public:

    Map() = default;
    void mapInit(sf::Vector2i map_dimensions);

    sf::Vector2f& getStartPoss();
    void setRectangleShapes(sf::RectangleShape& shape, sf::Texture& texture, std::string path);
    std::vector<std::vector<sf::RectangleShape>> myMapVec;

    //wall
    sf::RectangleShape wall;
    sf::Texture wallTexture;

    //path
    sf::RectangleShape path;
    sf::Texture pathTexture;

    //start and end doors
    sf::RectangleShape startDoor;
    sf::Texture startDoorTexture;

    sf::RectangleShape endDoor;
    sf::Texture endDoorTexture;

    //key
    sf::RectangleShape key;
    sf::Texture keyTexture;

    //maze object and maze startposs
    maze mainMaze;
    sf::Vector2f startPoss;

    //*********************************
    maze mainMaze2;
    sf::Vector2f startPoss2;
    sf::Vector2f EndPoss;
    void setPoss(sf::RectangleShape &shapes, int &x, int &y, sf::Vector2i &old);
    void createMaze2(sf::Vector2i map_dimensions);
    sf::RectangleShape key2;
    sf::Texture keyTexture2;
};
#endif