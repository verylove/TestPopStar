/*
 * GameLayer.h
 *
 *  Created on: 2014��11��14��
 *      Author: Yang
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
};



#endif /* GAMELAYER_H_ */
