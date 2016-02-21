#ifndef CLANG_AST_EXPORT_ASTEXPORTASTCONSUMER_H
#define CLANG_AST_EXPORT_ASTEXPORTASTCONSUMER_H

#include "AstExportRecursiveAstVisitor.h"
#include "clang/AST/ASTConsumer.h"

class clang::ASTContext;

namespace ast_export {
class AstExportAstConsumer : public clang::ASTConsumer {
public:
  explicit AstExportAstConsumer(clang::ASTContext *context);
  void HandleTranslationUnit(clang::ASTContext &context) override;
private:
  AstExportRecursiveAstVisitor visitor_;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTASTCONSUMER_H
