#ifndef CLANG_AST_EXPORT_ASTEXPORTASTCONSUMER_H
#define CLANG_AST_EXPORT_ASTEXPORTASTCONSUMER_H

#include "AstExportRecursiveAstVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "KvltConsumerJsonWriter.h"

namespace clang {
class ASTContext;
}

namespace ast_export {
class AstExportAstConsumer : public clang::ASTConsumer {
public:
  explicit AstExportAstConsumer(clang::ASTContext *context);
  void HandleTranslationUnit(clang::ASTContext &context) override;
private:
  KvltConsumerJsonWriter json_writer_;
  AstExportRecursiveAstVisitor visitor_;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTASTCONSUMER_H
