
#include "coreGameOperations.h"
#include <SFML/Graphics.hpp>


TransparentSprite::TransparentSprite() {

}

TransparentSprite::TransparentSprite(std::string fileName) {
    (this->imageObj).loadFromFile(fileName);
    (this->imageObj).createMaskFromColor(sf::Color(255, 255, 255), 0);

    (this->textureObj).loadFromImage(this->imageObj);
    (this->spriteObj).setTexture(this->textureObj);
}

TransparentSprite::~TransparentSprite() {

}

void TransparentSprite::loadNewTransparentTexture(std::string fileName) {
    (this->imageObj).loadFromFile(fileName);
    (this->imageObj).createMaskFromColor(sf::Color(255, 255, 255), 0);

    (this->textureObj).loadFromImage(this->imageObj);
    (this->spriteObj).setTexture(this->textureObj);
}

bool TransparentSprite::intersection(sf::Sprite otherSprite) {
    return (this->spriteObj.getGlobalBounds()).intersects(otherSprite.getGlobalBounds());
}



void setSprite(sf::Sprite* spriteToMove, float x, float y) {
    (*spriteToMove).setPosition(x, y);
    return;
}

void moveSprite(sf::Sprite* spriteToMove, float x, float y) {
    (*spriteToMove).move(x, y);
    return;
}

PauseMenu::PauseMenu() {
    Instance = 0;
}

PauseMenu* PauseMenu::getMenu() {
    if (!Instance) Instance = new PauseMenu();
    return Instance;
}
