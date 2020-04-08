// These "include" code from the C++ library and SFML too
//#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include "coreGameOperations.h"

//#define KEY_PRESSED 
#define SINGLE_KEY_REP 1

void createTransparentSprite(sf::Sprite *targetSprite, sf::Image *tempImg, sf::Texture *tempTexture, std::string fileName) {
    //sf::Image tempImg;
    (*tempImg).loadFromFile(fileName);
    (*tempImg).createMaskFromColor(sf::Color(255, 255, 255), 0);

    //sf::Texture tempTexture;
    (*tempTexture).loadFromImage(*tempImg);
    (*targetSprite).setTexture(*tempTexture);
    return;
}

// It is where our game starts from
int main()
{
    sf::Clock clock;
    bool Up = false;
    bool Down = false;
    bool Right = false;
    bool Left = false;
    int LShift = 1;
    // Make a window that is 800 by 200 pixels
    // And has the title "Hello from SFML"
    sf::RenderWindow window(sf::VideoMode(1280, 720), "CPP Sidescroller");

    PauseMenu* pause = pause->getMenu();
    sf::RenderTexture screenGrab;
    screenGrab.create(1280, 720);

    sf::Sprite transDude;
    sf::Image dudeImg;
    sf::Texture transText;

    createTransparentSprite(&transDude, &dudeImg, &transText, "ModestAttemptx4.png");
    transDude.setPosition(400, 300);

    /*sf::Sprite floor;
    sf::Texture *floorPic = new sf::Texture;
    if (!(*floorPic).loadFromFile("TexturedFloor650.png")) {
        return -1;
    }
    floor.setTexture(*floorPic);
    floor.setPosition(100, 0);*/
    TransparentSprite floor("TexturedFloor650.png");
    floor.getSprite()->setPosition(-620, 160); //620 width pic, 60 width tile
    //1280/60
    
    LevelBackground backing("TexturedFloor650.png");
    //delete floorPic;
    sf::Sprite dude;
    sf::Texture dudePic;
    if (!dudePic.loadFromFile("ModestAttemptx4small.png")) {
        return -1;
    }
    dude.setTexture(dudePic);
    dude.setPosition(300, 300);

    // Text
    sf::Text newMessage;
    sf::Font textFont;
    textFont.loadFromFile("unispace.ttf");
    newMessage.setFont(textFont);
    newMessage.setString("Quit to Menu");
    newMessage.setCharacterSize(30);
    newMessage.setFillColor(sf::Color::Red);
    newMessage.setOrigin(newMessage.getLocalBounds().width/2.0f, newMessage.getLocalBounds().height/2.0f);
    newMessage.setPosition(400, 400);

    sf::RectangleShape outerRect(sf::Vector2f(300, 60));
    outerRect.setOrigin(outerRect.getLocalBounds().width / 2.0f, outerRect.getLocalBounds().height / 2.0f);
    outerRect.setFillColor(sf::Color(150, 150, 150, 255));
    outerRect.setOutlineColor(sf::Color::Black);
    outerRect.setOutlineThickness(5);
    outerRect.setPosition(400, 400);

    sf::RectangleShape screenOverlay;
    //screenOverlay.setOrigin(150, 30);
    screenOverlay.setSize(sf::Vector2f(1280, 720));
    screenOverlay.setFillColor(sf::Color(100, 150, 100, 200));
    screenOverlay.setOutlineColor(sf::Color::Black);
    screenOverlay.setOutlineThickness(5);
    
    // Start Composite creation here
    sf::RenderTexture *comp = new sf::RenderTexture;
    if (!(*comp).create(40, 133)) {
        return -1;
    }
    sf::Texture *tImg = new sf::Texture;
    (*tImg).loadFromFile("top.png");
    sf::Sprite *tSprite = new sf::Sprite(*tImg);

    sf::Image *tempImg = new sf::Image;
    (*tempImg).loadFromFile("bottom.png");
    //(*tempImg).createMaskFromColor(sf::Color(255, 255, 255), 0);
    sf::Texture *bImg = new sf::Texture;
    (*bImg).loadFromImage(*tempImg);
    sf::Sprite *bSprite = new sf::Sprite(*bImg);

    (*comp).clear();
    (*comp).draw(*bSprite);
    (*comp).draw(*tSprite);
    (*comp).display();
    
    sf::Image newTempImg((*comp).getTexture().copyToImage());
    newTempImg.createMaskFromColor(sf::Color(255, 255, 255), 0);
    
    sf::Texture transCompText;
    transCompText.loadFromImage(newTempImg);
    sf::Sprite compSprite(transCompText);
    delete tSprite;
    delete tImg;
    delete comp;

    // End composite creation here

    compSprite.setPosition(200, 300);


#if SINGLE_KEY_REP
    window.setKeyRepeatEnabled(false);
#endif

float displacement = 100.0;

// This "while" loop goes round and round- perhaps forever
while (window.isOpen())
{
    // The next 6 lines of code detect if the window is closed
    // And then shuts down the program
    sf::Event event;
    float deltaTime = clock.restart().asSeconds();

    while (window.pollEvent(event)) {
#if SINGLE_KEY_REP
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                Up = true;
            }
            if (event.key.code == sf::Keyboard::Down) {
                Down = true;
            }
            if (event.key.code == sf::Keyboard::Left) {
                Left = true;
            }
            if (event.key.code == sf::Keyboard::Right) {
                Right = true;
            }
            if (event.key.code == sf::Keyboard::LShift) LShift = 2;
            if (event.key.code == sf::Keyboard::Escape) {
                screenGrab.clear(sf::Color(100, 100, 100));
                backing.draw(screenGrab);
                screenGrab.draw(transDude);
                screenGrab.display();
                pause->startMenu(window, screenGrab.getTexture());
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Up) {
                Up = false;
            }
            if (event.key.code == sf::Keyboard::Down) {
                Down = false;
            }
            if (event.key.code == sf::Keyboard::Left) {
                Left = false;
            }
            if (event.key.code == sf::Keyboard::Right) {
                Right = false;
            }
            if (event.key.code == sf::Keyboard::LShift) LShift = 1;
        }


    }
    if (Up) {
        if (Right) moveSprite(&transDude, displacement * deltaTime * LShift, -displacement * deltaTime * LShift);
        else if (Left) moveSprite(&transDude, -displacement * deltaTime * LShift, -displacement * deltaTime * LShift);
        else moveSprite(&transDude, 0, -displacement * deltaTime * LShift);
    }
    else if (Down) {
        if (Right) moveSprite(&transDude, displacement * deltaTime * LShift, displacement * deltaTime * LShift);
        else if (Left) moveSprite(&transDude, -displacement * deltaTime * LShift, displacement * deltaTime * LShift);
        else moveSprite(&transDude, 0, displacement * deltaTime * LShift);
    }
    else if (Left) moveSprite(&transDude, -displacement * deltaTime * LShift, 0);
    else if (Right) moveSprite(&transDude, displacement * deltaTime * LShift, 0);

