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

using clang::Decl;
using clang::PresumedLoc;
using clang::SourceLocation;
using clang::SourceManager;
using std::string;

namespace ast_export {
AstExportRecursiveAstVisitor::AstExportRecursiveAstVisitor(
  clang::ASTContext *ast_context,
  KvltConsumer *consumer)
  : ast_context_(ast_context),
  kvlt_stream_(consumer),
  //kvlt_root_(KvltRoot(&kvlt_stream_).List()) {}
  kvlt_root_(KvltRoot(&kvlt_stream_).List()) {
}

bool AstExportRecursiveAstVisitor::VisitDecl(Decl *decl) {
  KvltKvList kvlist = std::move(kvlt_root_.KvList());
  ExportSourceLocation(decl->getLocStart(), &kvlist.Key("loc_start"));
  ExportSourceLocation(decl->getLocEnd(), &kvlist.Key("loc_end"));

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

void AstExportRecursiveAstVisitor::ExportSourceLocation(
  const SourceLocation &location, KvltKvListValue *kvlt_value) {
  const SourceManager &source_manager = ast_context_->getSourceManager();
  KvltKvList kvlist = kvlt_value->KvList();
  bool is_valid = location.isValid();
  bool is_file_id = location.isFileID();

  //string is_valid_str = (is_valid) ?
  //kvlist.Key("is_valid"); //.Value("");
  kvlist.Key("isValid").Value(location.isValid());
  kvlist.Key("isFileID").Value(location.isFileID());
  kvlist.Key("isMacroID").Value(location.isMacroID());
  kvlist.Key("presumedLoc")
  string presumed_location = "";

  //JsonOstreamObject ostream = _ostream.NewObject();
  //SourceManager &sm = Context->getSourceManager();
  //ostream.NewPropertyAndBool("is_valid", location.isValid());
  //int invalid = 0;
  //if (!location.isValid()) {
  //  invalid = 1;
  //}
  //if (location.isValid()) {
  //  ostream.NewPropertyAndBool("is_file_id", location.isFileID());
  //  if (location.isFileID()) {
  //    ostream.NewProperty("presumedLocation");
  //    exportPresumedLocation(sm.getPresumedLoc(location));
  //    ostream.NewProperty("expansionLocation");
  //    SourceLocation expansionLocation = sm.getExpansionLoc(location);
  //    exportFullSourceLocation("", sm.getExpansionLineNumber(location), sm.getExpansionColumnNumber(location), sm.getExpansionLoc(location).isValid());
  //    //exportFullSourceLocation(sm.getExpansionLoc(location));
  //    ostream.NewProperty("spellingLocation");
  //    exportFullSourceLocation("", sm.getSpellingLineNumber(location), sm.getSpellingColumnNumber(location), sm.getSpellingLoc(location).isValid());
  //    //exportFullSourceLocation(sm.getSpellingLoc(location));
  //  }
  //}
}
void AstExportRecursiveAstVisitor::ExportPresumedLoc(const PresumedLoc &presumed_location, KvltKvListValue *kvlt_value) {
  const SourceManager &source_manager = ast_context_->getSourceManager();

}
//
//void AstExportRecursiveAstVisitor::ExportPresumedLocation(const PresumedLoc &PLoc) {
//  JsonOstreamObject ostream = _ostream.NewObject();
//  ostream.NewPropertyAndBool("is_valid", PLoc.isValid());
//  if (PLoc.isValid()) {
//    ostream.NewPropertyAndValue("file", PLoc.getFilename());
//    ostream.NewPropertyAndUint("line", PLoc.getLine());
//    ostream.NewPropertyAndUint("column", PLoc.getColumn());
//  }
//}

}
