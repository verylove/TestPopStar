/*
 * GameLayer.cpp
 *
 *  Created on: 2014Äê11ÔÂ14ÈÕ
 *      Author: Yang
 */


#include "GameLayer.h"
USING_NS_CC;

bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	return true;
}

