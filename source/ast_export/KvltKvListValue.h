#ifndef CLANG_AST_EXPORT_KVLTKVLISTVALUE_H
#define CLANG_AST_EXPORT_KVLTKVLISTVALUE_H

#include <string>

namespace ast_export {
class KvltKvList;
class KvltList;
class KvltStream;
}

namespace ast_export {
class KvltKvListValue {
public:
  KvltKvListValue(KvltStream *stream);
  ~KvltKvListValue();
  KvltKvList Value(std::string value);

  // TODO: Refactor these two to a common base class.
  KvltList List();
  KvltKvList KvList();
private:
  KvltStream *stream_;
};
}

#endif // CLANG_AST_EXPORT_KVLTKVLISTVALUE_H
