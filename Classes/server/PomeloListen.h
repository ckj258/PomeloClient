#pragma once
#include "cocos2d.h"

class PomeloListen
{
public:
    virtual void handle_event(const char* msgId, const char* msgBody)=0;
};

