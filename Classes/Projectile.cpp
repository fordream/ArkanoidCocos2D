//
//  Projectile.cpp
//  ArkanoidCocos2D
//
//  Created by Javier López Punzano on 21/05/14.
//
//

#include "Projectile.h"

#define PROJECTILE_WIDTH 70
#define PROJECTILE_HEIGHT 28

using namespace cocos2d;

Projectile::Projectile() {
    _vector = ccp(0.0,3.0);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    this->setHeight(_screenSize.height / PROJECTILE_HEIGHT);
    this->setWidth(_screenSize.width / PROJECTILE_WIDTH);
}

Projectile* Projectile::create () {
	Projectile * _projectile = new Projectile();
	if (_projectile && _projectile->initWithFile("blank.png") ) {
        
        _projectile->setTextureRect(CCRectMake(0, 0, _projectile->getWidth(), _projectile->getWidth()));
        _projectile->setColor(ccc3(255,255,0));
        _projectile->autorelease();
		return _projectile;
	}
	CC_SAFE_DELETE(_projectile);
	return NULL;
}



void Projectile::setPosition(const CCPoint& pos){
    CCNode::setPosition(pos);
    if(!_nextPosition.equals(pos)){
        _nextPosition = pos;
    }
    
}


