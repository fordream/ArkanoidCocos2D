//
//  Paddle.cpp
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 14/05/14.
//
//
#define PADDLE_H_SIZE 120
#define PADDLE_W_SIZE 6


#include "Paddle.h"

Paddle::~Paddle () {
}

Paddle::Paddle () {
    
    //get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();
    _paddleWidth = _screenSize.width / PADDLE_W_SIZE;
    _paddleHeight = _screenSize.height / PADDLE_H_SIZE;
    _paddleHalfWidth = _paddleWidth/2;
    _paddleHalfHeight = _paddleHeight/2;

    this->setVisible(true);
    
}

Paddle * Paddle::create () {
    
    Paddle * paddle = new Paddle();
	if (paddle && paddle->initWithFile("blank.png")) {
        paddle->setTextureRect(CCRectMake(0, 0, paddle->_paddleWidth, paddle->_paddleHalfWidth));
        paddle->setColor(ccc3(124,252,0));
		//paddle->initPaddle();
        paddle->autorelease();
		return paddle;
	}
	CC_SAFE_DELETE(paddle);
	return NULL;
}


void Paddle::setupPaddle (int width, int height, int type) {
    
    
}

void Paddle::initPaddle() {
    
    
}
