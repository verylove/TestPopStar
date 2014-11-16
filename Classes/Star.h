/*
 * Star.h
 *
 *  Created on: 2014��11��16��
 *      Author: Administrator
 */

#ifndef STAR_H_
#define STAR_H_

#include "cocos2d.h"
USING_NS_CC;

class Star : public Sprite{
public:
	enum color{
		GREEN,
		RED,
		YELLOW,
		PURPLE,
		BLUE
	};

	static Star* create(int color);
	bool isSelected();
	inline void setSelected(bool b){selected = b;}
	int getColor();
	void setDesPosition(const Point& p);
	inline Point getDesPosition(){return desPosition;}//��������������C�궨��
	void updatePosition();
	inline int getIndexI(){return index_i;}
	inline int getIndexJ(){return index_j;}
	inline void setIndex_ij(int i,int j){index_i = i;index_j = j;}
private:
	char* getImage(int color); //ͨ������Ĵ���������ɫ��intֵ�ҵ���Ӧ��ͼƬ

public:
	const static int MOVE_SPEED = 4;
	static const int COLOR_MAX_NUM = 5;
	static const int STAR_WIDTH = 48;
	static const int STAR_HEIGHT = 48;

private:
	int color;
	Point desPosition;
	bool selected;
	int index_i;
	int index_j;



};




#endif /* STAR_H_ */
