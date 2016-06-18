#include "KvltKvListValue.h"

#include <sstream>
#include <string>
#include "KvltConsumer.h"
#include "KvltKvList.h"
#include "KvltList.h"
#include "KvltStream.h"

using std::string;
using std::stringstream;

namespace ast_export {
KvltKvListValue::KvltKvListValue(KvltStream *stream, KvltKvList *parent)
  : stream_(stream), parent_(parent) {}

KvltKvListValue::~KvltKvListValue() {}

//template <typename T> KvltKvList &KvltKvListValue::Value(const T &value) {
//  std::sstream ss;
//  ss << value;
//  stream_->Consumer()->ConsumeValue(std::move(ss.str()));
//  return *parent_;
//}

//KvltKvList &KvltKvListValue::Value(string value) {
//  stream_->Consumer()->ConsumeValue(value);
//  return *parent_;
//}

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
