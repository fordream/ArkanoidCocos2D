//
//  IBlockGenerator.h
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 22/05/14.
//
//

#ifndef ArkanoidCocos2D_IBlockGenerator_h
#define ArkanoidCocos2D_IBlockGenerator_h

#include "cocos2d.h"

USING_NS_CC;

class GameLayer;


class IBlockGenerator {
    
    
public:

    CCSize _screenSize;
    CCArray * _blocks;    
    virtual CCArray *  generateBlocks() = 0;
    virtual void generateRow(int offsetX, int offsetY) = 0;
    
    
};

class RandomGenerator : public IBlockGenerator {
    
public:

    CCSize _screenSize;
    CCArray * _blocks;
    virtual CCArray * generateBlocks();
    virtual void generateRow(int offsetX, int offsetY);
    
    
};



#endif
