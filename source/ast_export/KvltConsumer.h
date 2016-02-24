#ifndef CLANG_AST_EXPORT_KVLTCONSUMER_H
#define CLANG_AST_EXPORT_KVLTCONSUMER_H

#include <string>

namespace ast_export {
class KvltConsumer {
public:
  virtual void ConsumeKey(std::string key) = 0;
  virtual void ConsumeValue(std::string value) = 0;
  virtual void ConsumeListOpen() = 0;
  virtual void ConsumeListClose() = 0;
  virtual void ConsumeKvListOpen() = 0;
  virtual void ConsumeKvListClose() = 0;
};
}

#endif // CLANG_AST_EXPORT_KVLTCONSUMER_H
