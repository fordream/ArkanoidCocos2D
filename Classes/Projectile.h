//
//  Projectile.h
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 21/05/14.
//
//

#ifndef ArkanoidCocos2D_Projectile_h
#define ArkanoidCocos2D_Projectile_h

#include "cocos2d.h"

USING_NS_CC;



class Projectile : public CCSprite {
    
    CCSize _screenSize;
    
public:

    CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
    
    
    Projectile();
    static Projectile * create();
    virtual void setPosition(const CCPoint& pos);

    
};



#endif


