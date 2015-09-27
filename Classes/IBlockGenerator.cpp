//
//  IBlockGenerator.cpp
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 22/05/14.
//
//

#include "IBlockGenerator.h"
#include "Block.h"

using namespace cocos2d;


CCArray * RandomGenerator::generateBlocks(){
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _blocks = CCArray::create();
    _blocks->retain();
    float maxHeight = (_screenSize.height/2);
    int filledHeight = _screenSize.height;
    int offsetX = 40, offsetY = 10;
    int paddingY = 4;
    while (filledHeight  > maxHeight ){

        generateRow(offsetX, offsetY);
        offsetY += Block::getBlockHeight() + paddingY;
        filledHeight = filledHeight - Block::getBlockHeight() - offsetY;
    }
    return _blocks;

}

void RandomGenerator::generateRow(int offsetX, int offsetY){
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    int nblocks = ((_screenSize.width - offsetX * 2 )/ Block::getBlockWidth());
    int paddingX = 4;
    int nextPositionX = (_screenSize.width - (nblocks * Block::getBlockWidth()) - (paddingX * nblocks)   + Block::getBlockWidth())/2;

    for (int i = 0; i < nblocks; i++) {
        Block * block = Block::create();
        block->setPosition(ccp(nextPositionX ,_screenSize.height - offsetY));
        int type = rand() % 3 + 1;
        switch (type){
            case 1:
                block->setupBlock(blue);
                break;
            case 2:
                block->setupBlock(yellow);
                break;
            case 3:
                block->setupBlock(red);
                break;
        }
        nextPositionX += block->_blockWidth + paddingX;
        _blocks->addObject(block);
    }

}