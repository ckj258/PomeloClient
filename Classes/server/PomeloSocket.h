#pragma once
#include "pomelo.h"
#include "pomelo_trans.h"
#include "PomeloListen.h"
#include "cocos2d.h"
USING_NS_CC;
#define REQ_EX ((void*)0x22)
#define REQ_TIMEOUT 10
#define REQ_GATE_EX ((void*)0x22)
#define REQ_NEWEVENTS_EX ((void*)0x33)


struct ChatMsg
{
	std::string usingname;
	std::string content;
};

class PomeloSocket{
public:
	static PomeloSocket* getInstance();
	void conConnect(const char*ServerIP, int ServerPort	);//建立连接
	void quit();										  //断开连接

/* ==============================================================================
 * 功能描述：发送事件,回调函数 typedef void (*pc_notify_cb_t)(const pc_notify_t* req, int rc);  rc表示错误码,无参数返回. 例用于上传游戏数据等等
 * 创 建 者：ckj
 * 创建日期：2016年12月13日17:30:49
 * ==============================================================================*/
	void sendEvents(const char* params, const char*remote, pc_notify_cb_t event_cb);
/* ==============================================================================
 * 功能描述：发送请求,回调函数 typedef void (*pc_request_cb_t)(const pc_request_t* req, int rc, const char* resp);  rc表示错误码,resp为服务器json结构. 例用于登录等需要返回结果的场景  
 * 创 建 者：ckj
 * 创建日期：2016年12月13日17:33:53
 * ==============================================================================*/
	void sendRequest(const char* params, const char*remote, pc_request_cb_t request_cb);

private:
	PomeloSocket();
	static PomeloSocket* _instance;
private:
	int handler_id;
	pc_client_t* workingClient;
	static void connect_cb(pc_client_t* client, int ev_type, void* ex_data, const char* arg1, const char* arg2);
	///user
private:
	CC_SYNTHESIZE(std::string, _username, username);
	CC_SYNTHESIZE(std::string, _rid, rid);
	
};