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

Expression Parser::parseTerm() {
    switch (lexer->currentToken.type) {
        // add term cases
    }
}

Expression Parser::parseExpression(int precedence) {
    Expression left = parseTerm();
    Token op = lexer->currentToken;
    while (precedence < getPrecedence(op)) {
        lexer->next();
        Expression right = parseExpression(getPrecedence(op));
        //left = builder->binary(left, op, right);
    }
    return left;
}

void Parser::parse() {
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
                    std::cerr << "Expected Identifier after Func, got \"" << lexer->currentToken.value << "\" instead.";
                    std::exit(1);
                }
                // (parse parameters)
                // function body
                Expression body = parseExpression(0);
                // builder->funcdef(name, body)
                break;
            }
            case TokenType::Import:
                lexer->next();
                while (lexer->currentToken.type != TokenType::End) {
                    // consume currentToken
                    lexer->next();
                }
                break;
            case TokenType::End:
                break;
            default:
                parseExpression(0);
                break;
        }
        lexer->next();
    }
}