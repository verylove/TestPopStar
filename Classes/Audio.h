/*
 * Audio.h
 *
 *  Created on: 2014Äê11ÔÂ14ÈÕ
 *      Author: Yang
 */

#ifndef AUDIO_H_
#define AUDIO_H_

class Audio{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playPop();
	void prepare();
	void playCombo(int size);
private:
	static Audio* m_instance;
};




#endif /* AUDIO_H_ */
