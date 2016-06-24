#include "AstExportRecursiveAstVisitor.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "KvltConsumer.h"
#include "KvltKvList.h"
#include "KvltKvListValue.h"
#include "KvltRoot.h"
#include "KvltStream.h"

// debug
#include <iostream>

using clang::CXXRecordDecl;
using clang::Decl;
using clang::NamedDecl;
using clang::PresumedLoc;
using clang::RecordDecl;
using clang::SourceLocation;
using clang::SourceManager;
using clang::TagDecl;
using clang::TypeDecl;
using std::string;

namespace ast_export {
AstExportRecursiveAstVisitor::AstExportRecursiveAstVisitor(
  clang::ASTContext *ast_context,
  KvltConsumer *consumer)
  : ast_context_(ast_context),
  kvlt_stream_(consumer),
  //kvlt_root_(KvltRoot(&kvlt_stream_).List()) {}
  kvlt_root_(KvltRoot(&kvlt_stream_).List()),
  kvlist_for_active_traversal_node_(nullptr) {
}

bool AstExportRecursiveAstVisitor::TraverseDecl(Decl *declaration) {
  // TODO: Sometimes it calls this function recursively. When it does so, we should add to a stack the new node being exported. Should try to find out why it calls this recursively. I was kind of under the assumption it would traverse each node (including visiting all the Visit*) for each node one at a time.
  bool allocated_kvltlist = false;
  if (!kvlist_for_active_traversal_node_) {
    allocated_kvltlist = true;
    //std::cout << "traversing 1";
    KvltKvList kvlist = std::move(kvlt_root_.KvList());
    //std::cout << "traversing 2";
    kvlist_for_active_traversal_node_ = &kvlist;
    RecursiveASTVisitor::TraverseDecl(declaration);
    kvlist_for_active_traversal_node_ = nullptr;
  } else {
    RecursiveASTVisitor::TraverseDecl(declaration);
  }
  //std::cout << "traversing 3";
  return true;
}

bool AstExportRecursiveAstVisitor::VisitDecl(Decl *decl) {
  KvltKvList &kvlist = *kvlist_for_active_traversal_node_; // std::move(kvlt_root_.KvList());
  kvlist.Key("clang_type").Value("Decl");
  //std::cout << "visit decl 1";
  ExportSourceLocation(decl->getLocStart(), &kvlist.Key("loc_start"));
  //std::cout << "visit decl 2";
  ExportSourceLocation(decl->getLocEnd(), &kvlist.Key("loc_end"));
  //std::cout << "visit decl 3";

  //const DeclContext *Ctx = Declaration->getDeclContext();
  ////std::ostream& OS = std::cout;
  ////auto &OS = llvm::outs();
  //JsonOstreamObject streamer = _root.NewObject("Decl");

  ////bool is_anonymous = (Declaration->getDeclName()) ? false : true;
  ////streamer.NewPropertyAndBool("is_anonymous", is_anonymous);

  ////streamer.NewPropertyAndValue("name", Declaration->getNameAsString());
  ////streamer.NewPropertyAndValue("qualified_name",
  ////  Declaration->getQualifiedNameAsString());

  ////streamer.NewPropertyAndValue("identifier_name",
  ////  Declaration->getIdentifier()->getName());
  ////streamer.NewPropertyAndPointer("unique_id", Declaration);
  //streamer.NewPropertyAndPointer("unique_id", Declaration->getDeclContext());

  //streamer.NewProperty("declaration_start");
  //exportSourceLocation(Declaration->getLocation());

  ////streamer.NewProperty("right_brace_start");
  ////exportSourceLocation(Declaration->getRBraceLoc());

  //streamer.NewProperty("source_start");
  //exportSourceLocation(Declaration->getLocStart());

  //streamer.NewProperty("source_end");
  //exportSourceLocation(Declaration->getLocEnd());

  ////if (Ctx->isFunctionOrMethod()) {
  ////  streamer.NewProperty("Function");
  ////  ExportFunctionOrMethod(Declaration);
  ////  //llvm::outs() << "'function': '" << Declaration->getNameAsString() << "',";
  ////  ////Declaration->printName(OS);
  ////  return;
  ////}

  //typedef SmallVector<const DeclContext *, 8> ContextsTy;
  //ContextsTy Contexts;

  //// Collect contexts.
  //while (Ctx && isa<NamedDecl>(Ctx)) {
  //  Contexts.push_back(Ctx);
  //  Ctx = Ctx->getParent();
  //}

  ////streamer.NewProperty("parents");
  //      {
  //        JsonOstreamArray parents_stream = streamer.NewArray("parents");
  //        for (ContextsTy::reverse_iterator I = Contexts.rbegin(), E = Contexts.rend();
  //          I != E; ++I) {
  //          const DeclContext &parent = **I;
  //          parents_stream.NewPointerValue(&parent);
  //        }
  //      }
  return true;
}

bool AstExportRecursiveAstVisitor::VisitNamedDecl(NamedDecl *decl) {
  KvltKvList &kvlist = *kvlist_for_active_traversal_node_; // std::move(kvlt_root_.KvList());
  kvlist.Key("clang_type").Value("NamedDecl");
  //ExportSourceLocation(decl->getLocStart(), &kvlist.Key("loc_start"));
  //ExportSourceLocation(decl->getLocEnd(), &kvlist.Key("loc_end"));
  return true;
}

bool AstExportRecursiveAstVisitor::VisitTypeDecl(TypeDecl *decl) {
  KvltKvList &kvlist = *kvlist_for_active_traversal_node_;
  kvlist.Key("clang_type").Value("TypeDecl");
  return true;
}

bool AstExportRecursiveAstVisitor::VisitTagDecl(TagDecl *decl) {
  KvltKvList &kvlist = *kvlist_for_active_traversal_node_;
  kvlist.Key("clang_type").Value("TagDecl");
  kvlist.Key("kind_name").Value(decl->getKindName().str());
  kvlist.Key("identifier_info_name_start").Value(decl->getIdentifier()->getNameStart());
  return true;
}

bool AstExportRecursiveAstVisitor::VisitRecordDecl(RecordDecl *decl) {
  KvltKvList &kvlist = *kvlist_for_active_traversal_node_;
  kvlist.Key("clang_type").Value("RecordDecl");
  return true;
}

bool AstExportRecursiveAstVisitor::VisitCxxRecordDecl(CXXRecordDecl *decl) {
  KvltKvList &kvlist = *kvlist_for_active_traversal_node_;
  kvlist.Key("clang_type").Value("CXXRecordDecl");
  return true;
}

void AstExportRecursiveAstVisitor::ExportSourceLocation(
  const SourceLocation &location, KvltKvListValue *kvlt_value) {
  const SourceManager &source_manager = ast_context_->getSourceManager();
  KvltKvList kvlist = kvlt_value->KvList();

  kvlist.Key("isValid").Value(location.isValid());
  kvlist.Key("isFileID").Value(location.isFileID());
  kvlist.Key("isMacroID").Value(location.isMacroID());

  if (!location.isValid() || !location.isFileID()) {
    return;
  }

  ExportPresumedLoc(
    source_manager.getPresumedLoc(location), &kvlist.Key("presumedLoc"));
  ExportExpansionLoc(
    source_manager.getExpansionLoc(location), &kvlist.Key("expansionLoc"));
  ExportSpellingLoc(
    source_manager.getSpellingLoc(location), &kvlist.Key("spellingLoc"));
}

void AstExportRecursiveAstVisitor::ExportPresumedLoc(
  const PresumedLoc &presumed_location, KvltKvListValue *kvlt_value) {
  KvltKvList kvlist = kvlt_value->KvList();

  kvlist.Key("isValid").Value(presumed_location.isValid());
  if (presumed_location.isValid()) {
    kvlist.Key("filename").Value(presumed_location.getFilename());
    kvlist.Key("line").Value(presumed_location.getLine());
    kvlist.Key("column").Value(presumed_location.getColumn());
  }
}

void AstExportRecursiveAstVisitor::ExportExpansionLoc(
  const SourceLocation &expansion_location, KvltKvListValue *kvlt_value) {
  const SourceManager &source_manager = ast_context_->getSourceManager();
  KvltKvList kvlist = kvlt_value->KvList();

  kvlist.Key("isValid").Value(expansion_location.isValid());
  if (expansion_location.isValid()) {
    kvlist.Key("line").Value(source_manager.getExpansionLineNumber(expansion_location));
    kvlist.Key("column").Value(source_manager.getExpansionColumnNumber(expansion_location));
  }
}

void AstExportRecursiveAstVisitor::ExportSpellingLoc(
  const SourceLocation &spelling_location, KvltKvListValue *kvlt_value) {
  const SourceManager &source_manager = ast_context_->getSourceManager();
  KvltKvList kvlist = kvlt_value->KvList();

  kvlist.Key("isValid").Value(spelling_location.isValid());
  if (spelling_location.isValid()) {
    kvlist.Key("line").Value(source_manager.getSpellingLineNumber(spelling_location));
    kvlist.Key("column").Value(source_manager.getSpellingColumnNumber(spelling_location));
  }
}
}
