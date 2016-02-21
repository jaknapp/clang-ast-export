#ifndef CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
#define CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H

#include "clang/AST/RecursiveASTVisitor.h"

class clang::ASTContext;

namespace ast_export {
class AstExportRecursiveAstVisitor
  : public clang::RecursiveASTVisitor < AstExportRecursiveAstVisitor > {
public:
  explicit AstExportRecursiveAstVisitor(clang::ASTContext *context);
private:
  clang::ASTContext *ast_context_;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
