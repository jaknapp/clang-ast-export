#include "AstExportAstConsumer.h"
#include "clang/AST/ASTContext.h"

namespace ast_export {
AstExportAstConsumer::AstExportAstConsumer(clang::ASTContext *Context)
  : visitor_(Context) {}

void AstExportAstConsumer::HandleTranslationUnit(clang::ASTContext &Context) {
  visitor_.TraverseDecl(Context.getTranslationUnitDecl());
}
}
