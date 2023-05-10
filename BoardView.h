#include <cocos2d.h>
#include <Board.h>

USING_NS_CC;

class BoardView : public Layer
{
	Board* board;

	float squareSize, width, height;

	std::vector<std::vector<Sprite*>> pokemons;

public:

	static Layer* createBoardView(Board* board);

	void showBoard();

	Sprite* addPokemon(int row, int column, int type);

	Vec2 positionOf(int row, int column);

	std::pair<int, int> findRowAndColumnOfSprite(Node* node);

	bool removePokemon(int row, int column);

	CREATE_FUNC(BoardView);
};