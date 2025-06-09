#pragma once

#include "builder.h"
#include "lexer.h"

#include <memory>

struct Expression {
    std::string value;
    int start;
    int end;
};

class Parser {
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Builder> builder;
    public:
        Parser(std::unique_ptr<Lexer> _lexer, std::unique_ptr<Builder> _builder);
        std::string parseTerm();
        std::string parseExpression(int precedence);
        void parse();
};