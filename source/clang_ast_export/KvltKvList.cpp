#include "KvltKvList.h"

#include <string>
#include "KvltConsumer.h"
#include "KvltKvListValue.h"
#include "KvltStream.h"

// debug
#include <iostream>

using std::string;

namespace ast_export {
KvltKvList::KvltKvList(KvltStream *stream) : stream_(stream), should_close_(true) {
  //std::cout << "constructing ";
}

// Sometimes RVO is turned off (debug builds, etc.). Instead the compiler will
// use the move constructor.
KvltKvList::KvltKvList(KvltKvList &&from) 
  : stream_(from.stream_), should_close_(from.should_close_) {
  //std::cout << "moving ";
  from.stream_ = nullptr;
  // The moved to object will do the close. Don't want to double close.
  from.should_close_ = false;
}

KvltKvList::~KvltKvList() {
  //std::cout << "destructing ";
  if (should_close_) {
    //std::cout << "closing ";
    stream_->Consumer()->ConsumeKvListClose();
  }
}

KvltKvListValue KvltKvList::Key(string value) {
  stream_->Consumer()->ConsumeKey(value);
  KvltKvListValue kv_list_value(stream_, this);
  return kv_list_value;
}
}
