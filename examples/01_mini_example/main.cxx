#include "easy_msg.h"
#include <iostream>

struct SomeMsg {
  std::string msg_str;
};

struct SomeMsg2 {
  std::string msg_str2;
};

// reg struct to msg
EASY_MSG_DEFINE(SomeMsg, SomeMsgId);

int main() {
  // define a msg var
  SomeMsgId::MsgType msg;
  msg.msg_str = "ada";
  // match msg
  if (msg.match<SomeMsgId>()) {
    std::cout << "msg matched = " << msg.id() << std::endl;
  }
  // 消息匹配失败不会导致程序停止或编译失败
  if (msg.match<SomeMsg2>()) {
    std::cout << "msg matched = " << msg.id() << std::endl;
  }

  return 0;
}
