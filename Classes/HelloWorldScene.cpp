#include "HelloWorldScene.h"
#include "server/PomeloSocket.h"
#include "chat/ChatScene.h"
#define SERVERIP "127.0.0.1"
#define SERVERPORT 3051

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }


	auto visibile = Director::getInstance()->getVisibleSize();

	auto frame = Sprite::create("loginFram.png");
	frame->setPosition(visibile.width/2, 232);
	addChild(frame);
	//输入名字	
	_editName = ui::EditBox::create(Size(240, 53), ui::Scale9Sprite::create());
	_editName->setPosition(Vec2(visibile.width/2, 232));
	_editName->setPlaceHolder("Input your username");
	_editName->setFontName("Arial");
	_editName->setFontSize(20);
	_editName->setFontColor(Color3B::YELLOW);
	_editName->setMaxLength(14);
	_editName->setDelegate(this);
	addChild(_editName);
	//输入房号	
	frame = Sprite::create("loginFram.png");
	frame->setPosition(visibile.width/2, 169);
	addChild(frame);
	_editRoom = ui::EditBox::create(Size(240, 53), ui::Scale9Sprite::create());
	_editRoom->setPosition(Vec2(visibile.width/2, 169));
	_editRoom->setPlaceHolder("Input roomid with 1-99");
	_editRoom->setFontName("Arial");
	_editRoom->setFontSize(20);
	_editRoom->setInputMode(ui::EditBox::InputMode::NUMERIC);
	_editRoom->setFontColor(Color3B::YELLOW);
	_editRoom->setMaxLength(14);
	_editRoom->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editRoom->setDelegate(this);
	addChild(_editRoom);

	//登录按钮
	auto enter = MenuItemFont::create("EnterRoom",CC_CALLBACK_1(HelloWorld::loginCallback,this));
	enter->setPosition(visibile.width / 2, visibile.height*0.10);
	auto menu = Menu::create(enter, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);


	PomeloSocket::getInstance()->conConnect(SERVERIP, SERVERPORT);



    return true;
}

void HelloWorld::loginCallback(Ref*psend)
{

	if (_editName->getText() == ""&&_editRoom->getText() == "")
	{
		return;
	}
	//bad dealwith
	PomeloSocket::getInstance()->setusername(_editName->getText());
	PomeloSocket::getInstance()->setrid(_editRoom->getText());


	pc_request_cb_t request_cb = [](const pc_request_t* req, int rc, const char* resp) {
		CCLOG("[server]sendRequest connect_cb: get  rc %d resp %s   route %s", rc, resp, pc_request_route(req));
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([](){Director::getInstance()->replaceScene(ChatScene::createScene()); });
		
		
	};
	std::string reqParams = "{\"username\": \"" + Value(_editName->getText()).asString() + "\",\"rid\": \"" + Value(_editRoom->getText()).asString() + "\" }";
	PomeloSocket::getInstance()->sendRequest(reqParams.c_str(), "connector.entryHandler.enter", request_cb);

}
void HelloWorld::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	
}

void HelloWorld::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{

}

void HelloWorld::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{

}

void HelloWorld::editBoxReturn(ui::EditBox* editBox)
{

}