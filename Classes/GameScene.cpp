/*
 * GameScene.cpp
 *
 *  Created on: 2014Äê11ÔÂ14ÈÕ
 *      Author: Yang
 */

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Audio.h"
#include "GameLayer.h"

USING_NS_CC;



bool GameScene::init()
{
	if(!Scene::init())
	{
		return false;
	}

	Audio::getInstance()->playBGM();
	this->addChild(GameLayer::create());


	return true;
}


