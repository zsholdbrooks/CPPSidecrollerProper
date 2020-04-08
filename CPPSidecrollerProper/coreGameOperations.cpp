
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

    (*composite).clear(sf::Color(200, 100, 50));
    (*composite).draw(*headSprite);
    (*composite).draw(*shirtSprite);
    (*composite).draw(*hairSprite);
    (*composite).draw(*pantsSprite);
    (*composite).draw(*shoesSprite);
    (*composite).display();

    this->imageObj = new sf::Image((*composite).getTexture().copyToImage());
    (*this->imageObj).createMaskFromColor(sf::Color(200, 100, 50), 0); //

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

void TransparentSprite::move(float x, float y) {
    this->spriteObj->move(x, y);
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




PauseMenu *PauseMenu::getMenu() {
    if (!Instance) { Instance = new PauseMenu(); }
    return Instance;
}

int PauseMenu::startMenu(sf::RenderWindow& window, sf::Texture screenGrab) {
    sf::Sprite prevScreen(screenGrab);
    sf::Event menuEvent;
    int selectionState = RETURN_TO_GAME;

    sf::RectangleShape screenOverlay(sf::Vector2f(1280, 720));
    screenOverlay.setFillColor(sf::Color(100, 150, 100, 200));

    sf::Font textFont;
    textFont.loadFromFile("unispace.ttf");

    sf::Text msgRetToGame("Return to Game", textFont, 30);
    msgRetToGame.setFillColor(sf::Color::White);
    msgRetToGame.setOrigin(msgRetToGame.getLocalBounds().width / 2.0f, msgRetToGame.getLocalBounds().height / 2.0f);
    msgRetToGame.setPosition(640, 200);

    sf::RectangleShape topRect(sf::Vector2f(400, 60));
    topRect.setOrigin(topRect.getLocalBounds().width / 2.0f, topRect.getLocalBounds().height / 2.0f);
    topRect.setFillColor(sf::Color(150, 150, 150, 255));
    topRect.setOutlineColor(sf::Color::White);  //Default option as Return to Game
    topRect.setOutlineThickness(5);
    topRect.setPosition(640, 200);

    sf::Text msgQuitToMenu("Quit to Menu", textFont, 30);
    msgQuitToMenu.setFillColor(sf::Color::White);
    msgQuitToMenu.setOrigin(msgQuitToMenu.getLocalBounds().width / 2.0f, msgQuitToMenu.getLocalBounds().height / 2.0f - 3);
    msgQuitToMenu.setPosition(640, 400);

    sf::RectangleShape midRect(sf::Vector2f(400, 60));
    midRect.setOrigin(midRect.getLocalBounds().width / 2.0f, midRect.getLocalBounds().height / 2.0f);
    midRect.setFillColor(sf::Color(150, 150, 150, 255));
    midRect.setOutlineColor(sf::Color::Black);
    midRect.setOutlineThickness(5);
    midRect.setPosition(640, 400);

    sf::Text msgQuitToDesk("Quit to Desktop", textFont, 30);
    msgQuitToDesk.setFillColor(sf::Color::White);
    msgQuitToDesk.setOrigin(msgQuitToDesk.getLocalBounds().width / 2.0f, msgQuitToDesk.getLocalBounds().height / 2.0f - 3);
    msgQuitToDesk.setPosition(640, 600);

    sf::RectangleShape botRect(sf::Vector2f(400, 60));
    botRect.setOrigin(botRect.getLocalBounds().width / 2.0f, botRect.getLocalBounds().height / 2.0f);
    botRect.setFillColor(sf::Color(150, 150, 150, 255));
    botRect.setOutlineColor(sf::Color::Black);
    botRect.setOutlineThickness(5);
    botRect.setPosition(640, 600);

    // Return to Game
    // Quit to Menu
    // Quit to Desktop

    while (window.isOpen()) {
        while (window.pollEvent(menuEvent)) {
            if (menuEvent.type == sf::Event::Closed) {
                window.close();
            }
            if (menuEvent.type == sf::Event::KeyPressed) {
                if (menuEvent.key.code == sf::Keyboard::Escape) {
                    return RETURN_TO_GAME;
                }
                if (menuEvent.key.code == sf::Keyboard::Enter) {
                    return selectionState;
                }
                if (menuEvent.key.code == sf::Keyboard::Up) {
                    switch (selectionState) {
                        case RETURN_TO_GAME:
                            selectionState = QUIT_TO_DESKTOP;
                            botRect.setOutlineColor(sf::Color::White);
                            topRect.setOutlineColor(sf::Color::Black);
                            break;
                        case QUIT_TO_DESKTOP:
                            selectionState = QUIT_TO_MENU;
                            midRect.setOutlineColor(sf::Color::White);
                            botRect.setOutlineColor(sf::Color::Black);
                            break;
                        default:
                            selectionState = RETURN_TO_GAME;
                            topRect.setOutlineColor(sf::Color::White);
                            midRect.setOutlineColor(sf::Color::Black);
                    }
                }
                if (menuEvent.key.code == sf::Keyboard::Down) {
                    switch (selectionState) {
                        case RETURN_TO_GAME:
                            selectionState = QUIT_TO_MENU;
                            midRect.setOutlineColor(sf::Color::White);
                            topRect.setOutlineColor(sf::Color::Black);
                            break;
                        case QUIT_TO_MENU:
                            selectionState = QUIT_TO_DESKTOP;
                            botRect.setOutlineColor(sf::Color::White);
                            midRect.setOutlineColor(sf::Color::Black);
                            break;
                        default: 
                            selectionState = RETURN_TO_GAME;
                            topRect.setOutlineColor(sf::Color::White);
                            botRect.setOutlineColor(sf::Color::Black);
                    }
                }
            }
        }
        window.clear();

        window.draw(prevScreen);
        window.draw(screenOverlay);
        window.draw(topRect);
        window.draw(midRect);
        window.draw(botRect);
        window.draw(msgRetToGame);
        window.draw(msgQuitToMenu);
        window.draw(msgQuitToDesk);

        window.display();
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

void LevelBackground::draw(sf::RenderTexture& texture) {
    for (int i = 0; i < this->floorBackground.size(); i++) {
        texture.draw(*(floorBackground[i]->getSprite()));
    }
}

void LevelBackground::appendTileRow(int index) {
    floorBackground[index]->getSprite()->move(1888.0, 0.0);//1829
}
