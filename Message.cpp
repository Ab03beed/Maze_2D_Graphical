#include "Message.h"

//! Initializing the font and the text messages that will appear in a certain moment of the game 
void Message::messageInit() {
    
    font.loadFromFile("L:/livecoding/Martin-c++/Project_test1/Project_test1/Fonts/arial.ttf");
    message.setFont(font);
    message.setCharacterSize(24);
    message.setFillColor(sf::Color(51, 153, 255));
    message.setStyle(sf::Text::Bold);
    message.setString("");
    message.setLetterSpacing(1.5);
}

void Message::setMessage(std::string new_message) {
    message.setString(new_message);
}

bool Message::is_empty() const {

    if (message.getString().isEmpty()) {
        return true;
    }
     return false;
}

const sf::Text Message::getMessage() const {
    return message;
}

 void Message::setMessagePos(int x_axie, int y_axie) {
     message.setPosition( x_axie, y_axie);
 }

 void Message::setMessageColor(sf::Color new_color) {
     message.setFillColor(new_color);
 }
