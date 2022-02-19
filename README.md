# 设计目标
 - 定义消息时，不能破坏消息本身的结构，
 - 处理消息的类无需继承任何基类
 - 足够简单的订阅方法
 - RAII形式的取消订阅，但也支持手动取消订阅

# 使用导航

## 最小示例
```
#include "easy_msg.h"
#include "easymsg_subscriber.h"
#include <iostream>
//项目中需要传递的结构体
struct SomeMsg {
  std::string msg_str;
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

```


## 消息和消息ID

假设你有一个原始结构体 
```
struct SomeMsg {
  std::string msg_str;
};
```
定义消息将会非常简单

```
EASY_MSG_DEFINE(SomeMsg, SomeMsgId);
```
EASY_MSG_DEFINE 的第一个参数为原始消息结构体，这个结构体定义了消息内容，第二个参数是由用户决定的名称，这个名称将作为消息ID使用，消息ID再订阅消息，发送消息和处理消息时十分重要。

## 消息订阅
