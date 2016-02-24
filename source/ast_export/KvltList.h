#ifndef CLANG_AST_EXPORT_KVLTLIST_H
#define CLANG_AST_EXPORT_KVLTLIST_H

#include <string>

namespace ast_export {
class KvltKvList;
class KvltStream;
}

namespace ast_export {
class KvltList {
public:
  KvltList(KvltStream *stream);
  ~KvltList();
  KvltList Value(std::string value);

  // TODO: Refactor these two to a base class.
  KvltList List();
  KvltKvList KvList();
private:
  KvltStream *stream_;
};
}

#endif // CLANG_AST_EXPORT_KVLTLIST_H
