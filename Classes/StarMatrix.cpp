/*
 * StarMatrix.cpp
 *
 *  Created on: 2014��11��16��
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
			star->setPosition(getPositionByIndex(i,j)+Point(0,100));//��ǰλ��,�������ǵ�ǰ������λ�ã��ǿ��Ըı��
			star->setDesPosition(getPositionByIndex(i,j));//Ŀ��λ��,������Ҫ�����λ�ã�������ǵĵ�ǰλ�ò�����Ŀ�����ǣ����ǵĵ�ǰλ�û᲻�ϵظı䣬ֱ���ƶ���Ŀ��λ��
			star->setIndex_ij(i,j);//������λ��
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
		genSelectedList(s);//�õ�һ�����ӵ����ǵĺ���
		CCLOG("SIZE = %d",selectedList.size());
		deleteSelectedList();//ɾ��һ�����ӵ����ǵĺ���
	}
}


void StarMatrix::setNeedClear(bool b){
	needClear = b;
}


/*

�õ�һ���������ǵ��㷨˼·������ʹ���˹�����ȱ�������������һ������������

���岽�����£�

1.�ѱ���������ǷŽ��������У�

2.�ֱ�Ա������������Ԫ�ؽ������²�����

1)  �Ѹ�Ԫ�طŽ���ɾ�����б���������Ҫ���б���

2�������Ϸ��Ƿ�����ͬ��ɫ�����ǣ�����У����Ϸ������ǷŽ��������У�

3�������·��Ƿ�����ͬ��ɫ�����ǣ�����У����·������ǷŽ��������У�

4����������Ƿ�����ͬ��ɫ�����ǣ�����У�����ߵ����ǷŽ��������У�

5�������ұ��Ƿ�����ͬ��ɫ�����ǣ�����У����ұߵ����ǷŽ��������У�

3.�������ж�ͷ���У��õ��µĶ�ͷ��

4.�ظ�����2��
 */
Star* StarMatrix::getStarByTouch(const Point& p){
	int k = p.y/Star::STAR_HEIGHT;//����Ҫ��Kתһ��int ��Ȼ�ò�����ȷ���
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
    selectedList.clear();//�ǵ�ÿ�ε����Ҫ�ȰѴ�ɾ���б����
    deque<Star*> travelList;//��������
    travelList.push_back(s);//�ѵ�������ǷŽ���������
    deque<Star*>::iterator it;
    for(it= travelList.begin();it != travelList.end();){//����������Ϊ�յ�ʱ��ֹͣ
        Star* star = *it;
        Star* linkStar = nullptr;
        int index_i = star->getIndexI();
        int index_j = star->getIndexJ();
        //��
        if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){//�ж��Ƿ�����Խ��
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())//�ж��Ƿ��Ѿ�������ѡ����в�����������е�������ɫһ��
                travelList.push_back(stars[index_i-1][index_j]);//���û�б�����ѡ����У�������ɫһ���ͼ����������
        }
        //��
        if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
                travelList.push_back(stars[index_i+1][index_j]);
        }
        //��
        if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
                travelList.push_back(stars[index_i][index_j-1]);
        }
        //��
        if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){
            if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
                travelList.push_back(stars[index_i][index_j+1]);
        }
        if(!star->isSelected()){//����ǰ������
            star->setSelected(true);//�����Ѿ������뵽ѡ����У���ɾ�����У�
            selectedList.push_back(star);//���뵽ѡ����У���ɾ�����У�
        }
        travelList.pop_front();//��ͷ����
        it = travelList.begin();//�õ��µĶ�ͷ
    }
}

/*
 * ͨ��genSelectedList���ǿ��Եõ�һ����ɾ�����б�������������deleteSelectedListɾ������б�
�⻹���򵥣�ֻҪ���ж�һ�´�ɾ���б�ĳ����Ƿ���ڵ���2������ǾͶ��б������ÿһ��Star*����removeFromParentAndCleanUp�Ϳ����ˡ�
 */
void StarMatrix::deleteSelectedList(){
	if(selectedList.size() <= 1){
		m_layer->hideLinkNum();
		selectedList.at(0)->setSelected(false);
		return;
	}


	for(auto it = selectedList.begin();it != selectedList.end();it++){
		Star* star = *it;
		//����Ч��
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
		//������Ч
		Audio::getInstance()->playPop();
	}
	//COMBOЧ��
	showComboEffect(selectedList.size(),this);
	Audio::getInstance()->playCombo(selectedList.size());

	refreshScore();
	m_layer->showLinkNum(selectedList.size());
	adjustMatrix();
	if(isEnded()){
		m_layer->floatLeftStarMsg(getLeftStarNum());//֪ͨlayer����ʣ�����ǵ���Ϣ
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
 * �����⻹û��ȫ��ʵ��һ�����ǵ����������ǻ�Ҫ���µ����Ǿ�����е������õ���û�����ǵ��������䣨�ܲ����м�������һ��ɣ���
 */
void StarMatrix::adjustMatrix(){
	//��ֱ�������
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
	//ˮƽ�������
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
			//��
			if(i-1>=0 && stars[i-1][j]!=nullptr && stars[i-1][j]->getColor() ==  curColor)
				return false;
			//��
			if(i+1<ROW_NUM && stars[i+1][j]!=nullptr && stars[i+1][j]->getColor() == curColor)
				return false;
			//��
			if(j-1>=0 && stars[i][j-1]!=nullptr && stars[i][j-1]->getColor() == curColor)
				return false;
			//��
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
	//�ܹ�ִ�е���һ��˵��MatrixȫΪ�գ�������Ҫ���
	needClear = false;
	//ת����һ�ػ��ߵ���������Ϸ�Ĵ���
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
