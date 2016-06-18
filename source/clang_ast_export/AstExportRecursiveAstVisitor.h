#ifndef CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
#define CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "KvltList.h"
#include "KvltStream.h"

namespace ast_export {
class KvltConsumer;
class KvltKvListValue;
}
namespace clang {
class ASTContext;
class Decl;
class SourceLocation;
}

namespace ast_export {
class AstExportRecursiveAstVisitor
  : public clang::RecursiveASTVisitor < AstExportRecursiveAstVisitor > {
public:
  AstExportRecursiveAstVisitor(
    clang::ASTContext *context, KvltConsumer *consumer);

  // These visitor functions hide the RecursiveASTVisitor definitions.
  bool VisitDecl(clang::Decl *decl);
private:
  // Exporting utilities.
  // TODO: Move somewhere else?
  void ExportSourceLocation(
    const clang::SourceLocation &location, KvltKvListValue *kvlt_value);

  clang::ASTContext *ast_context_;
  KvltStream kvlt_stream_;
  KvltList kvlt_root_;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
