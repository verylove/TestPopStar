/*
 * StarMatrix.h
 *
 *  Created on: 2014Äê11ÔÂ16ÈÕ
 *      Author: Administrator
 */

#ifndef STARMATRIX_H_
#define STARMATRIX_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "Star.h"
#include <deque>
using namespace std;
USING_NS_CC;
class GameLayer;
class StarMatrix : public Node{
public:
	static StarMatrix* create(GameLayer* layer);
	virtual bool init(GameLayer* layer);
	void initMatrix();
	void updateStar(float dalta);
	void onTouch(const Point& p);
	void setNeedClear(bool b);

private:
	Point getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Point& p);
	void genSelectedList(Star* s);
	void deleteSelectedList();
	void adjustMatrix();
	void refreshScore();
	bool isEnded();
	void clearMatrixOneByOne();
	int getLeftStarNum();
public:
	const static int ROW_NUM = 10;
	const static int COL_NUM = 10;
private:
	Star* stars[ROW_NUM][COL_NUM];
	deque<Star*> selectedList;
	GameLayer* m_layer;
	bool needClear;
    static float ONE_CLEAR_TIME;
	float clearSumTime;
};



#endif /* STARMATRIX_H_ */
