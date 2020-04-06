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

class PauseMenu final {
public:
	PauseMenu* getMenu();


private:
	PauseMenu();
	~PauseMenu() {};
	static PauseMenu *Instance;
	//static PauseMenu *Instance = new PauseMenu();

};

void setSprite(sf::Sprite* spriteToMove, float x, float y);

void moveSprite(sf::Sprite* spriteToMove, float x, float y);
#endif // !