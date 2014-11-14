/*
 * MenuLayer.h
 *
 *  Created on: 2014Äê11ÔÂ14ÈÕ
 *      Author: Yang
 */

#ifndef MENULAYER_H_
#define MENULAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class MenuLayer : public Layer
{
public:
		virtual bool init();

		CREATE_FUNC(MenuLayer);

		void startGame(Ref* ref);

};



#endif /* MENULAYER_H_ */
