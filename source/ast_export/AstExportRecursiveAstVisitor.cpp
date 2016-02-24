#include "AstExportRecursiveAstVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"

using clang::Decl;

namespace ast_export {
AstExportRecursiveAstVisitor::AstExportRecursiveAstVisitor(
  clang::ASTContext *ast_context) : ast_context_(ast_context) {}

bool AstExportRecursiveAstVisitor::VisitDecl(Decl *Declaration) {
  return true;
}
}
