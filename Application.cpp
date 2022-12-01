#include "Application.h"

//! Runs both the MainMenu and Game classes until the user decides to exit.    
void Application::run() {

    while (true) {
 
	    menu.run();
        if (menu.eventIsClosed() || menu.getUserChoice() == 3) {// Either pressed ESC button or pressed 'x' button
            break;
        }

        switch (menu.getUserChoice()) {
            case 0: {
                Game gameEasy(sf::Vector2i(11, 11));
                gameEasy.run();
                break;
            }
            case 1: {
                Game gameNormal(sf::Vector2i(21, 21));
                gameNormal.run();
                break;
            }
            case 2: {
                Game gameHard(sf::Vector2i(31, 31));
                gameHard.run();
                break;
            }
        }
        menu.resetUserChoice();// Will reset the user menu choice 
    }
}
