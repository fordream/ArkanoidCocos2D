//
//  Block.h
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 14/05/14.
//
//
#ifndef __BLOCK_H__
#define __BLOCK_H__



#include "cocos2d.h"

USING_NS_CC;


enum  {
    blue,
    yellow,
    red
    
};
const int colorRed[3] = {255,0,0};
const int colorBlue[3] = {0,0,255};
const int colorYellow[3] = {255,255,0};

class Block : public CCSprite {
    
    CCSize _screenSize;
    void initBlock(void);
    
public:
    
    int _blockWidth;
    int _blockHeight;
    
    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE(float, _width, Width);    
	CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(int, _lifes, Lifes);
    
    
    Block();
    ~Block();
    
    static Block * create();
    static float getBlockWidth();
    static float getBlockHeight();
    void setupBlock (int type);
    
    void setCol();
    
    inline virtual int left() {
    	return this->getPositionX();
	}
    
	inline virtual int right() {
    	return this->getPositionX() + _width;
	}
    
    inline virtual int top() {
        return this->getHeight();
    }
    
    inline virtual int bottom() {
		return 0;
    }
    
    
};

#endif // __BLOCK_H__
