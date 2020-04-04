
#include "coreGameOperations.h"
#include <SFML/Graphics.hpp>


void setSprite(sf::Sprite* spriteToMove, float x, float y) {
    (*spriteToMove).setPosition(x, y);
    return;
}

void moveSprite(sf::Sprite* spriteToMove, float x, float y) {
    (*spriteToMove).move(x, y);
    return;
}
