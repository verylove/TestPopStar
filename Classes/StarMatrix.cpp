/*
 * StarMatrix.cpp
 *
 *  Created on: 2014年11月16日
 *      Author: Administrator
 */


#include "StarMatrix.h"
#include "GameData.h"
#include "StarParticle.h"
#include "ComboEffect.h"
#include "Audio.h"
#include <ctime>
float StarMatrix::ONE_CLEAR_TIME = 0.05f;

USING_NS_CC;

StarMatrix* StarMatrix::create(GameLayer* layer){
	StarMatrix* ret = new StarMatrix();
	if(ret && ret->init(layer)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool StarMatrix::init(GameLayer* layer){
	if(!Node::init()){
		return false;
	}
	m_layer = layer;
	needClear = false;
	clearSumTime = 0;
	memset(stars, 0, sizeof(Star*) * ROW_NUM * COL_NUM);
	initMatrix();
	return true;
}

void StarMatrix::initMatrix(){
	srand(time(0));
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<ROW_NUM;j++){
			int color = abs(rand()%Star::COLOR_MAX_NUM);
			Star* star = Star::create(color);
			stars[i][j] = star;
			star->setPosition(getPositionByIndex(i,j)+Point(0,100));//当前位置,就是星星当前所处的位置，是可以改变的
			star->setDesPosition(getPositionByIndex(i,j));//目标位置,是星星要到达的位置，如果星星的当前位置不等于目标星星，星星的当前位置会不断地改变，直到移动到目标位置
			star->setIndex_ij(i,j);//矩阵中位置
			this->addChild(star);
		}
	}
}

Point StarMatrix::getPositionByIndex(int i,int j){
	float x = j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y = (StarMatrix::COL_NUM - i)*Star::STAR_HEIGHT - Star::STAR_HEIGHT/2;
	return Point(x,y);
}

void StarMatrix::updateStar(float delta){

    for(int i = 0;i < ROW_NUM;i++){
        for(int j = 0;j< COL_NUM;j++){
            if(stars[i][j]!=nullptr){
                stars[i][j]->updatePosition();
            }
        }
    }
    if(needClear){
        clearSumTime += delta;
        if(clearSumTime > ONE_CLEAR_TIME){
            clearMatrixOneByOne();
            clearSumTime = 0;
        }
    }

}

void StarMatrix::onTouch(const Point& p){
	Star* s = getStarByTouch(p);
	if(s){
		genSelectedList(s);//得到一串连接的星星的函数
		CCLOG("SIZE = %d",selectedList.size());
		deleteSelectedList();//删除一串连接的星星的函数
	}
}


void StarMatrix::setNeedClear(bool b){
	needClear = b;
}


/*

得到一串连接星星的算法思路，这里使用了广度优先遍历，并且用了一个队列来辅助

具体步骤如下：

1.把被点击的星星放进遍历队列；

2.分别对遍历队列里面的元素进行如下操作：

1)  把该元素放进待删除的列表（就是我们要的列表）；

2）看看上方是否有相同颜色的星星，如果有，把上方的星星放进遍历队列；

3）看看下方是否有相同颜色的星星，如果有，把下方的星星放进遍历队列；

4）看看左边是否有相同颜色的星星，如果有，把左边的星星放进遍历队列；

5）看看右边是否有相同颜色的星星，如果有，把右边的星星放进遍历队列；

3.遍历队列队头出列，得到新的队头。

4.重复步骤2；
 */
Star* StarMatrix::getStarByTouch(const Point& p){
	int k = p.y/Star::STAR_HEIGHT;//这里要用K转一下int 不然得不到正确结果
	int i = ROW_NUM -1 - k;
	int j = p.x/Star::STAR_WIDTH;
	if(i >=0 && i < ROW_NUM &&
	   j >=0 && j < COL_NUM &&
	   stars[i][j] != nullptr){
		CCLOG("i=%d,j=%d",i,j);
		return stars[i][j];
	}else{
		return nullptr;
	}
}


void StarMatrix::genSelectedList(Star* s){
    selectedList.clear();//记得每次点击都要先把待删除列表清空
    deque<Star*> travelList;//遍历队列
    travelList.push_back(s);//把点击的星星放进遍历队列
    deque<Star*>::iterator it;
    for(it= travelList.begin();it != travelList.end();){//当遍历队列为空的时候停止
        Star* star = *it;
        Star* linkStar = nullptr;
        int index_i = star->getIndexI();
        int index_j = star->getIndexJ();
        //上
        if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){//判断是否数组越界
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())//判断是否已经被纳入选择队列并且与遍历队列的星星颜色一样
                travelList.push_back(stars[index_i-1][index_j]);//如果没有被纳入选择队列，并且颜色一样就加入遍历队列
        }
        //下
        if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
                travelList.push_back(stars[index_i+1][index_j]);
        }
        //左
        if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
                travelList.push_back(stars[index_i][index_j-1]);
        }
        //右
        if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
                travelList.push_back(stars[index_i][index_j+1]);
        }
        if(!star->isSelected()){//处理当前的星星
            star->setSelected(true);//设置已经被加入到选择队列（待删除队列）
            selectedList.push_back(star);//加入到选择队列（待删除队列）
        }
        travelList.pop_front();//队头出队
        it = travelList.begin();//得到新的队头
    }
}

