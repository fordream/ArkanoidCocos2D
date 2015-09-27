
#define TILE_H_SIZE 34
#define TILE_W_SIZE 8



#include "Block.h"

Block::~Block () {
}

Block::Block () {
    

    //get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();
    _blockWidth = _screenSize.width / TILE_W_SIZE;
    _blockHeight = _screenSize.height / TILE_H_SIZE;
    this->setVisible(true);
    
}

Block * Block::create () {
    
    Block * block = new Block();
	if (block && block->initWithFile("blank.png")) {
        block->setTextureRect(CCRectMake(0, 0, block->_blockWidth, block->_blockHeight));
        block->setColor(ccc3(255,255,255));
		block->initBlock();
        block->autorelease();
		return block;
	}
	CC_SAFE_DELETE(block);
	return NULL;
}

float Block::getBlockHeight(){
    return CCDirector::sharedDirector()->getWinSize().height / TILE_H_SIZE;
}
float Block::getBlockWidth(){
    return CCDirector::sharedDirector()->getWinSize().width / TILE_W_SIZE;
}

void Block::setupBlock(int type){
    switch (type) {
        case blue:
            this->setColor(ccc3(colorBlue[0],colorBlue[1],colorBlue[2]));
            this->setType(blue);
            this->setLifes(3);
            break;
        case yellow:
            this->setColor(ccc3(colorYellow[0],colorYellow[1],colorYellow[2]));
            this->setType(yellow);
            this->setLifes(2);
            break;
        case red:
            this->setColor(ccc3(colorRed[0],colorRed[1],colorRed[2]));
            this->setType(red);
            this->setLifes(1);
            break;
        default:
            break;
    }
}



void Block::initBlock() {
    
    
}

