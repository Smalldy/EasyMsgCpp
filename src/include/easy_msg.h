#ifndef EASYMSG_H
#define EASYMSG_H
#include "easymsg_export.h"
#include <assert.h>
#include <functional>
#include <iostream>
#include <string>
#include <utility>

namespace em {

class EasyMsg;

class EASYMSG_API EasyMsg {
public:
  EasyMsg();
  virtual ~EasyMsg(){};
  virtual std::string id() const = 0;

  template <typename T> struct is_easymsg {
    template <typename U> static char test(typename U::MsgType *x);
    template <typename U> static long test(U *x);
    static const bool value = sizeof(test<T>(0)) == 1;
  };

  // c++17 support constexpr if
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
  template <typename MSGID> bool match() {
    is_easymsg<MSGID> test_easymsg;
    if constexpr (test_easymsg.value) { // c++17
      return id() == MSGID::value;
    } else {
      std::cerr << "匹配消息ID时发生错误，检查是否使用了未定义的消息？ 检查:"
                << typeid(MSGID).name() << std::endl;
      return false;
    }
  }
#else
  template <class MSGID>
  typename std::enable_if<!is_easymsg<MSGID>::value, bool>::type match() {
    std::cerr
        << "匹配消息ID时发生错误，检查是否使用了未定义的消息？ typeinfo : "
        << typeid(MSGID).name() << std::endl;
    return false;
  }

  template <class MSGID>
  typename std::enable_if<is_easymsg<MSGID>::value, bool>::type match() {
    return id() == MSGID::value;
  }

#endif
};

// 定义消息后 一定会经过模板特化，因此调用非特化版本的MsgId意味着没有定义此消息
template <typename _MSG_> std::string MsgId() {
  assert(!("EasyMsg: subscript invalid EasyMsg!"));
  return "";
}

#define MAKE_MSG_ID_CAT(_MSG_) #_MSG_
#define MSG_ID_STR(_MSG_) MAKE_MSG_ID_CAT(_MSG_)

#define EASY_MSG_DEFINE(_MSG_, _MSG_ID_)                                       \
  template <> std::string em::MsgId<_MSG_>() { return MSG_ID_STR(_MSG_); }     \
  struct _MSG_##_MSG : public _MSG_, public em::EasyMsg {                      \
  public:                                                                      \
    std::string id() const { return MSG_ID_STR(_MSG_); }                       \
  };                                                                           \
  struct _MSG_ID_ {                                                            \
  public:                                                                      \
    static const std::string value;                                            \
    using MsgType = _MSG_##_MSG;                                               \
  };                                                                           \
  const std::string _MSG_ID_::value = em::MsgId<_MSG_>();

#define DeclareMsg

} // namespace em

#endif // EASYMSG_H
