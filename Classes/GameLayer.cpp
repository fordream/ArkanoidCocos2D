#include "GameLayer.h"
#include <math.h>
USING_NS_CC;

#define INITLIVES 4

GameLayer::~GameLayer () {
    blocks->release();
    targets->release();
    powerups->release();
    projectiles->release();
    balls->release();
}

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameLayer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    //get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();
    
    startGame();
    
    return true;
}

void GameLayer::startGame(){
    
    //Defines seed for random
    srand(time(NULL));
    
    _state = playing;
    shootstate = false;
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    _tryAgainLabel = CCLabelTTF::create("Try Again? ", "Cambria", 22);
    _tryAgainLabel->setVisible(false);
    _tryAgainLabel->setPosition(ccp(_screenSize.width/2, _screenSize.height/2 - _tryAgainLabel->getContentSize().height ));
    
    _gameOverLabel = CCLabelTTF::create("Game Over ", "Cambria", 26);
    _gameOverLabel->setVisible(false);
    _gameOverLabel->setPosition(ccp(_screenSize.width/2, _screenSize.height/2  ));
    
    this->addChild(_tryAgainLabel);
    this->addChild(_gameOverLabel);
    
    CCLabelTTF* lifeTextLabel = CCLabelTTF::create("Lifes : ", "Arial", 20);
    
    // position the label on the center of the screen
    lifeTextLabel->setPosition(ccp(origin.x + lifeTextLabel->getContentSize().width/2,
                                   origin.y + lifeTextLabel->getContentSize().height * 2) );
    
    // add the label as a child to this layer
    this->addChild(lifeTextLabel, 1);

    lives = INITLIVES;
    
    char lives_buffer[10];
    sprintf(lives_buffer,"%i", lives);
    _livesLabel = CCLabelTTF::create(lives_buffer, "Arial", 18);
    // position the label on the center of the screen
    _livesLabel->setPosition(ccp(origin.x + lifeTextLabel->getContentSize().width + _livesLabel->getContentSize().width,
                                 origin.y + lifeTextLabel->getContentSize().height * 2) );
    
    // add the label as a child to this layer
    this->addChild(_livesLabel, 1);
    

    paddle = Paddle::create();
    paddle->setPosition(ccp(visibleSize.width/2 + origin.x , paddle->_paddleHeight));
    paddle->setNextPosition(ccp(visibleSize.width/2  , paddle->_paddleHeight));
    this->addChild(paddle);
    
    balls = CCArray::create();
    balls->retain();
    
    
    ball = Ball::create();
    ball->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2 ));
    balls->addObject(ball);
    this->addChild(ball);
    
    
    //generate blocks and add them to the scene

    RandomGenerator  randAlg ;
    this->setGenerationAlgorithm(&randAlg);
    blocks = generatorAlg->generateBlocks();

    for(int i = 0; i < blocks->count(); i++)
    {
        this->addChild((Block *)blocks->objectAtIndex(i));
        //some more code hereafter...
    }
    //listen for touches
    this->setTouchEnabled(true);
    
    targets = CCArray::create();
    targets->retain();
    targets->addObjectsFromArray(blocks);
    targets->addObject(paddle);
    
    powerups = CCArray::create();
    powerups->retain();
    
    projectiles = CCArray::create();
    projectiles->retain();
    
    
    //create main loop
    this->schedule(schedule_selector(GameLayer::update));
    
}

void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	
	CCSetIterator i;
	CCTouch* touch;
    CCPoint tap;
    
	//loop through all beginning touches
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch*) (*i);
		
        if(touch) {
            if (shootstate)
                this->shootProjectiles();
            //get location in OpenGL view
    		tap = touch->getLocation();
            if (_state == over){
                if (_tryAgainLabel->boundingBox().containsPoint(tap)){
                    this->removeAllChildrenWithCleanup(true);
                    startGame();
                }
            }
            if (paddle->boundingBox().containsPoint(tap)) {
                   //store player's touch
                paddle->setTouch(touch);
            }
        	
		}
	}
}


void GameLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
	
    CCSetIterator i;
	CCTouch* touch;
    CCPoint tap;
    
    //loop through all moving touches
	for( i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch*) (*i);
		if(touch) {
			tap = touch->getLocation();
        		//if touch belongs to player
        		if (paddle->getTouch() != NULL && paddle->getTouch() == touch) {
                    CCPoint nextPosition = tap;
                    nextPosition.y = paddle->getPositionY();
                    //keep player inside screen
                    if (nextPosition.x < paddle->_paddleHalfWidth * paddle->getScaleX())
                        nextPosition.x = paddle->_paddleHalfWidth * paddle->getScaleX();
                    if (nextPosition.x > _screenSize.width - paddle->_paddleHalfWidth * paddle->getScaleX())
                        nextPosition.x = _screenSize.width - paddle->_paddleHalfWidth * paddle->getScaleX();
                    paddle->setNextPosition(nextPosition);
                    paddle->setVector(ccp(tap.x - paddle->getPositionX(), tap.y - paddle->getPositionY()));
				}
        	
		}
	}
}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
    
	CCSetIterator i;
	CCTouch* touch;
    
    //loop through all ending touches
	for( i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch*) (*i);
		
		if(touch) {
            if (paddle->getTouch() != NULL && paddle->getTouch() == touch) {
                //if touch ending belongs to this player, clear it
                paddle->setTouch(NULL);
                paddle->setVector(CCPointZero);
            }
        	
		}
	}
	
}

void GameLayer::update (float dt) {
	
    CCObject* object = NULL;

    CCARRAY_FOREACH(balls, object){
        
        Ball *ball = static_cast<Ball*>(object);
        ball->retain();
        CCPoint ballNextPosition = ball->getNextPosition();
        CCPoint ballVector = ball->getVector();
        if (ball->launch){
            ballVector = ccpMult(ballVector, 0.98f * 4);
            ball->launch = false;
        }
        else
            ballVector = ccpMult(ballVector, 1.0f) ;
        ballNextPosition.x += ballVector.x;
        ballNextPosition.y += ballVector.y;
        CCPoint paddleNextPosition;
        CCPoint paddleVector;       
        paddleNextPosition = paddle->getNextPosition();
        paddleVector = paddle->getVector();  
        
        CCRect ballRect = CCRectMake( (ballNextPosition.x - ball->getContentSize().width/2), (ballNextPosition.y - ball->getContentSize().height/2), ball->getContentSize().width, ball->getContentSize().height);
        
        
        for(int i = 0; i < targets->count(); i++)
        {
            CCSprite *target = (CCSprite *)targets->objectAtIndex(i);
            
            if (ballRect.intersectsRect(target->boundingBox())) {
                float diffx = ballNextPosition.x - target->getPositionX();
                float diffy = ballNextPosition.y - target->getPositionY();
                float mag_ball = pow(ballVector.x, 2) + pow(ballVector.y, 2);
                float force, angle;
                Block * block = dynamic_cast<Block*>(target);
                if (block != NULL){
                    
                    force = sqrt(mag_ball * 0.98f);
                    switch (block->getType()) {
                        case blue:
                            block->setupBlock(yellow);
                            break;
                        case yellow:
                            block->setupBlock(red);
                            break;
                        case red:
                            
                            this->removeChild(block);
                            int prob = rand() % 10 + 1;
                            // Likelihood set to 40% (powerup) , 60%(nothing)
                            if (prob > 6){
                                int type = rand() % 4 + 1;
                                PowerUp * _powerup = PowerUp::create();
                                CCPoint pos (block->getPositionX() , block->getPositionY() );
                                switch (type){
                                    case 1:
                                        _powerup->setupPower(wide);
                                        _powerup->setPosition(pos);
                                        this->addChild(_powerup);
                                        powerups->addObject(_powerup);
                                        break;
                                    case 2:
                                        _powerup->setupPower(shoot);
                                        _powerup->setPosition(pos);
                                        this->addChild(_powerup);
                                        powerups->addObject(_powerup);
                                        
                                        break;
                                    case 3:
                                        _powerup->setupPower(life);
                                        _powerup->setPosition(pos);
                                        this->addChild(_powerup);
                                        powerups->addObject(_powerup);
                                        break;
                                    case 4:
                                        Ball * extraball = Ball::create();
                                        extraball->setVector(ccp(0.0,-1.0));
                                        extraball->setPosition(block->getPosition());
                                        this->addChild(extraball);
                                        balls->addObject(extraball);
                                        break;                                        
                                }
                                
                            }
                            blocks->removeObject(block);
                            targets->removeObject(block);
                            break;
                            
                    }
                    
                    angle = atan2(diffy, diffx);
                    angle = clampf(angle,-2.2 , -0.6);
                    
                }
                else{
                    force = sqrt(mag_ball * 1.125f);
                    angle = atan2(diffy, diffx);
                }
                ballVector.x = force * cos(angle) ;
                ballVector.y = (force * sin(angle));
                ballNextPosition.x = ball->getPositionX() + ( ball->radius() + force) * cos(angle) ;
                ballNextPosition.y = ball->getPositionY() + ( ball->radius() + force) * sin(angle) ;
                
            }
        }
        //check collision of ball and sides
        if (ballNextPosition.x < ball->radius()) {
            ballNextPosition.x = ball->radius();
            ballVector.x *= -0.98f;
            
        }
        
        if (ballNextPosition.x > _screenSize.width - ball->radius()) {
            ballNextPosition.x = _screenSize.width - ball->radius();
            ballVector.x *= -0.98f;
            
        }
        //ball and top of the scene
        if (ballNextPosition.y > _screenSize.height - ball->radius()) {
            ballVector.y *= -0.98f;
            ballNextPosition.y = _screenSize.height - ball->radius();
        }
        
        
        //finally, after all checks, update ball's vector and next position
        ball->setVector(ballVector);
        ball->setNextPosition(ballNextPosition);
        
        
        //move pieces to next position
        ball->setPosition(ball->getNextPosition());
        
        //check for goals!
        if (ballNextPosition.y  < -ball->radius() * 2) {
            if (balls->count() < 2){
            // update lifes value and lives label
                lives--;
				if (lives == 0){
					_state = over;
					_tryAgainLabel->setVisible(true);
					_gameOverLabel->setVisible(true);
					unschedule(schedule_selector(GameLayer::update));
				}
				else{
					Ball  *replaceball = Ball::create();
					replaceball->setPosition(ccp(_screenSize.width/2 , _screenSize.height/2 ));
					balls->addObject(replaceball);
					this->addChild(replaceball);
				}                
            }
            balls->removeObject(ball);
            this->removeChild(ball);
            char lives_buffer[10];
            sprintf(lives_buffer,"%i", lives);
            _livesLabel->setString(lives_buffer);    

        }
        ball->release();
    }
    
    paddle->setPosition(paddle->getNextPosition());
    
    this->updatePowerUps();
    
    this->updateProjectiles();


	
	
}


void GameLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void GameLayer::shootProjectiles() {
    Projectile * _projectileL = Projectile::create();
    Projectile * _projectileR = Projectile::create();
    _projectileL->setPosition(CCPoint(paddle->getPositionX() - paddle->_paddleHalfWidth, paddle->getPositionY() + paddle->_paddleHalfHeight + 30));
    _projectileR->setPosition(CCPoint(paddle->getPositionX() + paddle->_paddleHalfWidth, paddle->getPositionY() + paddle->_paddleHalfHeight + 30));
    
    projectiles->addObject(_projectileR);
    projectiles->addObject(_projectileL);
    this->addChild(_projectileL);
    this->addChild(_projectileR);
    
    
}


void GameLayer::updateProjectiles(){
    for(int i=0; i < projectiles->count(); i++){
        Projectile *projectile = (Projectile *) projectiles->objectAtIndex(i);
        projectile->retain();
        CCPoint projectileNextPosition = projectile->getNextPosition();
        CCPoint projectileVector = projectile->getVector();
        projectileVector = ccpMult(projectileVector, 1.0f);
        projectileNextPosition.x += projectileVector.x;
        projectileNextPosition.y += projectileVector.y;
        for(int j = 0; j < blocks->count(); j++)
        {
            Block *block = (Block *)blocks->objectAtIndex(j);

            if (projectile->boundingBox().intersectsRect(block->boundingBox())) {

                    switch (block->getType()) {
                        case blue:
                            block->setupBlock(yellow);
                            break;
                        case yellow:
                            block->setupBlock(red);
                            break;
                        case red:
                            
                            this->removeChild(block);
                            int prob = rand() % 10 + 1;
                            // Likelihood set to 40% (powerup) , 60%(nothing)
                            if (prob > 6){
                                int type = rand() % 4 + 1;
                                PowerUp * _powerup = PowerUp::create();
                                CCPoint pos (block->getPositionX() , block->getPositionY() );
                                switch (type){
                                    case 1:
                                        _powerup->setupPower(wide);
                                        _powerup->setPosition(pos);
                                        this->addChild(_powerup);
                                        powerups->addObject(_powerup);
                                        break;
                                    case 2:
                                        _powerup->setupPower(shoot);
                                        _powerup->setPosition(pos);
                                        this->addChild(_powerup);
                                        powerups->addObject(_powerup);
                                        
                                        break;
                                    case 3:
                                        _powerup->setupPower(life);
                                        _powerup->setPosition(pos);
                                        this->addChild(_powerup);
                                        powerups->addObject(_powerup);
                                        break;
                                    case 4:
                                        break;
                                        
                                }
                                
                            }
                            blocks->removeObject(block);
                            targets->removeObject(block);
                            break;
                            
                    }
                    //remove projectile
                    projectiles->removeObject(projectile);
                    this->removeChild(projectile);
            }
            
            
        }
        if (projectileNextPosition.y > _screenSize.height - projectile->getHeight()){
            projectiles->removeObject(projectile);
            this->removeChild(projectile);
            
        }
        else {
            //Update powerups values
            projectile->setVector(projectileVector);
            projectile->setNextPosition(projectileNextPosition);
            projectile->setPosition(projectile->getNextPosition());
        }
		projectile->release();
    }

}

