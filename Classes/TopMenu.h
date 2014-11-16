/*
 * TopMenu.h
 *
 *  Created on: 2014Äê11ÔÂ16ÈÕ
 *      Author: Administrator
 */

#ifndef TOPMENU_H_
#define TOPMENU_H_

#include "cocos2d.h"
USING_NS_CC;

class TopMenu : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh();
private:
	Label* highestScore;
	Label* level;
	Label* targetScore;
	Label* curScore;
};



#endif /* TOPMENU_H_ */
