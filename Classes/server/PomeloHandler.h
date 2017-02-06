#pragma once
#include "cocos2d.h"
#include "PomeloListen.h"
USING_NS_CC;
struct PomeloMsg
{
	std::string route;
	std::string body;
};


class PomeloHandler :public Node{
public:
	static PomeloHandler* getInstance();
private:
	virtual bool init();
	virtual void update(float dt);
public:
	void pushMsg(PomeloMsg msg);
	void addHandlerListen(PomeloListen* listen);//Ìí¼Ó¼àÌý
	void removeHandlerLister(PomeloListen*listen);
private:
	static PomeloHandler* _instance;
	PomeloHandler();
	CREATE_FUNC(PomeloHandler);
	std::mutex m_mutex;


	std::vector<PomeloListen*> _listensVec;
	std::queue<PomeloMsg> _msgList;
};
