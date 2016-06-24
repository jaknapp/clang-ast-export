#ifndef CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
#define CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "KvltList.h"
#include "KvltStream.h"

namespace ast_export {
class KvltConsumer;
class KvltKvList;
class KvltKvListValue;
}
namespace clang {
class ASTContext;
class CXXRecordDecl;
class Decl;
class NamedDecl;
class PresumedLoc;
class RecordDecl;
class SourceLocation;
class TagDecl;
class TypeDecl;
}

namespace ast_export {
class AstExportRecursiveAstVisitor
  : public clang::RecursiveASTVisitor < AstExportRecursiveAstVisitor > {
public:
  AstExportRecursiveAstVisitor(
    clang::ASTContext *context, KvltConsumer *consumer);

  bool TraverseDecl(clang::Decl *D);

  // These visitor functions hide the RecursiveASTVisitor definitions.
  bool VisitDecl(clang::Decl *decl);
  bool VisitNamedDecl(clang::NamedDecl *decl);
  bool VisitTypeDecl(clang::TypeDecl *decl);
  bool VisitTagDecl(clang::TagDecl *decl);
  bool VisitRecordDecl(clang::RecordDecl *decl);
  bool VisitCxxRecordDecl(clang::CXXRecordDecl *decl);
private:
  // Exporting utilities.
  // TODO: Move somewhere else?
  void ExportSourceLocation(
    const clang::SourceLocation &location, KvltKvListValue *kvlt_value);
  void ExportPresumedLoc(
    const clang::PresumedLoc &presumed_location, KvltKvListValue *kvlt_value);
  void ExportExpansionLoc(
    const clang::SourceLocation &expansion_location, KvltKvListValue *kvlt_value);
  void ExportSpellingLoc(
    const clang::SourceLocation &spelling_location, KvltKvListValue *kvlt_value);

  clang::ASTContext *ast_context_;
  KvltStream kvlt_stream_;
  KvltList kvlt_root_;
  KvltKvList *kvlist_for_active_traversal_node_;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTRECURSIVEASTVISITOR_H
