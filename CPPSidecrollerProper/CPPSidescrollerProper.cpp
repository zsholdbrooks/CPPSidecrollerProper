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

    
    //floor is 620 width pic, 60 width tile
    
    LevelBackground backing("TexturedFloor650.png");

    /*if (!dudePic.loadFromFile("ModestAttemptx4small.png")) {
        return -1;
    }*/
       
    TransparentSprite compTest("hair.png", "body.png", "shirt.png", "pants.png", "shoes.png");
    compTest.getSprite()->setPosition(400, 200);


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
                Up = false;
                Down = false;
                Left = false;
                Right = false;

                screenGrab.clear(sf::Color(100, 100, 100));
                backing.draw(screenGrab);
                screenGrab.draw(*compTest.getSprite());
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
        if (Right) compTest.move(displacement * deltaTime * LShift, -displacement * deltaTime * LShift);
        else if (Left) compTest.move(-displacement * deltaTime * LShift, -displacement * deltaTime * LShift);
        else compTest.move(0, -displacement * deltaTime * LShift);
    }
    else if (Down) {
        if (Right) compTest.move(displacement * deltaTime * LShift, displacement * deltaTime * LShift);
        else if (Left) compTest.move(-displacement * deltaTime * LShift, displacement * deltaTime * LShift);
        else compTest.move(0, displacement * deltaTime * LShift);
    }
    else if (Left) compTest.move(-displacement * deltaTime * LShift, 0);
    else if (Right) compTest.move(displacement * deltaTime * LShift, 0);

    if (event.type == sf::Event::Closed)
        // Someone closed the window- bye
        window.close();
    /*if ((transDude.getGlobalBounds()).intersects(dude.getGlobalBounds())) {
        dude.move(-10, -10);
    }*/
        // Clear everything from the last run of the while loop
        //window.clear();
    backing.move(-displacement * deltaTime * LShift, 59 * -0);

    window.clear(sf::Color(100, 100, 100));

    //window.draw(*floor.getSprite());
    backing.draw(window);
    window.draw(*compTest.getSprite());

    // Show everything we just drew
    window.display();

    
}// This is the end of the "while" loop

    return 0;
}