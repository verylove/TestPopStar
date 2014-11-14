/*
 * MenuLayer.cpp
 *
 *  Created on: 2014Äê11ÔÂ14ÈÕ
 *      Author: Yang
 */

#include "MenuLayer.h"

#include "GameScene.h"

USING_NS_CC;


bool MenuLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_menuscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	MenuItemImage* startBtn = MenuItemImage::create(
			"menu_start.png","menu_star.png",CC_CALLBACK_1(MenuLayer::startGame,this)
	);


	Menu* menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);


	return true;
}

void MenuLayer::startGame(Ref* ref)
{
	Director::getInstance()->replaceScene(GameScene::create());
}
