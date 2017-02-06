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
	void conConnect(const char*ServerIP, int ServerPort	);//��������
	void quit();										  //�Ͽ�����

/* ==============================================================================
 * ���������������¼�,�ص����� typedef void (*pc_notify_cb_t)(const pc_notify_t* req, int rc);  rc��ʾ������,�޲�������. �������ϴ���Ϸ���ݵȵ�
 * �� �� �ߣ�ckj
 * �������ڣ�2016��12��13��17:30:49
 * ==============================================================================*/
	void sendEvents(const char* params, const char*remote, pc_notify_cb_t event_cb);
/* ==============================================================================
 * ������������������,�ص����� typedef void (*pc_request_cb_t)(const pc_request_t* req, int rc, const char* resp);  rc��ʾ������,respΪ������json�ṹ. �����ڵ�¼����Ҫ���ؽ���ĳ���  
 * �� �� �ߣ�ckj
 * �������ڣ�2016��12��13��17:33:53
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