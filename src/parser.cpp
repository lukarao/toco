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
            case TokenType::Identifier:
            {
                lexer->next();
                if (lexer->currentToken.type == TokenType::OpenParen) { // function call
                    lexer->next();
                    // TODO: parse multiple arguments
                    std::string argument = parseExpression(0);
                    if (lexer->currentToken.type != TokenType::CloseParen) {
                        std::cerr << "Expected closing ) after arguments, got \"" << lexer->currentToken.value << "\" instead." << std::endl;
                        std::exit(1);
                    }
                } else {
                    // parse other expressions starting with an identifier
                }
            }
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
            case TokenType::OpenBrace:
            {
                lexer->next();
                std::string content = "(block, ";
                while (lexer->currentToken.type != TokenType::CloseBrace) {
                    if (lexer->currentToken.type == TokenType::Eof) {
                        std::cerr << "Missing closing } in block." << std::endl;
                        std::exit(1);
                    }
                    content += parseExpression(0) + ", ";
                    lexer->next();
                }
                return content;
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
    while (lexer->currentToken.type == TokenType::End) {
        lexer->next();
    }
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