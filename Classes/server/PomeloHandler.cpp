#include "PomeloHandler.h"

PomeloHandler* PomeloHandler::_instance = nullptr;

PomeloHandler* PomeloHandler::getInstance(){

	if (_instance == 0){
		_instance = PomeloHandler::create();
		_instance->retain();
	}
	return _instance;

}

PomeloHandler::PomeloHandler(){
	
}
bool PomeloHandler::init()
{
	if (!Node::init())
	{
		return false;
	}
	Director::getInstance()->getScheduler()->schedule(schedule_selector(PomeloHandler::update), this, Director::getInstance()->getAnimationInterval(), false);
	return true;
}
void PomeloHandler::addHandlerListen(PomeloListen* listen)
{
	_listensVec.push_back(listen);
}
void PomeloHandler::removeHandlerLister(PomeloListen*listen)
{
	for (auto iter = _listensVec.begin(); iter != _listensVec.end();iter++)
	{
		if (*iter == listen)
		{
			_listensVec.erase(iter);
			return;
		}
	}
}
void PomeloHandler::update(float dt){

	m_mutex.lock();
	while (!_msgList.empty())
	{
		auto msg = _msgList.front();
		for (auto var:_listensVec)
		{
			var->handle_event(msg.route.c_str(), msg.body.c_str());
		}
		_msgList.pop();
	}
	m_mutex.unlock();
}

void PomeloHandler::pushMsg(PomeloMsg msg){
	m_mutex.lock();
	_msgList.push(msg);
	m_mutex.unlock();
}

