#ifndef EASYMSGSUBSCRIBER_H
#define EASYMSGSUBSCRIBER_H

#include "easymsg_dispatcher.h"
#include "easymsg_export.h"
#include <functional>

namespace em {
class EasyMsg;
class EASYMSG_API EasyMsgSubscriber {
public:
  EasyMsgSubscriber();
  ~EasyMsgSubscriber();

  template <typename _MSGID, typename _HOST>
  void subscribe(_HOST *hostObj, void (_HOST::*handleMsg)(EasyMsg *)) {
    EasyMsgDispatcher &dispatcher = getDispatcher();
    dispatcher.addCallback<_MSGID>(hostObj, handleMsg);
    host_ptr = static_cast<void *>(hostObj);
  }

  template <typename _MSGID, typename _HOST> void unSubscribe(_HOST *hostObj) {
    if (host_ptr != static_cast<void *>(hostObj)) {
      return;
    }
    EasyMsgDispatcher &dispatcher = getDispatcher();
    dispatcher.removeCallback<_MSGID>(hostObj);
  }

private:
  EasyMsgDispatcher &getDispatcher();

  void *host_ptr;
};

} // namespace em

#endif // EASYMSGSUBSCRIBER_H
