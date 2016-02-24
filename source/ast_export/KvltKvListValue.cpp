#include "KvltKvListValue.h"

#include <string>
#include "KvltConsumer.h"
#include "KvltKvList.h"
#include "KvltList.h"
#include "KvltStream.h"

using std::string;

namespace ast_export {
KvltKvListValue::KvltKvListValue(KvltStream *stream) : stream_(stream) {}

KvltKvListValue::~KvltKvListValue() {}

KvltKvList KvltKvListValue::Value(string value) {
  stream_->Consumer()->ConsumeValue(value);
  KvltKvList kv_list(stream_);
  return kv_list;
}

KvltList KvltKvListValue::List() {
  stream_->Consumer()->ConsumeListOpen();
  KvltList list(stream_);
  return list;
}

KvltKvList KvltKvListValue::KvList() {
  stream_->Consumer()->ConsumeKvListOpen();
  KvltKvList kv_list(stream_);
  return kv_list;
}
}
