#pragma once

#include "builder.h"
#include "lexer.h"

class Parser {
    Lexer *lexer;
    Builder *builder;
    public:
        Parser(Lexer *_lexer, Builder *_builder);
        void parse();
};