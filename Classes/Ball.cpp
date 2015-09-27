//
//  Ball.cpp
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 15/05/14.
//
//

#include "Ball.h"
#define BALL_SIZE 30

using namespace cocos2d;

Ball::Ball() {
    _vector = ccp(0.0,1);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _pivot = ccp(-1,1);
    _ballRadius = _screenSize.height / BALL_SIZE;
    
}

Ball* Ball::create () {
	Ball * ball = new Ball();
	if (ball ) {
        ball->launch = true;
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return NULL;
}

void Ball::draw(){

    cocos2d::ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
    cocos2d::ccDrawSolidCircle( _pivot, _ballRadius, CC_DEGREES_TO_RADIANS(90), 50, false);

}

void Ball::setPosition(const CCPoint& pos){
    CCNode::setPosition(pos);
    if(!_nextPosition.equals(pos)){
        _nextPosition = pos;
    }
    
}

float Ball::radius(){
    return _ballRadius;
}
