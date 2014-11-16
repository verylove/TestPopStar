/*
 * GameData.h
 *
 *  Created on: 2014年11月16日
 *      Author: Administrator
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

class GAMEDATA{
public:
    static GAMEDATA* getInstance();
    /*当前等级*/
    void setCurLevel(int level);
    inline int getCurLevel(){return cur_level;}
    /*下一等级*/
    inline int getNextLevel(){return next_level;}
    /*最高分*/
    inline void setHistoryScore(int score){history_score = score;}
    inline int getHistoryScore(){return history_score;}
    /*当前分数*/
    inline void setCurScore(int score){cur_score = score;}
    inline int getCurScore(){return cur_score;}
    /*通关分数*/
    inline int getNextScore(){return next_score;}
    inline int getScoreByLevel(int level);

    /*奖励分数*/
    int getJiangli(int size);

    void saveHighestScore();
private:
    GAMEDATA();
    void init();
private:
    static GAMEDATA* _instance;
    int cur_level;
    int next_level;
    int history_score;
    int cur_score;
    int next_score;
    friend class MenuLayer;
};



#endif /* GAMEDATA_H_ */