void GameLayer::updatePowerUps(){
    for(int i=0; i < powerups->count(); i++){
        
        PowerUp *powerup = (PowerUp *)powerups->objectAtIndex(i);
        CCPoint powerupNextPosition = powerup->getNextPosition();
        CCPoint powerupVector = powerup->getVector();
        powerupVector = ccpMult(powerupVector, 1.01f) ;
        powerupNextPosition.x += powerupVector.x;
        powerupNextPosition.y += powerupVector.y;
        
        
        CCRect powerupRect = CCRectMake( (powerup->getPositionX() - powerup->getContentSize().width/2), (powerup->getPositionY() - powerup->getContentSize().height/2), powerup->getContentSize().width, powerup->getContentSize().height);
        if (paddle->boundingBox().intersectsRect(powerupRect)){
         
            switch (powerup->getType()) {
                case life:
                {
                    lives++;
                    char lives_buffer[10];
                    sprintf(lives_buffer,"%i", lives);
                    _livesLabel->setString(lives_buffer);
                    break;
                }
                case wide:
                {
                    paddle->stopActionByTag(paddlesequence);
                    CCScaleTo *scalebigger = CCScaleTo::create(0,1.5,1.0);
                    CCScaleTo *scalesmaller = CCScaleTo::create(0,1.0,1.0);
                    CCDelayTime *delay = CCDelayTime::create(7);
                    // prevent sprite from disappearing
                    CCShow *show = CCShow::create();
                    CCBlink *blink = CCBlink::create(3, 10);
                    CCSequence * padsequence = CCSequence::create(show,scalebigger,delay,blink,scalesmaller, NULL);
                    padsequence->setTag(paddlesequence);
                    paddle->runAction(padsequence);
                    break;
                    
                }
                case shoot:
                {
                    paddle->stopActionByTag(shootsequence);
                    CCDelayTime *delay = CCDelayTime::create(3);
                    CCCallFuncN *enable = CCCallFuncN::create(this, callfuncN_selector(GameLayer::enableShoot));
                    CCCallFuncN *disable = CCCallFuncN::create(this, callfuncN_selector(GameLayer::disableShoot));
                    CCSequence * shsequence = CCSequence::create(enable,delay,disable, NULL);
                    shsequence->setTag(shootsequence);
                    this->runAction(shsequence);

                    break;
                }
                    
            }
            powerups->removeObject(powerup);
            this->removeChild(powerup);
        }
        
        else if (powerupNextPosition.y < -powerup->getHeight() * 2){
            powerups->removeObject(powerup);
            this->removeChild(powerup);
            
        }
        else{
            //Update powerups values
            powerup->setVector(powerupVector);
            powerup->setNextPosition(powerupNextPosition);
            powerup->setPosition(powerup->getNextPosition());
        }
    }


}

void GameLayer::setGenerationAlgorithm(IBlockGenerator *algorithm){
    this->generatorAlg = algorithm;
}

void GameLayer::enableShoot(cocos2d::CCNode *sender){
    shootstate = true;
}

void GameLayer::disableShoot(cocos2d::CCNode *sender){
    shootstate = false;
}



