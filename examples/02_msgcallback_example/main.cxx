#include "easy_msg.h"
#include "easymsg_subscriber.h"
#include <iostream>
//项目中需要传递的结构体
struct SomeMsg {
  std::string msg_str;
};

struct SomeMsg2 {
  std::string msg_str2;
};

// 将其注册为消息
EASY_MSG_DEFINE(SomeMsg, SomeMsgId);

class MailBox {
public:
  MailBox() {
    //注册消息回调函数
    sub.subscribe<SomeMsgId>(this, &MailBox::handleMsg);
  }

  void handleMsg(em::EasyMsg *easymsg) {
    //使用 msg函数
    if (easymsg->match<SomeMsgId>()) {
      auto *p = em::easymsg_cast<SomeMsgId>(easymsg);
      std::cout << p->msg_str << std::endl;
    }
  }

private:
  em::EasyMsgSubscriber sub; //析构时自动取消订阅
};

int main() {
  SomeMsg msg1{"shshhshsh"};
  // 填充消息字段 可以用原始结构体构造
  SomeMsgId::MsgType msg{msg1};
  // 当然 也可以重新为字段赋值
  // msg.msg_str = "ada";
  MailBox box;
  // 消息分发 执行回调
  em::sendMsg<SomeMsgId>(&msg);

  return 0;
}
