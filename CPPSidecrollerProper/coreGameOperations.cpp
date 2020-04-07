
#include "coreGameOperations.h"
#include <SFML/Graphics.hpp>


TransparentSprite::TransparentSprite() {
    this->imageObj = 0;
    this->textureObj = 0;
    this->spriteObj = 0;
}

TransparentSprite::TransparentSprite(std::string fileName) : TransparentSprite(fileName, 0, 0) {}

TransparentSprite::TransparentSprite(std::string fileName, float originX, float originY) {
    imageObj = new sf::Image;
    textureObj = new sf::Texture;
    spriteObj = new sf::Sprite;
    (*(this->imageObj)).loadFromFile(fileName);
    (*(this->imageObj)).createMaskFromColor(sf::Color(255, 255, 255), 0);

    (*(this->textureObj)).loadFromImage(*(this->imageObj));
    (*(this->spriteObj)).setTexture(*(this->textureObj));
    if (originX || originY) {
        this->spriteObj->setOrigin(originX, originY);
    }
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
    delete this->spriteObj;
    delete this->textureObj;
    delete this->imageObj;
}

sf::Sprite *TransparentSprite::getSprite()
{
    return spriteObj;
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

//  Pause Menu

PauseMenu* PauseMenu::Instance = nullptr;

PauseMenu::PauseMenu() {
}




PauseMenu& PauseMenu::getMenu() {
    if (!Instance) { Instance = new PauseMenu(); }
    return *Instance;
}

int PauseMenu::startMenu(sf::RenderWindow *window) {
    sf::Event menuEvent;

    while (window->isOpen()) {
        while (window->pollEvent(menuEvent)) {


        }

        window->display();
    }
    return -1;
}

// LevelBackground

LevelBackground::LevelBackground()
{
}

LevelBackground::LevelBackground(std::string baseFile) {
    for (int i = 0; i < 33; i++) {
        this->floorBackground.push_back(new TransparentSprite(baseFile, 600, -160));
        (floorBackground[i]->getSprite())->setPosition(i * 59.0, 0.0);
    }
}

LevelBackground::~LevelBackground()
{
}

// Positive number moves object right across screen

void LevelBackground::move(float x, float wrapDelimiter) {
    for (int i = 0; i < this->floorBackground.size(); i++) {
        floorBackground[i]->getSprite()->move(x, 0.0);
        if (floorBackground[i]->getSprite()->getPosition().x < wrapDelimiter) {
            appendTileRow(i);
        }
    }
    //floorBackground[0]->getSprite()->get
}

void LevelBackground::draw(sf::RenderWindow& window) {
    for (int i = 0; i < this->floorBackground.size(); i++) {
        window.draw(*(floorBackground[i]->getSprite()));
    }
}

void LevelBackground::appendTileRow(int index) {
    floorBackground[index]->getSprite()->move(1888.0, 0.0);//1829
}
