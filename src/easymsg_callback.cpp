#include "easymsg_callback.h"

#include <utility>
#include "easy_msg.h"
namespace em {

EasyMsgCallback::EasyMsgCallback(std::function<void(em::EasyMsg *)> func) {
  easymsg_callback_ = std::move(func);
}

void EasyMsgCallback::operator()(em::EasyMsg *easymsg) {
  easymsg_callback_(easymsg);
}

} // namespace em
