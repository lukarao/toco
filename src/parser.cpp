#include "parser.h"

#include <iostream> // debug

Parser::Parser(std::unique_ptr<Lexer> _lexer, std::unique_ptr<Builder> _builder) {
    lexer = std::move(_lexer);
    builder = std::move(_builder);
}

void Parser::parse() {
    while (lexer->currentToken.type != TokenType::Eof) {
        std::cout << lexer->currentToken.value << " " << lexer->currentToken.type << std::endl;
        lexer->next();
    }
}