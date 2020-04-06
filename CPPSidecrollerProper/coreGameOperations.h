#ifndef COREGAMEOPERATIONS_HEADER
#define COREGAMEOPERATIONS_HEADER

#include <SFML/Graphics.hpp>

class TransparentSprite {
public:
	TransparentSprite();
	TransparentSprite(std::string fileName);

	~TransparentSprite();

	void loadNewTransparentTexture(std::string fileName);
	bool intersection(sf::Sprite otherSprite);

private:

	sf::Sprite spriteObj;

	sf::Texture textureObj;

	sf::Image imageObj;
};



void setSprite(sf::Sprite* spriteToMove, float x, float y);

void moveSprite(sf::Sprite* spriteToMove, float x, float y);
#endif // !