...

bool GameScene::init()
{
        ...

	//Show Board
	showBoard();

	return true;
}

Layer* GameScene::showBoard()
{
	std::vector<int> count(16, 4);
	Board* board = new Board(8, 8, 16, count);
	auto boardView = BoardView::createBoardView(board);
	this->addChild(boardView, 1);
	float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
	float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;
	boardView->setPosition({x, y});
	return boardView;
}