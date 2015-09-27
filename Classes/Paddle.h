//
//  Paddle.h
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 14/05/14.
//
//

#ifndef ArkanoidCocos2D_Paddle_h
#define ArkanoidCocos2D_Paddle_h


#include "cocos2d.h"

USING_NS_CC;

using namespace cocos2d;

class Paddle : public CCSprite {
    
    CCSize _screenSize;
    void initPaddle(void);
    
public:
    
    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
    CC_SYNTHESIZE(CCTouch *, _touch, Touch);
    float _paddleWidth;
    float _paddleHeight;
    float _paddleHalfWidth;
    float _paddleHalfHeight;
    Paddle();
    ~Paddle();
    
    static Paddle * create();
    void setupPaddle (int width, int height, int type);
    
    
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

#endif // __PADDLE_H__


