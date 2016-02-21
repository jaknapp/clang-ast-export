#include "AstExportRecursiveAstVisitor.h"
#include "clang/AST/ASTContext.h"

namespace ast_export {
AstExportRecursiveAstVisitor::AstExportRecursiveAstVisitor(
  clang::ASTContext *ast_context) : ast_context_(ast_context) {}
}
