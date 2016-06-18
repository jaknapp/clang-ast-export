#include "AstExportAstConsumer.h"
#include "clang/AST/ASTContext.h"

namespace ast_export {
AstExportAstConsumer::AstExportAstConsumer(clang::ASTContext *context)
  : visitor_(context, &json_writer_) {}

void AstExportAstConsumer::HandleTranslationUnit(clang::ASTContext &context) {
  visitor_.TraverseDecl(context.getTranslationUnitDecl());
}
}
