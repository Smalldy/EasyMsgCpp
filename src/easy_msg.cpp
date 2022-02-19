#include "easy_msg.h"
#include "easymsg_dispatcher.h"
#include <iostream>
namespace em {
EasyMsgDispatcher ___dispatcher;

EasyMsg::EasyMsg() { std::cout << __FUNCTION__ << std::endl; }

} // namespace em
