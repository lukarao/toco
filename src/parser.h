#pragma once

#include "builder.h"
#include "lexer.h"

#include <memory>

class Parser {
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Builder> builder;
    public:
        Parser(std::unique_ptr<Lexer> _lexer, std::unique_ptr<Builder> _builder);
        void parse();
};