#ifndef CLANG_AST_EXPORT_KVLTKVLISTVALUE_H
#define CLANG_AST_EXPORT_KVLTKVLISTVALUE_H

#include <sstream>
#include <string>

namespace ast_export {
class KvltKvList;
class KvltList;
class KvltStream;
}

namespace ast_export {
class KvltKvListValue {
public:
  explicit KvltKvListValue(KvltStream *stream, KvltKvList *parent);
  ~KvltKvListValue();
  template <typename T> KvltKvList &Value(const T &value);
  //KvltKvList &Value(std::string value);

  // TODO: Refactor these two to a common base class.
  KvltList List();
  KvltKvList KvList();
private:
  KvltKvListValue();
  KvltStream *stream_;
  KvltKvList *parent_;
};

template <typename T> KvltKvList &KvltKvListValue::Value(const T &value) {
  std::stringstream ss;
  ss << value;
  stream_->Consumer()->ConsumeValue(std::move(ss.str()));
  return *parent_;
}

}

#endif // CLANG_AST_EXPORT_KVLTKVLISTVALUE_H
