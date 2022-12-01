#include "MainMenu.h"
#include "Game.h"

//! Default constructor of the main menu, which contains the approachable keys by the user. 
MainMenu::MainMenu() {
    
    windowInit();

    //Easy
    mainMenu[0].messageInit();
    mainMenu[0].setMessage("Easy");
    mainMenu[0].setMessagePos(100, 100);
    //Normal
    mainMenu[1].messageInit();
    mainMenu[1].setMessage("Normal");
    mainMenu[1].setMessagePos(100, 200);
    //Hard
    mainMenu[2].messageInit();
    mainMenu[2].setMessage("Hard");
    mainMenu[2].setMessagePos(100, 300);
    //Quit
    mainMenu[3].messageInit();
    mainMenu[3].setMessage("Quit");
    mainMenu[3].setMessagePos(100, 400);
    //Help message
    mainMenu[4].messageInit();
    mainMenu[4].setMessage("\"arrow keys\" to move in menu. \n\"WADS\" to move in game. \n\"ESC\" to exit.");
    mainMenu[4].setMessagePos(100, 600);
    mainMenu[4].setMessageColor(sf::Color(0, 0, 0));

    //Will start from the index [0] after adding up by pressing the down arrow at the menu start.
    userChoice = -1;
}
//! Destrcutor. 
MainMenu::~MainMenu() {
    delete window;
}

//! Navigating through the menu by pressing the up arrow. 
void MainMenu::MoveUp() {

    if (userChoice >= 0) {

        if (userChoice < MAX) {
            mainMenu[userChoice].setMessageColor(sf::Color(51, 153, 255));
        }
        userChoice--;

        if (userChoice == - 1) {
            mainMenu[userChoice + 1].setMessageColor(sf::Color(51, 153, 255));
            userChoice = 3;
        }
        mainMenu[userChoice].setMessageColor(sf::Color::Red);
    }
}

//! Navigating through the menu by pressing the down arrow.   
void MainMenu::MoveDown() {

    if (userChoice < MAX) {

        if (userChoice >= 0) {
            mainMenu[userChoice].setMessageColor(sf::Color(51, 153, 255));
        }
        userChoice++;

        if (userChoice > 3) {
            mainMenu[userChoice - 1].setMessageColor(sf::Color(51, 153, 255));
            userChoice = 0;
        }
       mainMenu[userChoice].setMessageColor(sf::Color::Red);
    }
}

//! Initializing image and size to the main menu window.  
void MainMenu::windowInit() {
    window = new sf::RenderWindow(sf::VideoMode(920, 700), "Main Menu", sf::Style::Close | sf::Style::Titlebar);
    backgroundTexture.loadFromFile("L:/livecoding/Martin-c++/Project_test1/Project_test1/Images/BackGround.jpg");
    background.setTexture(&backgroundTexture);
    background.setSize(sf::Vector2f(920, 700));
}

//! Is a check case for any new events  
void MainMenu::update() {
 
    while (window->pollEvent(event)){

        if (event.type == sf::Event::Closed) { window->close(); }
        
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Up) {MoveUp(); }
            if (event.key.code == sf::Keyboard::Down) { MoveDown(); }
        }
    }
}

//! Rendering the main menu window.  
void MainMenu::render() {

    window->clear();
    window->draw(background);
    
    for (int i = 0; i < MAX + 1; i++) {//'+1' to get the help message
        window->draw(mainMenu[i].getMessage());
    }
    window->display();
}

//! Calles the update and render fuctions as long as the window is open.   
void MainMenu::run() {
    
    while (window->isOpen()) {
        update();
        render();
        if (event.key.code == sf::Keyboard::Return) {//Will reset the color of the user choose, and starts the user choose.
            mainMenu[userChoice].setMessageColor(sf::Color(51, 153, 255));
            break;
        }
    }
}
//! Returns the user Choice, this function will be needed in the Application class.
const int MainMenu::getUserChoice() const {
    return userChoice;
}

//! Resets the user Choice to the default value(-1), this function will be needed in the Application class.
void MainMenu::resetUserChoice() {
    userChoice = -1;
}

//! Will return ture if the menu window is closed, this function will be needed in the Application class.
bool MainMenu::eventIsClosed() const {
    if (event.type == sf::Event::Closed) { return true; }
    return false;
}

