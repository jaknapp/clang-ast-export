#ifndef CLANG_AST_EXPORT_ASTEXPORTASTFRONTENDACTION_H
#define CLANG_AST_EXPORT_ASTEXPORTASTFRONTENDACTION_H

#include <memory>
#include "clang/Frontend/FrontendAction.h"

namespace clang {
class ASTConsumer;
class CompilerInstance;
}

namespace llvm {
class StringRef;
}

namespace ast_export {
class AstExportAstFrontendAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) override;
};
}

#endif // CLANG_AST_EXPORT_ASTEXPORTASTFRONTENDACTION_H
