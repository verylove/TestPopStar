/*
 * MenuScene.cpp
 *
 *  Created on: 2014��11��14��
 *      Author: Yang
 */


#include "MenuScene.h"
#include "Audio.h"
#include "MenuLayer.h"

USING_NS_CC;

bool MenuScene::init()
{
	if(!Scene::init()){
		return false;
	}

	//Audio::getInstance()->playBGM();
	this->addChild(MenuLayer::create());
	return true;
}

