#include "MyGrammarBaseListener.h"
#include "MyGrammarBaseVisitor.h"
#include "MyGrammarLexer.h"
#include "MyGrammarParser.h"
#include <ANTLRInputStream.h>
#include <antlr4-runtime.h>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

struct Symbol {
  int value;
};

std::unordered_map<std::string, Symbol *> hashtable;

class Listener : public MyGrammarBaseListener {};

class Visitor : public MyGrammarBaseVisitor {
  std::vector<int> switchVal;
  bool defaultSwitch = false;
  unsigned int currentNestingLevel = 0;

  std::any visitSt_switch(MyGrammarParser::St_switchContext *ctx) {

    this->switchVal.push_back(stoi(ctx->INT()->getText()));
    this->defaultSwitch = false;

    auto result = visitChildren(ctx);
    this->switchVal.pop_back();
    this->currentNestingLevel = switchVal.size();

    return result;
  }

  std::any visitSt_case(MyGrammarParser::St_caseContext *ctx) {
    int caseVal = stoi(ctx->INT()->getText());
    auto result = std::any();
    if (caseVal == this->switchVal.back()) {
      this->currentNestingLevel++;
      this->defaultSwitch = true;
    }
    if (this->currentNestingLevel == this->switchVal.size()) {
      this->visitPayload(ctx->payload());
    }

    return result;
  }
  std::any visitSt_default(MyGrammarParser::St_defaultContext *ctx) {
    if (this->currentNestingLevel == this->switchVal.size()) {
      return visitChildren(ctx);
    }
    if (this->defaultSwitch)
      return std::any();
    return visitChildren(ctx);
  }
  std::any visitPayload(MyGrammarParser::PayloadContext *ctx) {
    auto first = ctx->getStart()->getText();
    if (first == "PRINT") {
      std::cout << ctx->INT()->getText() << "\n";
    }
    if (first == "BREAK;") {
      if (this->currentNestingLevel >= this->switchVal.size()) {
        this->currentNestingLevel--;
      }
      return std::any();
    }
    return visitChildren(ctx);
  }
};

int exec(antlr4::tree::ParseTree *tree) {
  Visitor *visitor = new Visitor();
  std::cout << "\n\n";
  visitor->visit(tree);
  std::cout << "\n\n";
  return 0;
}

int main(int argc, const char *argv[]) {
  std::ifstream stream;
  if (argc > 1) {
    stream.open(argv[1]);
    std::cout << argv[1] << std::endl;
  } else {
    stream.open("../prog.txt");
  }
  antlr4::ANTLRInputStream input(stream);

  MyGrammarLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  MyGrammarParser parser(&tokens);
  Listener listener;
  parser.addParseListener(&listener);

  antlr4::tree::ParseTree *tree = parser.statement();

  std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  return exec(tree);
}
