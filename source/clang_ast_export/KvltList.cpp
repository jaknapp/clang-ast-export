#include "KvltKvListValue.h"

#include <string>
#include "KvltConsumer.h"
#include "KvltKvList.h"
#include "KvltList.h"
#include "KvltStream.h"

using std::string;

namespace ast_export {
KvltList::KvltList(KvltStream *stream)
  : stream_(stream), should_close_(true) {}

KvltList::KvltList(KvltList &&from)
  : stream_(from.stream_) {
  from.stream_ = nullptr;
  from.should_close_ = false;
}

KvltList::~KvltList() {
  if (should_close_) {
    stream_->Consumer()->ConsumeListClose();
  }
}

KvltList &KvltList::Value(string value) {
  stream_->Consumer()->ConsumeValue(value);
  return *this;
}

KvltList KvltList::List() {
  stream_->Consumer()->ConsumeListOpen();
  KvltList list(stream_);
  return list;
}

KvltKvList KvltList::KvList() {
  stream_->Consumer()->ConsumeKvListOpen();
  KvltKvList kv_list(stream_);
  return kv_list;
}
}
