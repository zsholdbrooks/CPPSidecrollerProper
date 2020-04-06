
#include "coreGameOperations.h"
#include <SFML/Graphics.hpp>


TransparentSprite::TransparentSprite() {

}

TransparentSprite::TransparentSprite(std::string fileName) {
    (*(this->imageObj)).loadFromFile(fileName);
    (*(this->imageObj)).createMaskFromColor(sf::Color(255, 255, 255), 0);

    (*(this->textureObj)).loadFromImage(*(this->imageObj));
    (*(this->spriteObj)).setTexture(*(this->textureObj));
}

TransparentSprite::TransparentSprite(std::string hair, std::string head, std::string shirt, std::string pants, std::string shoes) {
    sf::RenderTexture *composite = new sf::RenderTexture;
    (*composite).create(40, 133);

    sf::Image* tempHairImage = new sf::Image;
    sf::Image* tempHeadImage = new sf::Image;
    sf::Image* tempShirtImage = new sf::Image;
    sf::Image* tempPantsImage = new sf::Image;
    sf::Image* tempShoesImage = new sf::Image;

    (*tempHairImage).loadFromFile(hair);
    (*tempHeadImage).loadFromFile(head);
    (*tempShirtImage).loadFromFile(shirt);
    (*tempPantsImage).loadFromFile(pants);
    (*tempShoesImage).loadFromFile(shoes);

    (*tempHairImage).createMaskFromColor(sf::Color(255, 255, 255), 0);
    (*tempHeadImage).createMaskFromColor(sf::Color(255, 255, 255), 0);
    (*tempShirtImage).createMaskFromColor(sf::Color(255, 255, 255), 0);
    (*tempPantsImage).createMaskFromColor(sf::Color(255, 255, 255), 0);
    (*tempShoesImage).createMaskFromColor(sf::Color(255, 255, 255), 0);

    sf::Texture* tempHairTexture = new sf::Texture;
    sf::Texture* tempHeadTexture = new sf::Texture;
    sf::Texture* tempShirtTexture = new sf::Texture;
    sf::Texture* tempPantsTexture = new sf::Texture;
    sf::Texture* tempShoesTexture = new sf::Texture;

    (*tempHairTexture).loadFromImage(*tempHairImage);
    (*tempHeadTexture).loadFromImage(*tempHeadImage);
    (*tempShirtTexture).loadFromImage(*tempShirtImage);
    (*tempPantsTexture).loadFromImage(*tempPantsImage);
    (*tempShoesTexture).loadFromImage(*tempShoesImage);

    sf::Sprite *hairSprite = new sf::Sprite(*tempHairTexture);
    sf::Sprite *headSprite = new sf::Sprite(*tempHeadTexture);
    sf::Sprite *shirtSprite = new sf::Sprite(*tempShirtTexture);
    sf::Sprite *pantsSprite = new sf::Sprite(*tempPantsTexture);
    sf::Sprite *shoesSprite = new sf::Sprite(*tempShoesTexture);

    (*composite).clear();
    (*composite).draw(*headSprite);
    (*composite).draw(*shirtSprite);
    (*composite).draw(*hairSprite);
    (*composite).draw(*pantsSprite);
    (*composite).draw(*shoesSprite);
    (*composite).display();

    this->imageObj = new sf::Image((*composite).getTexture().copyToImage());
    (*this->imageObj).createMaskFromColor(sf::Color(255, 255, 255), 0);

    this->textureObj = new sf::Texture();
    (*this->textureObj).loadFromImage(*imageObj);

    this->spriteObj = new sf::Sprite(*textureObj);

    delete composite;

    delete hairSprite;
    delete headSprite;
    delete shirtSprite;
    delete pantsSprite;
    delete shoesSprite;

    delete tempHairTexture;
    delete tempHeadTexture;
    delete tempShirtTexture;
    delete tempPantsTexture;
    delete tempShoesTexture;

    delete tempHairImage;
    delete tempHeadImage;
    delete tempShirtImage;
    delete tempPantsImage;
    delete tempShoesImage;

}

TransparentSprite::~TransparentSprite() {

}

void TransparentSprite::loadNewTransparentTexture(std::string fileName) {
    (*(this->imageObj)).loadFromFile(fileName);
    (*(this->imageObj)).createMaskFromColor(sf::Color(255, 255, 255), 0);

    (*(this->textureObj)).loadFromImage(*(this->imageObj));
    (*(this->spriteObj)).setTexture(*(this->textureObj));
}

bool TransparentSprite::intersection(sf::Sprite otherSprite) {
    return ((*this->spriteObj).getGlobalBounds()).intersects(otherSprite.getGlobalBounds());
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