/*
 * 通过genSelectedList我们可以得到一个待删除的列表，接下来我们用deleteSelectedList删除这个列表。
这还不简单，只要先判断一下待删除列表的长度是否大于等于2，如果是就对列表里面的每一个Star*进行removeFromParentAndCleanUp就可以了。
 */
void StarMatrix::deleteSelectedList(){
	if(selectedList.size() <= 1){
		m_layer->hideLinkNum();
		selectedList.at(0)->setSelected(false);
		return;
	}


	for(auto it = selectedList.begin();it != selectedList.end();it++){
		Star* star = *it;
		//粒子效果
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
		//播放音效
		Audio::getInstance()->playPop();
	}
	//COMBO效果
	showComboEffect(selectedList.size(),this);
	Audio::getInstance()->playCombo(selectedList.size());

	refreshScore();
	m_layer->showLinkNum(selectedList.size());
	adjustMatrix();
	if(isEnded()){
		m_layer->floatLeftStarMsg(getLeftStarNum());//通知layer弹出剩余星星的信息
		CCLOG("ENDED");
	}

}

void StarMatrix::refreshScore(){
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore() + selectedList.size()*selectedList.size()*5);
	if(data->getCurScore() > data->getHistoryScore()){
		data->setHistoryScore(data->getCurScore());
	}
	m_layer->refreshMenu();
}


/*
 * 但是这还没完全的实现一次星星的消除，我们还要对新的星星矩阵进行调整，让底下没有星星的星星下落（总不能中间悬空了一块吧）。
 */
void StarMatrix::adjustMatrix(){
	//垂直方向调整
	for(int i = ROW_NUM-1;i>=0;i--){
		for(int j = COL_NUM-1;j>=0;j--){
			if(stars[i][j] == nullptr){
				int up = i;
				int dis = 0;
				while(stars[up][j] == nullptr){
					dis++;
					up--;
					if(up<0){
						break;
					}
				}

				for(int begin_i = i - dis;begin_i >= 0;begin_i--){
					if(stars[begin_i][j] == nullptr)
						continue;
					Star* s = stars[begin_i + dis][j] = stars[begin_i][j];
					s->setIndex_ij(begin_i + dis,j);
					s->setDesPosition(getPositionByIndex(begin_i + dis,j));
					stars[begin_i][j] = nullptr;
				}
			}else{
				continue;
			}
		}
	}
	//水平方向调整
	for(int j = 0;j < COL_NUM;j++){
		if(stars[ROW_NUM-1][j] == nullptr){
			int des = 0;
			int right = j;
			while(stars[ROW_NUM-1][right] == nullptr){
				des++;
				right++;
			}
			for(int begin_i = 0;begin_i<ROW_NUM;begin_i++){
				for(int begin_j = j + des;begin_j < COL_NUM;begin_j++){
					if(stars[begin_i][begin_j] == nullptr)
						continue;
					Star* s = stars[begin_i][begin_j - des] = stars[begin_i][begin_j];
					s->setIndex_ij(begin_i,begin_j - des);
					s->setDesPosition(getPositionByIndex(begin_i,begin_j - des));
					stars[begin_i][begin_j] = nullptr;
				}
			}
		}
	}

}


bool StarMatrix::isEnded(){
	bool bRet = true;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			int curColor = stars[i][j]->getColor();
			//上
			if(i-1>=0 && stars[i-1][j]!=nullptr && stars[i-1][j]->getColor() ==  curColor)
				return false;
			//下
			if(i+1<ROW_NUM && stars[i+1][j]!=nullptr && stars[i+1][j]->getColor() == curColor)
				return false;
			//左
			if(j-1>=0 && stars[i][j-1]!=nullptr && stars[i][j-1]->getColor() == curColor)
				return false;
			//右
			if(j+1<COL_NUM && stars[i][j+1]!=nullptr && stars[i][j+1]->getColor() == curColor)
				return false;
		}
	}
	return bRet;
}

void StarMatrix::clearMatrixOneByOne(){
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			showStarParticleEffect(stars[i][j]->getColor(),stars[i][j]->getPosition(),this);
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;
			return;
		}
	}
	//能够执行到这一句说明Matrix全为空，不在需要清空
	needClear = false;
	//转到下一关或者弹出结束游戏的窗口
	if(GAMEDATA::getInstance()->getCurScore() >= GAMEDATA::getInstance()->getNextScore()){
		GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);
		m_layer->gotoNextLevel();
	}else{
		m_layer->gotoGameOver();
		CCLOG("GAME OVER");
	}
}

int StarMatrix::getLeftStarNum(){
	int ret = 0;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			ret++;
		}
	}
	return ret;
}
