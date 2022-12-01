#include "Game.h"

//! Initializing the width and height of the game window 
/*!
    @param 'width' The width of the game window
    @param 'height' The height of the game window
*/
void Game::windowIniti() {

    window = new sf::RenderWindow(sf::VideoMode(1024, 960), "Find the key if you have the balls", sf::Style::Close|sf::Style::Titlebar);
    
    //background
    backgroundTextrue.loadFromFile("L:/livecoding/Martin-c++/Project_test1/Project_test1/Images/BackGround1.jpg");
    background.setTexture(&backgroundTextrue);
    background.setSize(sf::Vector2f( gameDimensions.x * 148, gameDimensions.y * 158));
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
    background.setPosition(sf::Vector2f((gameDimensions.x * 100) / 2, (gameDimensions.y * 100) / 2));
    // circle inti
    circleViewTexture.loadFromFile("L:/livecoding/Martin-c++/Project_test1/Project_test1/Images/circleView.png");
    circleViewSprite.setTexture(circleViewTexture);
    circleViewSprite.setScale(sf::Vector2f(2,2));
    circleViewSprite.setOrigin(sf::Vector2f(400, 300));
}

//! collision detection
/*!
    @param 'width' The width of the game window
    @param 'height' The height of the game window
*/
void Game::collisionDetec(sf::Vector2f& velocity) {

    sf::FloatRect nextpos;
    sf::FloatRect wallBounds;
    for (size_t y = 0; y < map.myMapVec.size(); y++) {

        for (size_t x = 0; x < map.myMapVec[y].size(); x++) {

            sf::FloatRect playerBounds = player.getPlayer().getGlobalBounds();
            //If the next positions on the map is a wall or start door as well as the end door or key(when the player does not has a key)
            if (map.myMapVec[y][x].getTexture() == &map.wallTexture
                || map.myMapVec[y][x].getTexture() == &map.startDoorTexture
                || map.myMapVec[y][x].getTexture() == &map.endDoorTexture
                || map.myMapVec[y][x].getTexture() == &map.keyTexture && !player.getKeyStatus()
                || map.myMapVec[y][x].getTexture() == &map.keyTexture2 && !player.getFinalKeyStatus()) {

                sf::FloatRect wallBounds = map.myMapVec[y][x].getGlobalBounds();
                nextpos = playerBounds;
                nextpos.left += velocity.x;
                nextpos.top += velocity.y;

                if (wallBounds.intersects(nextpos)) {// if the player next position will collide with any of the above conditions 

                    if (map.myMapVec[y][x].getTexture() == &map.keyTexture && !player.getKeyStatus() 
                        || map.myMapVec[y][x].getTexture() == &map.keyTexture2 && !player.getFinalKeyStatus()) {
                        collectkey.setMessage("Press E to collect the key");
                        if (sf::Keyboard().isKeyPressed(sf::Keyboard::E)) {
                            if (map.myMapVec[y][x].getTexture() == &map.keyTexture) {
                                map.keyTexture = map.pathTexture;
                                player.setkeyStatus(true);
                            }
                            else if(map.myMapVec[y][x].getTexture() == &map.keyTexture2) {
                                map.keyTexture2 = map.pathTexture;
                                player.setFinalKeyStatus(true);
                            }
                        }
                    }
                    else if (map.myMapVec[y][x].getTexture() == &map.endDoorTexture && !player.getKeyStatus() && !player.getFinalKeyStatus()) {
                        needkey.setMessage("Find the key to open the door");
                        velocity.x = 0.f;
                        velocity.y = 0.f;

                    }
                    else if (map.myMapVec[y][x].getTexture() == &map.endDoorTexture && player.getKeyStatus()) {  
                        sf::Vector2i v(11, 11);
                        map.createMaze2(v);
                        sf::Vector2f v2(player.getPlayer().getPosition().x, player.getPlayer().getPosition().y + 300);
                        player.setPoss(v2);
                        player.setkeyStatus(false);
                    }
                    else if (map.myMapVec[y][x].getTexture() == &map.endDoorTexture && player.getFinalKeyStatus()) {
                            sf::sleep(sf::seconds(3));
                    }
                    else {
                        velocity.x = 0.f;
                        velocity.y = 0.f;
                        player.resetTextureDimensions();//if the player collides with wall or doors the animation resets (player wont move).  
                    }
                }
            }
        }
    }
}

