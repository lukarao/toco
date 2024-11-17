#include "parser.h"

#include <iostream> // debug

Parser::Parser(Lexer *_lexer) {
    lexer = _lexer;
}

void Parser::parse() {
    while (lexer->currentToken.type != TokenType::Eof) {
        std::cout << lexer->currentToken.value << " " << lexer->currentToken.type << std::endl;
        lexer->next();
    }
}