#include "parser.h"

#include <iostream> // debug

int getPrecedence(Token token) {
    switch (token.type) {
        default:
            return 0;
    }
}

Parser::Parser(std::unique_ptr<Lexer> _lexer, std::unique_ptr<Builder> _builder) {
    lexer = std::move(_lexer);
    builder = std::move(_builder);
}

std::string Parser::parseTerm() {
    while (lexer->currentToken.type != TokenType::Eof) {
        switch (lexer->currentToken.type) {
            case TokenType::Func:
            {
                lexer->next();
                // function name
                std::string name;
                if (lexer->currentToken.type == TokenType::Identifier) {
                    name = lexer->currentToken.value;
                    lexer->next();
                } else {
                    std::cerr << "Expected Identifier after Func, got \"" << lexer->currentToken.value << "\" instead." << std::endl;
                    std::exit(1);
                }
                // (parse parameters)
                // function body
                std::string body = parseExpression(0);
                return "(funcdef, " + name + ", " + body + ")";
                
            }
            case TokenType::Import:
                lexer->next();
                while (lexer->currentToken.type != TokenType::End) {
                    // consume currentToken
                    lexer->next();
                }
                break;
            case TokenType::End:
                lexer->next();
                break;
        }
    }
}

std::string Parser::parseExpression(int precedence) {
    std::string left = parseTerm();
    Token op = lexer->currentToken;
    while (precedence < getPrecedence(op)) {
        lexer->next();
        std::string right = parseExpression(getPrecedence(op));
        left = "(" + op.value + ", " + left + ", " + right + ")";
    }
    return left;
}

void Parser::parse() {
    while (lexer->currentToken.type != TokenType::Eof) {
        std::cout << parseExpression(0) << std::endl;
        lexer->next();
    }
}