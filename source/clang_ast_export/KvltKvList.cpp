#include "KvltKvList.h"

#include <string>
#include "KvltConsumer.h"
#include "KvltKvListValue.h"
#include "KvltStream.h"

using std::string;

namespace ast_export {
KvltKvList::KvltKvList(KvltStream *stream) : stream_(stream) {}

// Sometimes RVO is turned off (debug builds, etc.). Instead the compiler will
// use the move constructor.
KvltKvList::KvltKvList(KvltKvList &&from) 
  : stream_(from.stream_) {
  from.stream_ = nullptr;
  // The moved to object will do the close. Don't want to double close.
  from.should_close_ = false;
}

KvltKvList::~KvltKvList() {
  if (should_close_) {
    stream_->Consumer()->ConsumeKvListClose();
  }
}

KvltKvListValue KvltKvList::Key(string value) {
  stream_->Consumer()->ConsumeKey(value);
  KvltKvListValue kv_list_value(stream_, this);
  return kv_list_value;
}
}
