#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "PowerUp.h"
#include "Projectile.h"
#include "IBlockGenerator.h"

using namespace cocos2d;


enum GameState{
    playing,
    over
};

enum Sequence{
    paddlesequence,
    shootsequence
};

class GameLayer : public cocos2d::CCLayer
{
    int lives;
public:
    CCSprite * quickSprite;
    Paddle * paddle;
    Ball * ball;
    CCArray * blocks, * targets, *powerups, *projectiles, *balls;
    CCLabelTTF * _livesLabel, *_tryAgainLabel, *_gameOverLabel;
    int filledHeight;
    GameState _state;
    bool shootstate;
    IBlockGenerator * generatorAlg;
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    //THE OVERRIDES
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    
    void setGenerationAlgorithm(IBlockGenerator * algorithm);
    void enableShoot(CCNode* sender);
    void disableShoot(CCNode* sender);
    void updatePowerUps();
    void updateProjectiles();
    void shootProjectiles();
    void generateBlocks();
    void generateRow(int offsetX, int offsetY);
    void startGame();
    void update (float dt);
    
    
    ~GameLayer();
     CCSize _screenSize;
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
};

#endif // __HELLOWORLD_SCENE_H__
