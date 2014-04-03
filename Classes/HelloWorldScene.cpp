#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	addBackground();

	addBall();

	playerHandleBall();

    return true;
}

void HelloWorld::addBackground()
{
	Sprite* sprite = Sprite::create("background.jpg");

	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);
}

void HelloWorld::addBall()
{
	ball = Sprite::create("ball.png");

	ball->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(ball, 1);
}

void HelloWorld::playerHandleBall()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);

	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event_)
{
	float speed = 1000;

	Point start = ball->getPosition();
	Point end;
	if (keyCode == EventKeyboard::KeyCode::KEY_A) 
	{
		end = Point(0, ball->getPositionY());

		float distance = ccpDistance(start, end);
		float duration = distance / speed;

		CCFiniteTimeAction* actionMove =
			CCMoveTo::create(duration, end);

		actionMove->setTag(0);

		ball->runAction(actionMove);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		end = Point(visibleSize.width, ball->getPositionY());

		float distance = ccpDistance(start, end);
		float duration = distance / speed;

		CCFiniteTimeAction* actionMove =
			CCMoveTo::create(duration, end);

		actionMove->setTag(1);

		ball->runAction(actionMove);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		end = Point(ball->getPositionX(), visibleSize.height);

		float distance = ccpDistance(start, end);
		float duration = distance / speed;

		CCFiniteTimeAction* actionMove =
			CCMoveTo::create(duration, end);
		
		actionMove->setTag(2);

		ball->runAction(actionMove);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		end = Point(ball->getPositionX(), 0);

		float distance = ccpDistance(start, end);
		float duration = distance / speed;

		CCFiniteTimeAction* actionMove =
			CCMoveTo::create(duration, end);

		actionMove->setTag(3);

		ball->runAction(actionMove);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		ball->setScale(ball->getScale() / 1.2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		ball->setScale(ball->getScale() * 1.2);
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event_)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		ball->stopActionByTag(0);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		ball->stopActionByTag(1);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		ball->stopActionByTag(2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		ball->stopActionByTag(3);
	}
}
