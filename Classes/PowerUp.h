//
//  PowerUp.h
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 20/05/14.
//
//

#ifndef ArkanoidCocos2D_PowerUp_h
#define ArkanoidCocos2D_PowerUp_h

#include "cocos2d.h"

USING_NS_CC;

enum  {
    shoot,
    wide,
    life,
    ball
    
};
const int colorOrange[3] = {255,162,0};
const int colorPurple[3] = {196,0,255};
const int colorSoftBlue[3] = {85,210,235};

class PowerUp : public CCSprite {
    
    CCSize _screenSize;
    
public:
    
    
    
	CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
    
    
    PowerUp();
    static PowerUp * create();
    virtual void setPosition(const CCPoint& pos);
    void setupPower(int type);

};



#endif
