#include "mailbox.h"
#include <iostream>
namespace test {
void test() {
  SomeMsg msg1{"shshhshsh"};
  // 填充消息字段 可以用原始结构体构造
  SomeMsgId::MsgType msg{msg1};
  // 当然 也可以重新为字段赋值
  // msg.msg_str = "ada";

  SomeMsg2Id::MsgType msg2;
  msg2.msg_str2 = "blabalal";

  SomeMsg msg3{"msg 3 move test"};
  SomeMsgId::MsgType msg_move_test{std::move(msg3)};

  MailBox box;
  // 消息分发 执行回调
  em::sendMsg<SomeMsgId>(&msg);
  em::sendMsg<SomeMsg2Id>(&msg2);
  em::sendMsg<SomeMsgId>(&msg_move_test);
}
} // namespace test

int main() {
  test::test();
  return 0;
}
