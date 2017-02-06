#include "PomeloSocket.h"

#include "PomeloHandler.h"
PomeloSocket* PomeloSocket::_instance = NULL;

PomeloSocket::PomeloSocket(){
}


PomeloSocket* PomeloSocket::getInstance(){
	if(_instance == NULL){
		_instance = new PomeloSocket();
	}
	return _instance;
}



void PomeloSocket::quit() {
    if(workingClient != NULL) {
        pc_client_disconnect(workingClient);
        pc_client_rm_ev_handler(workingClient, handler_id);
        pc_client_cleanup(workingClient);
        free(workingClient);
    }
    pc_lib_cleanup();
}


void PomeloSocket::sendEvents(const char* params, const char*remote, pc_notify_cb_t event_cb) {
	pc_notify_with_timeout(workingClient, remote, params, REQ_NEWEVENTS_EX, REQ_TIMEOUT, event_cb);
}

void PomeloSocket::sendRequest(const char* params, const char*remote, pc_request_cb_t request_cb)
{
	pc_request_with_timeout(workingClient, remote, params, REQ_EX, REQ_TIMEOUT, request_cb);
	

}

void PomeloSocket::conConnect(const char*ServerIP, int ServerPort) {

    pc_lib_init(NULL, NULL, NULL, NULL);
    workingClient = (pc_client_t*)malloc(pc_client_size());
    pc_client_init(workingClient, (void*)0x11, NULL);
	handler_id = pc_client_add_ev_handler(workingClient, connect_cb, REQ_EX, NULL);
	pc_client_connect(workingClient, ServerIP, ServerPort, NULL);
}




void PomeloSocket::connect_cb(pc_client_t* client, int ev_type, void* ex_data, const char* arg1, const char* arg2) {
	CCLOG("[server]event_cb: get event %s, arg1: %s, arg2: %s\n", pc_client_ev_str(ev_type), arg1 ? arg1 : "", arg2 ? arg2 : "");

	//ev_type=0时为服务器广播事件
	if (ev_type == 0)
	{
		PomeloMsg msg;
		msg.route = arg1;
		msg.body =  arg2;
		PomeloHandler::getInstance()->pushMsg(msg);
	}


};
