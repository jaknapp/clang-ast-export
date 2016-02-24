#ifndef CLANG_AST_EXPORT_KVLTCONSUMERJSONWRITER_H
#define CLANG_AST_EXPORT_KVLTCONSUMERJSONWRITER_H

#include "KvltConsumer.h"

namespace ast_export {
class JsonWriter : public KvltConsumer {
public:
  void ConsumeKey(std::string key) override;
  void ConsumeValue(std::string value) override;
  void ConsumeListOpen() override;
  void ConsumeListClose() override;
  void ConsumeKvListOpen() override;
  void ConsumeKvListClose() override;
};
}

#endif // CLANG_AST_EXPORT_KVLTCONSUMERJSONWRITER_H
