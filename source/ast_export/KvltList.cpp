#include "KvltKvListValue.h"

#include <string>
#include "KvltConsumer.h"
#include "KvltKvList.h"
#include "KvltList.h"
#include "KvltStream.h"

using std::string;

namespace ast_export {
KvltList::KvltList(KvltStream *stream) : stream_(stream) {}

KvltList::~KvltList() {
  stream_->Consumer()->ConsumeListClose();
}

KvltList KvltList::Value(string value) {
  stream_->Consumer()->ConsumeValue(value);
  KvltList list(stream_);
  return list;
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
