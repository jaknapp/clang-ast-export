#include <memory>
#include "AstExportAstConsumer.h"
#include "AstExportAstFrontendAction.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"

namespace ast_export {
std::unique_ptr<clang::ASTConsumer>
AstExportAstFrontendAction::CreateASTConsumer(
  clang::CompilerInstance &compiler, llvm::StringRef input_file) {
  return std::unique_ptr<clang::ASTConsumer>(
    new AstExportAstConsumer(&compiler.getASTContext()));
}
}
