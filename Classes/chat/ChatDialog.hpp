#ifndef ChatDialog_hpp
#define ChatDialog_hpp
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "server/PomeloHandler.h"

USING_NS_CC;
using namespace cocos2d::ui;

class ChatDialog : public Layer, public PomeloListen{
public:
    virtual bool init();
	CREATE_FUNC(ChatDialog);
private:
    std::string chatPid;
    ListView* listView;
    void closeView();
    void showChatInfo(std::string username,std::string content);
    void sendMessage();
private:
	virtual void  handle_event(const char* msgId, const char* msgBody);
};
#endif