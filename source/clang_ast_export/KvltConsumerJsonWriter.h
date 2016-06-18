#ifndef CLANG_AST_EXPORT_KVLTCONSUMERJSONWRITER_H
#define CLANG_AST_EXPORT_KVLTCONSUMERJSONWRITER_H

#include <stack>
#include "KvltConsumer.h"

namespace ast_export {
class KvltConsumerJsonWriter : public KvltConsumer {
public:
  KvltConsumerJsonWriter();
  void ConsumeKey(std::string key) override;
  void ConsumeValue(std::string value) override;
  void ConsumeListOpen() override;
  void ConsumeListClose() override;
  void ConsumeKvListOpen() override;
  void ConsumeKvListClose() override;
private:
  const char *MaybeSeparatorForValue();
  const char *MaybeSeparatorForKey();

  // TODO: Instead of these, use a real tree abstraction.
  // TODO: Or at least only use on stack.
  std::stack<bool> has_children_stack_;
  std::stack<bool> is_object_stack_;
};
}

#endif // CLANG_AST_EXPORT_KVLTCONSUMERJSONWRITER_H
