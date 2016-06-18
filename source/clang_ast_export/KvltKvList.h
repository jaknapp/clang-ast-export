#ifndef CLANG_AST_EXPORT_KVLTKVLIST_H
#define CLANG_AST_EXPORT_KVLTKVLIST_H

#include <string>

namespace ast_export {
class KvltKvListValue;
class KvltStream;
}

namespace ast_export {
class KvltKvList {
public:
  explicit KvltKvList(KvltStream *stream);
  // Needed because user-declared destructor is defined. N3225 12.8/8
  KvltKvList(KvltKvList &&from);
  ~KvltKvList();
  KvltKvListValue Key(std::string key);
private:
  KvltKvList();
  KvltStream *stream_;
  bool should_close_;
};
}

#endif // CLANG_AST_EXPORT_KVLTKVLIST_H
