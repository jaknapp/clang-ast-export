#ifndef CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
#define CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H

#include "clang/AST/RecursiveASTVisitor.h"

namespace clang {
class ASTContext;
class Decl;
}

namespace ast_export {
class AstExportRecursiveAstVisitor
  : public clang::RecursiveASTVisitor < AstExportRecursiveAstVisitor > {
public:
  explicit AstExportRecursiveAstVisitor(clang::ASTContext *context);

  // These visitor functions hide the RecursiveASTVisitor definitions.
  bool VisitDecl(clang::Decl *Declaration);
private:
  clang::ASTContext *ast_context_;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
