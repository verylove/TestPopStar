/*
 * GameLayer.h
 *
 *  Created on: 2014��11��14��
 *      Author: Yang
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
#include "FloatWord.h"
#include "StarMatrix.h"
#include "TopMenu.h"
USING_NS_CC;
class StarMatrix;

class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void floatLevelWord();//Ʈ���ؿ���Ϣ
	void floatTargetScoreWord();//Ʈ��Ŀ�����
	void removeFloatWord();//�Ƴ��ؿ���Ϣ��Ŀ�����
	void showStarMatrix();//�������Ǿ�����������)
	virtual bool onTouchBegan(Touch* touch,Event* unused_event);
	virtual void update(float dalta);
	void reeefreshMenu();//ˢ�¶�����Ϣ
	void refreshMenu();
	void showLinkNum(int size);//��ʾ������Ϣ
	void hideLinkNum();//����������Ϣ
	void floatLeftStarMsg(int leftNum);//��ʾʣ����������
	void gotoNextLevel();//��ת��һ��
	void gotoGameOver();//��Ϸ����
private:
	FloatWord* _levelMsg;//�ؿ���Ϣ��Ʈ�֣�
	FloatWord* _targetScore;//Ŀ�����(Ʈ�֣�
	TopMenu* menu;//������Ϣ
	StarMatrix* matrix;//������Ϣ
	Label* linkNum;//������Ϣ

};



#endif /* GAMELAYER_H_ */