void Game::displayMessages() {

    if (!collectkey.is_empty() || !needkey.is_empty()) {
        if (!collectkey.is_empty() && !needkey.is_empty()) {// the key is at the end door
            window->draw(needkey.getMessage());
            needkey.setMessage("");
            collectkey.setMessage("");

        }
        else if (needkey.is_empty() && !collectkey.is_empty()) {// colliding with key only
            window->draw(collectkey.getMessage());
            collectkey.setMessage("");
        }
        else { window->draw(needkey.getMessage()); }// after colliding with the end door, the text will only disapear if player coolide with the key
    }
}

//! Initializing the window, map, player, text and background of the game
/*!
    @param 'width' Is the width of the maze which will be created
    @param 'height' Is the height of the maze which will be created
*/
Game::Game(sf::Vector2i game_dimensions) {
    gameDimensions = game_dimensions;
    //window and map inti
    windowIniti();
    map.mapInit(gameDimensions);

    //player inti
    player.playerInit(sf::Vector2f(50, 60), "L:/livecoding/Martin-c++/Project_test1/Project_test1/Images/player.png");
    player.setPoss(map.getStartPoss());
    //message inti
    collectkey.messageInit();
    needkey.messageInit();
}

//! Game destructor
Game::~Game() {delete window;}

//! Checking if there is any update in game event as movement and collision 

//! Update any game event as well as the view(black circle view, text messages, camera fixed position)
void Game::update(){
    
    sf::Event sfEvent;
    while (window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) { window->close(); }
    }

    if (sf::Keyboard().isKeyPressed(sf::Keyboard::Escape)) { window->close(); }

    sf::Vector2f velocity;

    //Checks if any kay was pressed, and then checks what key was pressed (movment).
    if (sf::Keyboard().isKeyPressed(sf::Keyboard::W)) {
        player.moveUp(velocity, dt);
    }

    if (sf::Keyboard().isKeyPressed(sf::Keyboard::S)) {
        player.moveDown(velocity, dt);
    }

    if (sf::Keyboard().isKeyPressed(sf::Keyboard::A)) {
        player.moveLeft(velocity, dt);
    }

    if (sf::Keyboard().isKeyPressed(sf::Keyboard::D)) {
        player.moveRight(velocity, dt);
    }
    //reset player animation to defualt if key is released.
    if (velocity.x == 0 && velocity.y == 0 && player.getTextureDimensions().left != 0) { player.resetTextureDimensions(); }

    collisionDetec(velocity);
    player.animationUpdate();
    player.moveTo(velocity);

    view.setCenter(sf::Vector2f(player.getPlayer().getPosition().x + 25, player.getPlayer().getPosition().y + 25));
    circleViewSprite.setPosition(sf::Vector2f(player.getPlayer().getPosition().x + 25, player.getPlayer().getPosition().y +25));
    collectkey.setMessagePos(player.getPlayer().getPosition().x - 150, player.getPlayer().getPosition().y + 450);
    needkey.setMessagePos(player.getPlayer().getPosition().x - 150, player.getPlayer().getPosition().y + 450);
}

//! Rendering the window game which includes the map, player and view settings 
void Game::render() {

    window->clear();
    window->draw(background);
    window->setView(view);
   
    //Render Items
    for (size_t x = 0; x < map.myMapVec.size() ; x++) {
        for (sf::RectangleShape &mapElement : map.myMapVec[x]) {
            window->draw(mapElement); 
        }
    }  
    //window->draw(circleViewSprite);
    window->draw(player.getPlayer());
    displayMessages();
    window->display();
}

//! Resets the timer (delta time) and calls the update and render functions as long as the window is open 
void Game::run() {

    while (window->isOpen()) {
        
        dt = dt_clock.restart().asSeconds();
        update();
        render();
    }
}