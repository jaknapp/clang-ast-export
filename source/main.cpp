#include "ast_export/AstExportAstFrontendAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using clang::tooling::ClangTool;
using clang::tooling::CommonOptionsParser;
using clang::tooling::newFrontendActionFactory;
using llvm::cl::OptionCategory;
using llvm::cl::extrahelp;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static extrahelp MoreHelp("\nMore help text...");

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
    OptionsParser.getSourcePathList());
  return Tool.run(
    newFrontendActionFactory<ast_export::AstExportAstFrontendAction>().get());
}
