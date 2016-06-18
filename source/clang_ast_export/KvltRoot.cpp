#include "KvltRoot.h"

#include <iostream>
#include "KvltConsumer.h"
#include "KvltKvList.h"
#include "KvltList.h"
#include "KvltStream.h"

namespace ast_export {
KvltRoot::KvltRoot(KvltStream *stream) : stream_(stream) {}

KvltRoot::~KvltRoot() {}

void KvltRoot::Value(std::string value) {
  stream_->Consumer()->ConsumeValue(value);
}

KvltList KvltRoot::List() {
  stream_->Consumer()->ConsumeListOpen();
  KvltList list(stream_);
  return list;
}

KvltKvList KvltRoot::KvList() {
  stream_->Consumer()->ConsumeKvListOpen();
  KvltKvList kv_list(stream_);
  return kv_list;
}
}
