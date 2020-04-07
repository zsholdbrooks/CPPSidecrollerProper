#ifndef COREGAMEOPERATIONS_HEADER
#define COREGAMEOPERATIONS_HEADER

#include <SFML/Graphics.hpp>
//#include <vector>

class TransparentSprite {
public:
	TransparentSprite();
	TransparentSprite(std::string fileName);
	TransparentSprite(std::string fileName, float originX, float originY);
	TransparentSprite(std::string hair, std::string head,
		std::string shirt, std::string pants, std::string shoes);

	~TransparentSprite();

	sf::Sprite *getSprite();
	void loadNewTransparentTexture(std::string fileName);
	bool intersection(sf::Sprite otherSprite);

private:

	sf::Sprite *spriteObj;

	sf::Texture *textureObj;

	sf::Image *imageObj;
};

class LevelBackground {
public:
	LevelBackground();
	LevelBackground(std::string baseFile);
	~LevelBackground();

	void move(float x, float wrapDelimiter);
	void draw(sf::RenderWindow& window);
private:
	std::vector<TransparentSprite*> floorBackground;
	std::vector<TransparentSprite*> wallBackground;
	std::string baseTileFileName;

	//Derived classes can change how new tile rows are added allowing downtown
	virtual void appendTileRow(int index);
	
};


class PauseMenu final {
public:
	static PauseMenu& getMenu();
	int startMenu(sf::RenderWindow *window);

private:
	PauseMenu();
	~PauseMenu() {};
	static PauseMenu *Instance;

};

void setSprite(sf::Sprite* spriteToMove, float x, float y);

void moveSprite(sf::Sprite* spriteToMove, float x, float y);
#endif // !