#else
        // Y axis is flipped. First pixel is top left?
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
            if (/*!event.type == sf::Event::KeyReleased && */event.key.code == sf::Keyboard::Right) {
                moveSprite(&transDude, displacement, -displacement);
            }
            else if (event.key.code == sf::Keyboard::Left) {
                moveSprite(&transDude, -displacement, -displacement);
            }
            else {
                moveSprite(&transDude, 0, -displacement);
            }
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
            if (event.key.code == sf::Keyboard::Right) {
                moveSprite(&transDude, displacement, displacement);
            }
            else if (event.key.code == sf::Keyboard::Left) {
                moveSprite(&transDude, -displacement, displacement);
            }
            else {
                moveSprite(&transDude, 0, displacement);
            }
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
            moveSprite(&transDude, -displacement, 0);
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
            moveSprite(&transDude, displacement, 0);
        }
}
#endif

    if (event.type == sf::Event::Closed)
        // Someone closed the window- bye
        window.close();
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
        moveSprite(&transDude, 2, 2);
    }

    if ((transDude.getGlobalBounds()).intersects(dude.getGlobalBounds())) {
        dude.move(-10, -10);
    }
        // Clear everything from the last run of the while loop
        //window.clear();
    backing.move(-displacement * deltaTime * LShift, 59 * -0);

    window.clear(sf::Color(100, 100, 100));

    //window.draw(*floor.getSprite());
    backing.draw(window);
    //window.draw(dude);
    window.draw(transDude);
    //window.draw(compSprite);
    //window.draw(outerRect);
    //window.draw(newMessage);

    // Show everything we just drew
    window.display();

    
}// This is the end of the "while" loop

    return 0;
}