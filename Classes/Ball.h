//
//  Ball.h
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 15/05/14.
//
//

#ifndef ArkanoidCocos2D_Ball_h
#define ArkanoidCocos2D_Ball_h
#include "cocos2d.h"

USING_NS_CC;


class Ball : public CCSprite {
    
    CCSize _screenSize;
    void initBall(void);
    
public:
    
    float _ballRadius;
    bool launch;
    
	CC_SYNTHESIZE(CCPoint, _pivot, Pivot);
    CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
    

    Ball();
    static Ball * create();
    virtual void setPosition(const CCPoint& pos);
    virtual void draw();
    float radius();
    
    
};


#endif
