//
//  PowerUp.cpp
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 20/05/14.
//
//

#include "PowerUp.h"

#define POWERUP_SIZE 32

using namespace cocos2d;

PowerUp::PowerUp() {
    _vector = ccp(0.0,-1);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    this->setHeight(_screenSize.height / POWERUP_SIZE);
    this->setWidth(_screenSize.width / POWERUP_SIZE);
}

PowerUp* PowerUp::create () {
	PowerUp * _powerup = new PowerUp();
	if (_powerup && _powerup->initWithFile("blank.png") ) {
        _powerup->setTextureRect(CCRectMake(0, 0, _powerup->getWidth(), _powerup->getWidth()));
        _powerup->autorelease();
		return _powerup;
	}
	CC_SAFE_DELETE(_powerup);
	return NULL;
}



void PowerUp::setPosition(const CCPoint& pos){
    CCNode::setPosition(pos);
    if(!_nextPosition.equals(pos)){
        _nextPosition = pos;
    }
    
}

void PowerUp::setupPower(int type){

    switch (type) {
        case shoot:
            this->setColor(ccc3(colorOrange[0],colorOrange[1],colorOrange[2]));
            this->setType(shoot);
            break;
        case wide:
            this->setColor(ccc3(colorPurple[0],colorPurple[1],colorPurple[2]));
            this->setType(wide);
            break;
        case life:
            this->setColor(ccc3(colorSoftBlue[0],colorSoftBlue[1],colorSoftBlue[2]));
            this->setType(life);
            break;
        default:
            break;
    }

}
