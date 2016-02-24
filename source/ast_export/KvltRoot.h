#ifndef CLANG_AST_EXPORT_KVLTROOT_H
#define CLANG_AST_EXPORT_KVLTROOT_H

#include <string>

namespace ast_export {
class KvltKvList;
class KvltList;
class KvltStream;
}

namespace ast_export {
class KvltRoot {
  KvltRoot(KvltStream *stream);
  ~KvltRoot();
  void Value(std::string value);

  // TODO: Refactor these two to a common base class.
  KvltList List();
  KvltKvList KvList();
private:
  KvltStream *stream_;
};
}

#endif // CLANG_AST_EXPORT_KVLTROOT_H
