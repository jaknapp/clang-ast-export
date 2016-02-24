#include "KvltKvList.h"

#include <string>
#include "KvltConsumer.h"
#include "KvltKvListValue.h"
#include "KvltStream.h"

using std::string;

namespace ast_export {
KvltKvList::KvltKvList(KvltStream *stream) : stream_(stream) {}

KvltKvList::~KvltKvList() {
  stream_->Consumer()->ConsumeKvListClose();
}

KvltKvListValue KvltKvList::Key(string value) {
  stream_->Consumer()->ConsumeKey(value);
  KvltKvListValue kv_list_value(stream_);
  return kv_list_value;
}
}
