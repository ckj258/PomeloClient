#include "ChatDialog.hpp"
#include "server/PomeloSocket.h"
#include "json/document.h"
#include "json/rapidjson.h"

bool ChatDialog::init(){
    if(!Layer::init()){
        return false;
    }


    auto  dialogBg = Sprite::create("chat/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    

    
    auto inputText = Scale9Sprite::create("loginFram.png");
    inputText->setContentSize(Size(720,500));
    inputText->setPosition(640,375);
    addChild(inputText);
    
    listView = ListView::create();
    listView->setTouchEnabled(true);//可触摸
    listView->setContentSize(Size(720,480));//设置ListView大小
    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
    listView->setPosition(Point(640,375));
    addChild(listView);
    
    auto inputBg =  Scale9Sprite::create("loginFramg.png");
    inputBg->setContentSize(Size(720,81));
    inputBg->setPosition(Point(640,85));
    addChild(inputBg);
    
    auto inputField =  Scale9Sprite::create("loginFram.png");
    inputField->setContentSize(Size(560,71));
    inputField->setPosition(Point(565,85));
    addChild(inputField);
    
    
    MenuItemImage* snd = MenuItemImage::create("chat/send_btn_1.png","chat/send_btn_2.png",CC_CALLBACK_0(ChatDialog::sendMessage, this));
    auto sendBtn  = Menu::create(snd,NULL);
    sendBtn->setPosition(942,85);
    addChild(sendBtn);
    
    EditBox* field = EditBox::create(Size(500,71), Scale9Sprite::create());
    field->setTag(1001);
    field->setPosition(Point(545,85));
    addChild(field);
    

	PomeloHandler::getInstance()->addHandlerListen(this);
    return true;
}



void ChatDialog::showChatInfo(std::string username, std::string content){
    Layout *customItem = Layout::create();
    customItem->setLayoutType(Layout::Type::ABSOLUTE);
    customItem->setContentSize(Size(720,100));
	Label* labelname = Label::createWithSystemFont(username,"arial",30);
	labelname->setColor(Color3B::YELLOW);
	labelname->setPosition(100, 0);
	customItem->addChild(labelname);
    listView->pushBackCustomItem(customItem);
    listView->jumpToBottom();
    

    RichText* text = RichText ::create();
    text->setAnchorPoint(Point::ANCHOR_MIDDLE);
	RichElementText* element1 = RichElementText::create(1, Color3B(255, 255, 255), 255, content, "arial", 20);
	text->pushBackElement(element1);
	text->formatText();
    customItem->addChild(text,1);
    auto bob = Scale9Sprite::create("chat/text_bob.png", Rect(0, 0, 31, 38), Rect(20, 0, 6, 38));
    bob->setContentSize(Size(text->getContentSize().width+20, 65));
    customItem->addChild(bob);
    
        text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        text->setPosition(Point(140,40));
        bob->setPosition(Point(135,30));
}

void ChatDialog::closeView(){
    removeFromParent();
}

void ChatDialog:: sendMessage(){
    if(NULL != getChildByTag(1001)){
        std::string msg = ((cocos2d::ui::EditBox*)getChildByTag(1001))->getText();
        if("" != msg){
           
			pc_request_cb_t request_cb = [](const pc_request_t* req, int rc, const char* resp) {

				CCLOG("[server]sendRequest connect_cb: get  rc %d resp %s   route %s", rc, resp, pc_request_route(req));
				
			};
			std::string reqParams = "{\"content\": \"" + msg + "\",\"from\": \"" + PomeloSocket::getInstance()->getusername() + "\" ,\"target\": \"" + Value("*").asString() + "\",\"rid\": \"" + PomeloSocket::getInstance()->getrid() + "\"}";
			PomeloSocket::getInstance()->sendRequest(reqParams.c_str(), "chat.chatHandler.send", request_cb);
        }
        ((cocos2d::ui::EditBox*)getChildByTag(1001))->setText("");
    }
}

void ChatDialog::handle_event(const char* msgId, const char* msgBody)
{

	ChatMsg*msg = new ChatMsg();
	if (strcmp(msgId, "onChat") == 0)
	{
		rapidjson::Document _mDoc;
		_mDoc.Parse<0>(msgBody);

		msg->usingname = _mDoc["from"].GetString();
		msg->content = _mDoc["msg"].GetString();
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		rapidjson::Document _mDoc;
		_mDoc.Parse<0>(msgBody);

		msg->usingname = _mDoc["user"].GetString();
		msg->content = msg->usingname + "is onLeave";

	}
	if (strcmp(msgId, "onAdd") == 0)
	{

		rapidjson::Document _mDoc;
		_mDoc.Parse<0>(msgBody);

		msg->usingname = _mDoc["user"].GetString();
		msg->content = msg->usingname + "is onAdd";
	}
	showChatInfo(msg->usingname.c_str(), msg->content.c_str());
	CC_SAFE_DELETE(msg);
}