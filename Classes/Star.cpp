/*
 * Star.cpp
 *
 *  Created on: 2014Äê11ÔÂ16ÈÕ
 *      Author: Administrator
 */


#include "Star.h"

USING_NS_CC;

Star* Star::create(int color){
	Star* ret = new Star();
	if(ret && ret->initWithFile(ret->getImage(color))){
		ret->color = color;
		ret->selected = false;
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);

	return nullptr;
}

char* Star::getImage(int color){
	switch(color){
	case color::BLUE:
		return "blue.png";
	case color::GREEN:
		return "green.png";
	case color::YELLOW:
		return "orange.png";
	case color::RED:
		return "red.png";
	case color::PURPLE:
		return "purple.png";
	}
}

bool Star::isSelected(){
	return selected;
}

int Star::getColor(){
	return color;
}

void Star::setDesPosition(const Point& p){
	desPosition = p;
}

void Star::updatePosition(){
	if(desPosition.y != getPositionY()){
		setPositionY(getPositionY() - MOVE_SPEED);
		if(getPositionY() < desPosition.y){
			setPositionY(desPosition.y);
		}
	}
	if(desPosition.x != getPositionX()){
		setPositionX(getPositionX() - MOVE_SPEED);
		if(getPositionX() < desPosition.x){
			setPositionX(desPosition.x);
	}
}
}
