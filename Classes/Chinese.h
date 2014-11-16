/*
 * Chinese.h
 *
 *  Created on: 2014Äê11ÔÂ16ÈÕ
 *      Author: Administrator
 */

#ifndef CHINESE_H_
#define CHINESE_H_

#include <string>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

static ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("ChineseWords.xml");

string ChineseWord(const char* wordId);


#endif /* CHINESE_H_ */
