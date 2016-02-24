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
  ~KvltKvList();
  KvltKvListValue Key(std::string key);
private:
  KvltStream *stream_;
};
}

#endif // CLANG_AST_EXPORT_KVLTKVLIST_H
